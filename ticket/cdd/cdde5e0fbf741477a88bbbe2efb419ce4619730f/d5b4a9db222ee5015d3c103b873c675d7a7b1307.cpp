#if (wxVERSION_NUMBER >= 2900)
inline int wxGetPopupMenuSelectionFromUser(wxWindow* wnd, wxMenu& menu, int x, int y)
{
   return wnd->GetPopupMenuSelectionFromUser(menu, x, y);
}
#else
extern int wxGetPopupMenuSelectionFromUser(wxWindow*, wxMenu&, int x, int y);
#endif

/////////////////////////////////////////////////////////////////////////////

#if (wxVERSION_NUMBER < 2900)
static int gs_popupMenuSelection = wxID_NONE;

class wxWindowHack : public wxWindow
{
public:
   void InternalOnPopupMenu(wxCommandEvent& event)
   {
       // store the id in a global variable where we'll retrieve it from later
       gs_popupMenuSelection = event.GetId();
   }
};

int wxGetPopupMenuSelectionFromUser(wxWindow* wnd, wxMenu& menu, int x, int y)
{
    wxWindowHack* hack = (wxWindowHack*)wnd;
    gs_popupMenuSelection = wxID_NONE;

    hack->Connect(wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(wxWindowHack::InternalOnPopupMenu),
            NULL,
            hack);

    hack->PopupMenu(&menu, x, y);

    hack->Disconnect(wxEVT_COMMAND_MENU_SELECTED,
               wxCommandEventHandler(wxWindowHack::InternalOnPopupMenu),
               NULL,
               hack);

    return gs_popupMenuSelection;
}
#endif

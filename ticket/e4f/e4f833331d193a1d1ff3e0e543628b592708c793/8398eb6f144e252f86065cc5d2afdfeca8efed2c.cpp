/***************************************************************
 * Name:      menutitleMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2011-08-04
 * Copyright:  ()
 * License:
 **************************************************************/

#include <wx/msgdlg.h>

//(*InternalHeaders(menutitleFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)
#include <wx/app.h>

class menutitleFrame: public wxFrame
{
    public:

        menutitleFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~menutitleFrame();

    private:

        //(*Handlers(menutitleFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(menutitleFrame)
        static const long ID_STATICTEXT1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(menutitleFrame)
        wxStaticText* StaticText1;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};


//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(menutitleFrame)
const long menutitleFrame::ID_STATICTEXT1 = wxNewId();
const long menutitleFrame::idMenuQuit = wxNewId();
const long menutitleFrame::idMenuAbout = wxNewId();
const long menutitleFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(menutitleFrame,wxFrame)
    //(*EventTable(menutitleFrame)
    //*)
END_EVENT_TABLE()

menutitleFrame::menutitleFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(menutitleFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Label"), wxPoint(184,96), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
//    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    MenuItem2 = new wxMenuItem(NULL, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    MenuItem2->SetMenu(Menu2);
    Menu2->Append(MenuItem2);
    Menu2->Remove(MenuItem2);
    //MenuItem2->SetMenu(Menu2);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&menutitleFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&menutitleFrame::OnAbout);
    //*)
}

menutitleFrame::~menutitleFrame()
{
    //(*Destroy(menutitleFrame)
    //*)
}

void menutitleFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void menutitleFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}




class menutitleApp : public wxApp
{
    public:
        virtual bool OnInit();
};

IMPLEMENT_APP(menutitleApp);
bool menutitleApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	menutitleFrame* Frame = new menutitleFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}

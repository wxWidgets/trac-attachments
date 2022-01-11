
#include <wx/wx.h>


class MyFrame : public wxFrame
{
    enum { ID_Command = wxID_HIGHEST+1 };

public:

    MyFrame(wxWindow* parent) : wxFrame(parent, wxID_ANY, wxT("Test"))
    {
        wxMenuBar* mb = new wxMenuBar;
        wxMenu* file_menu = new wxMenu;
        file_menu->Append(ID_Command, _("Open URL...")); 
        mb->Append(file_menu, _("File"));
        SetMenuBar(mb);
    }

    void OnOpenURL(wxCommandEvent& evt)
    {
        wxMessageBox(wxT("Command Clicked"));
        evt.Skip();
    }

    DECLARE_EVENT_TABLE();
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(MyFrame::ID_Command, MyFrame::OnOpenURL)
END_EVENT_TABLE()



class MyApp : public wxApp
{
public:
    bool OnInit()
    {
        wxFrame* frame = new MyFrame(NULL);
        SetTopWindow(frame);
        frame->Show();
        return true;
    }
};

DECLARE_APP(MyApp);
IMPLEMENT_APP(MyApp);

 	  	 


#include "wx/wx.h"
#include "wx/defs.h"

#include <iostream>
using namespace std;

class MainFrame: public wxFrame {
	
	DECLARE_EVENT_TABLE()
	
public:
	MainFrame():
	    wxFrame(NULL, -1, _("MenuOpenTest")) {
	    
	    wxMenu *fileMenu = new wxMenu;
	    fileMenu->Append(wxID_EXIT, _("E&xit") );

	    wxMenuBar *menuBar = new wxMenuBar;
	    menuBar->Append(fileMenu, _("&File") );

	    SetMenuBar(menuBar);
		    
	    CreateStatusBar();
	    SetStatusText( _T("Welcome to wxWidgets!") );
	}
	
	void OnMenuOpen(wxMenuEvent& event) {
	    cout << "MenuOpenTest menu open" << endl;
	    wxMessageBox(_("MenuOpenTest menu open"));
	}
	
	void OnExit(wxCommandEvent &event) {
	    Close();
	}
};

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU_OPEN(MainFrame::OnMenuOpen)
    EVT_MENU(wxID_EXIT, MainFrame::OnExit)
END_EVENT_TABLE()

class App: public wxApp
{
virtual bool OnInit();
};

bool App::OnInit()
{
    MainFrame *frame = new MainFrame();
    frame->Show(true);
    SetTopWindow(frame);
    return true;
} 

IMPLEMENT_APP(App)
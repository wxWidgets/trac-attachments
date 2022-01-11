#include "wx/wx.h"
#include <wx/propgrid/propgrid.h>

#define PGID 1

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnDialog(wxCommandEvent& event);

private:
    DECLARE_EVENT_TABLE()
};

enum
{
    Minimal_Quit = wxID_EXIT,
    DLOG_MODAL=101,
    DLOG_MODELESS
};


BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(DLOG_MODAL, MyFrame::OnDialog)
    EVT_MENU(DLOG_MODELESS, MyFrame::OnDialog)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)


class TestDialog: public wxDialog {
public:
	
	wxPropertyGrid *pg;	
	TestDialog(wxWindow* parent);
	~TestDialog(void) {};
	void OnPropChanged(wxPropertyGridEvent& event);
	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(TestDialog, wxDialog)
EVT_PG_CHANGED( PGID,TestDialog::OnPropChanged )
END_EVENT_TABLE()



bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    MyFrame *frame = new MyFrame("Minimal wxWidgets App");
    frame->Show(true);
    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
 
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    fileMenu->Append(Minimal_Quit, "E&xit\tAlt-X", "Quit this program");
   	fileMenu->Append(DLOG_MODAL, "Modal version");
	fileMenu->Append(DLOG_MODELESS, "Modeless version");

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");
 
    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);


}


// event handlers

void MyFrame::OnDialog(wxCommandEvent &event)
{
	TestDialog *dlog = new TestDialog(this);
	if (event.GetId() == DLOG_MODAL)
		dlog->ShowModal();
	else
		dlog->Show();
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}


TestDialog::TestDialog(wxWindow* parent):
wxDialog(parent, wxID_ANY, _T("Preferences"), wxPoint(-1,-1), wxSize(300,300), wxCAPTION | wxCLOSE_BOX) {	

	pg = new wxPropertyGrid(
							this, // parent
							PGID, // id
							wxDefaultPosition, // position
							wxSize(540,380), // size
							wxPG_DEFAULT_STYLE);
	pg->SetVerticalSpacing(3);
	pg->Append( new wxPropertyCategory(wxT("Capture") ));

	wxArrayString choices;
	choices.Add("c1"); choices.Add("c2"); choices.Add("c3");
	pg->Append(new wxEnumProperty("choices",wxPG_LABEL,choices));
}
	
void TestDialog::OnPropChanged(wxPropertyGridEvent& WXUNUSED(event)) {
;
}


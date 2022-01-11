// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif



class TestApp: public wxApp {
	public:
		virtual bool OnInit();
};



class MainFrame: public wxFrame {
	public:
		MainFrame(const wxString &title);
		
		void Iconize(bool iconize=true);
		
		void OnIconize(wxIconizeEvent &event);
		void OnMinButtonPress(wxCommandEvent &event);
		void OnTimer(wxTimerEvent &event);
	
	protected:
		wxTextCtrl *Display;
		wxButton *MinButton;
		wxTimer *RestoreTimer;

	private:
		wxPanel *MainPanel;
		DECLARE_EVENT_TABLE()
};



// IDs for controls and menu items
enum {
	// control IDs
	MinButtonId = wxID_HIGHEST,
	RestoreTimerId
};

// Event table
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_ICONIZE(MainFrame::OnIconize)
	EVT_TIMER(RestoreTimerId, MainFrame::OnTimer)
	EVT_BUTTON(MinButtonId, MainFrame::OnMinButtonPress)
END_EVENT_TABLE()

// This macro defines main() and does all the appropriate stuff to run the app class
IMPLEMENT_APP(TestApp)

// TestApp implementation

bool TestApp::OnInit() {
	if (!wxApp::OnInit()) return false;
	MainFrame *frame = new MainFrame(_T("Windows EVT_ICONIZE Bug Demo"));
	frame->Show(true);
	return true;
}

// MainFrame implementation

MainFrame::MainFrame(const wxString &title) :wxFrame(NULL, wxID_ANY, title) {
	
	MainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	
	Display = new wxTextCtrl(MainPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
	
	MinButton = new wxButton(MainPanel, MinButtonId, _T("Minimise && Hide"));
	
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	MainSizer->Add(Display, 1, wxEXPAND | wxALIGN_CENTER | wxALL, 5);
	MainSizer->Add(MinButton, 0, wxEXPAND | wxALIGN_CENTER | wxALL, 5);
	
	MainPanel->SetSizer(MainSizer);
	
	wxString desc = _T("Minimising this window will cause it to auto-restore after 2 seconds.\n\n");
	desc += _T("Using the system's minimise button you should see that the Iconize(False) method triggers the EVT_ICONIZE event\n\n");
	desc += _T("Using the 'Minimise & Hide' button you should see that the Iconize(False) method doesn't trigger the EVT_ICONIZE event\n\n");
	Display->AppendText(desc);
}

void MainFrame::OnIconize(wxIconizeEvent &event) {
	wxString msg;
	msg.Printf(_T("EVT_ICONIZE triggered (window is being %s)\n"), (event.Iconized() ? _T("iconized") : _T("restored")));
	Display->AppendText(msg);
	if (event.Iconized()) {
		// Create a timer to auto-restore the window after 2 seconds
		RestoreTimer = new wxTimer(this, RestoreTimerId);
		RestoreTimer->Start(2000, wxTIMER_ONE_SHOT);
	}
}

void MainFrame::OnMinButtonPress(wxCommandEvent &WXUNUSED(event)) {
	Iconize(true);
	Hide();
}

void MainFrame::OnTimer(wxTimerEvent &WXUNUSED(event)) {
	Show();
	// The following Iconize() will not generate an EVT_ICONIZE event on Windows
	Iconize(false);
}

void MainFrame::Iconize(bool iconize) {
	wxString msg;
	msg.Printf(_T("Iconize(%s) called\n"), (iconize ? _T("true") : _T("false")));
	Display->AppendText(msg);
	wxFrame::Iconize(iconize);
}


 	  	 

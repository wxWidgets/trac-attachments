
#include "wx/wx.h"

// Declare the application class
class MyApp : public wxApp
{
public:
	// Called on application startup
	virtual bool OnInit();
};

// Declare our main frame class
class MyFrame : public wxFrame
{
public:
	// Constructor
	MyFrame(const wxString& title);
	// Event handlers
	void OnQuit(wxCommandEvent& event);
	void OnRadioBox(wxCommandEvent& event);
private:
	// This class handles events
	DECLARE_EVENT_TABLE()
};

	// Implements MyApp& GetApp()
	DECLARE_APP(MyApp)
	// Give wxWidgets the means to create a MyApp object
	IMPLEMENT_APP(MyApp)

// Initialize the application
bool MyApp::OnInit()
{
	// Create the main application window
	MyFrame *frame = new MyFrame(wxT("Minimal wxWidgets App"));
	// Show it
	frame->Show(true);
	// Start the event loop
	return true;
}

// Event table for MyFrame
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
	EVT_RADIOBOX(600, MyFrame::OnRadioBox)
END_EVENT_TABLE()

void MyFrame::OnQuit(wxCommandEvent& event)
{
	// Destroy the frame
	Close();
}

MyFrame::MyFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title)
{

// When the menu is addded,
// the event callbacks from the RadioBox disappear!
// the WM_COMMAND/BN_CLICKED message is not correctly processed.

#if 1
	// Create a menu bar
	wxMenu *fileMenu = new wxMenu;
	fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"), wxT("Quit this program"));
	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, wxT("&File"));
	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);
#endif

	// Put a radiobox here.. 
	wxArrayString strings;
	strings.Add(wxT("&One"));
	strings.Add(wxT("&Two"));
	strings.Add(wxT("T&hree"));
	wxRadioBox* radioBox = new wxRadioBox(this, 600,
		wxT("Radiobox"), wxDefaultPosition, wxDefaultSize, strings, 3, wxRA_SPECIFY_COLS);
}

void MyFrame::OnRadioBox(wxCommandEvent &event)
{
	wxMessageBox(wxT("Callback received"), wxT("Callback received"), wxOK | wxICON_INFORMATION, this);
}

 	  	 

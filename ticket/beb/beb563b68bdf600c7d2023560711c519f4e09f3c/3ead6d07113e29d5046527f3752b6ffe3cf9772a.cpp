 
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
 
#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows and OS/2 it is in resources and even
// though we could still include the XPM here it would be unused)
#if !defined(__WXMSW__) && !defined(__WXPM__)
    #include "../sample.xpm"
#endif

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();
private:
	wxPoint m_mousePos;
	wxFrame *frame;
	void OnMouseMove(wxMouseEvent& event);
	void OnMousePressed(wxMouseEvent& event);
	void OnMouseReleased(wxMouseEvent& event);
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------



// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MyApp)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;


	frame = new wxFrame(NULL, wxID_ANY, _("Aadsds"), wxPoint(200, 200), wxSize(200, 200), wxFRAME_SHAPED);
	frame->SetBackgroundColour(*wxRED);
	wxBoxSizer *frameSizer = new wxBoxSizer(wxVERTICAL);
	frame->SetSizer(frameSizer);

	wxBoxSizer *scrolledSizer = new wxBoxSizer(wxVERTICAL);
	wxScrolledWindow* scrolledWindow = new wxScrolledWindow(frame);
	scrolledWindow->SetBackgroundColour(*wxWHITE);
	scrolledWindow->SetSizer(scrolledSizer);
	scrolledWindow->SetScrollRate(0, 10);

	scrolledSizer->Add(new wxPanel(scrolledWindow, wxID_ANY, wxDefaultPosition, wxSize(-1, 600)));
	
	frameSizer->Add(scrolledWindow, wxSizerFlags(1).Expand().Border(wxTOP, 10));
	frame->Layout();
	frame->Show();

	frame->Connect(wxEVT_MOTION, wxMouseEventHandler(MyApp::OnMouseMove), NULL, this);
	frame->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(MyApp::OnMousePressed), NULL, this);
	frame->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MyApp::OnMouseReleased), NULL, this);

    return true;
}


/**
 * Moused pressed
 */
void MyApp::OnMousePressed(wxMouseEvent &WXUNUSED(event))
{
		wxPoint tmp(wxGetMousePosition());

		//frame->CaptureMouse();
		m_mousePos = tmp - frame->GetPosition();
}

/**
 * Moused released
 */
void MyApp::OnMouseReleased(wxMouseEvent &event)
{
	/*if (frame->HasCapture())
    {
        frame->ReleaseMouse();
    }*/

	event.Skip();
}


/**
 * Move window
 */
void MyApp::OnMouseMove(wxMouseEvent &event)
{  
	// move window to new position
    if (event.Dragging() && event.LeftIsDown()/* && frame->HasCapture()*/)
    {
		frame->Move(wxGetMousePosition() - m_mousePos);
    }

	event.Skip();
}

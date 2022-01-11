// This is a simple application which demonstrates an off-by-one bug
// in DrawPoint in GTK.

#include "wx/app.h"
#include "wx/event.h"
#include "wx/menu.h"
#include "wx/sizer.h"
#include "wx/frame.h"
#include "wx/dcclient.h"

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title, wxWindowID id);

    // event handlers (these functions should _not_ be virtual)
    void OnPaint(wxPaintEvent &WXUNUSED(event));

private:
    bool m_usePoints;
 
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};

wxIMPLEMENT_APP(MyApp);

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_PAINT(MyFrame::OnPaint)
wxEND_EVENT_TABLE()


// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

bool MyApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    MyFrame *frame = new MyFrame(wxT("wxDrawPoint Off-By-One App"), wxID_ANY);
    frame->Show(true);

    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title, wxWindowID id)
       : wxFrame(NULL, id, title)
{
}

void MyFrame::OnPaint(wxPaintEvent &WXUNUSED(event))
{
    wxPaintDC pdc(this);

    // A white background
    pdc.SetBackground(*wxWHITE_BRUSH);
    pdc.SetBackgroundMode(wxPENSTYLE_SOLID);
    pdc.Clear();

    // Draw a blue line from (50,100) to (100,100) using DrawPoint
    pdc.SetPen(*wxBLUE_PEN);
    for (int i = 50; i <= 100; i++) {
        pdc.DrawPoint(i, 100);
    }

    // A single point (blue)
    pdc.DrawPoint(25, 25);

    // DrawLine in red from (0,100) to (50,100)
    // This should meet up with the blue line drawn above.
    pdc.SetPen(*wxRED_PEN);
    pdc.DrawLine(0, 100, 50, 100);
}

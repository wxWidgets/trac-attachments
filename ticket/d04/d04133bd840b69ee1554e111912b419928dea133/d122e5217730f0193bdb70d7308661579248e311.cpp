#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/timer.h"

// Define a new application type, each program should derive a class from wxApp
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
    MyFrame(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnTimer1(wxTimerEvent& event);
    void OnTimer2(wxTimerEvent& event);

private:
    wxTextCtrl *text;
    wxTimer *m_timer1;
    wxTimer *m_timer2;
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
};

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_TIMER(2011, MyFrame::OnTimer1)
    EVT_TIMER(2013, MyFrame::OnTimer2)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // create the main application window
    MyFrame *frame = new MyFrame(_T("Minimal wxWidgets App"));
    frame->Show(true);
    return true;
}

// frame constructor
MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
    text = new wxTextCtrl( this, -1, wxT(""), wxPoint(0,0), wxSize(300, 300), wxTE_MULTILINE );
    text->SetBackgroundColour( wxT("wheat"));
    wxLog::SetActiveTarget( new wxLogTextCtrl( text ));

    m_timer1 = new wxTimer( this, 2011 );
    m_timer2 = new wxTimer( this, 2013 );

    m_timer1->Start( 10000 );
    m_timer2->Start( 2000 );
}

// event handlers

void MyFrame::OnTimer1(wxTimerEvent& event)
{
    wxLogMessage("Timer1");
}

void MyFrame::OnTimer2(wxTimerEvent& event)
{
    wxLogMessage("Timer2");
}


 	  	 

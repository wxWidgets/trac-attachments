// ----------------------------------------------------------------------------
// Demonstration program for wxTipWindow preventing double-clicks events
// to happen if shown
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
    #include "wx/tipwin.h"
#endif

enum {
    TTT_ID = 1234	// tooltip timer id
};

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

// Define a new frame type: this is going to be our main widget
class MyTextCtrl : public wxTextCtrl
{
public:
    MyTextCtrl(wxWindow* parent);
    ~MyTextCtrl();

    void OnMouse(wxMouseEvent&);
    void OnTimer(wxTimerEvent&);

private:
    wxTimer*     mTimer;
    wxTipWindow* mTipWindow;

    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyTextCtrl, wxTextCtrl)
    EVT_MOUSE_EVENTS(	MyTextCtrl::OnMouse)
    EVT_TIMER(TTT_ID,	MyTextCtrl::OnTimer)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    if (!wxApp::OnInit()) return false;

    wxFrame* frame = new wxFrame(NULL, wxID_ANY, "test: wxTipWindow + DClick");
    new MyTextCtrl(frame);
    frame->Show(true);
    return true;
}

MyTextCtrl::MyTextCtrl(wxWindow* parent)
    : wxTextCtrl(
	    parent,
	    wxID_ANY,
	    wxEmptyString,
	    wxDefaultPosition,
	    wxDefaultSize,
	    wxTE_LEFT|wxTE_READONLY|wxTE_MULTILINE
	    )
{
    mTimer = new wxTimer(this, TTT_ID); // will be started in OnMouse handler
    mTipWindow = NULL;
}

MyTextCtrl::~MyTextCtrl() {
    delete mTimer;
}

void MyTextCtrl::OnMouse(wxMouseEvent& event)
{
    mTimer->Start(700/*ms*/, TRUE/*one-shot timer*/);
    if (!event.Moving()) mTimer->Stop();

    if      (event.ButtonDown())   AppendText("event.ButtonDown()\n");
    else if (event.ButtonUp())     AppendText("event.ButtonUp()\n");
    else if (event.ButtonDClick()) AppendText("event.ButtonDClick()\n");
}

void MyTextCtrl::OnTimer(wxTimerEvent& WXUNUSED(event))
{
    if (!mTipWindow) {
	mTipWindow = new wxTipWindow(this,"try double-click!",200,&mTipWindow);
    }
}

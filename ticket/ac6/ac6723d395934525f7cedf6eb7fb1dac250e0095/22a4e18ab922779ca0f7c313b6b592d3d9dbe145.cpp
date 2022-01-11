// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------
// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;
};

class LastFocusTestFrame;

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title);

    void OnPushChildButton(wxCommandEvent& event);

private:
    LastFocusTestFrame *frame1;
    LastFocusTestFrame *frame2;
};

// child frame
class LastFocusTestFrame : public wxFrame
{
public:
    // ctor(s)
    LastFocusTestFrame(wxWindow *parent, const wxString& title, wxPoint pos);

    void CreateButton ();   

    wxButton *bttnFocusChild;
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

    wxIMPLEMENT_APP(MyApp);

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
	return false;

    // create the main application window
    MyFrame *frame = new MyFrame("Minimal wxWidgets App");   
    frame->Show(true);
    return true;
}

// frame constructor
MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize (10, 10))
{
    frame1 = new LastFocusTestFrame (this, "Frame 1", wxPoint (0, 0));
    frame2 = new LastFocusTestFrame (this, "Frame 2", wxPoint (350, 0));
    frame1->CreateButton ();
}

// callback on child window button click
void MyFrame::OnPushChildButton (wxCommandEvent& WXUNUSED(event))
{
    LastFocusTestFrame *next, *prev;
    if (frame1->bttnFocusChild == NULL && frame2->bttnFocusChild == NULL)
	return;
    if (frame1->bttnFocusChild != NULL)
    {
	next = frame2;
	prev = frame1;
    }
    else
    {
	next = frame1;
	prev = frame2;
    }

    next->SetFocus ();
    next->CreateButton ();

    // When the button "bttnFocusChild" had focus on "prev", neither the "Reparent" nor "Destroy" call resets the "m_winLastFocused" member pointer in  
    // "wxTopLevelWindowMSW". This causes a program crash, when the user activates the prev frame later again because wxWidgets can't
    // restore focus to the deleted button.

//   ugly workaround: uncomment the following 2 lines to reset "m_winLastFocused" manually. This is a low level MSW call which should not be done by the wxWidgets user.
//   if (prev->GetLastFocus () == prev->bttnFocusChild)
//	prev->SetLastFocus (NULL);

    // There are no problems, if you comment out only "Reparent" or "Destroy". But the combination of both does not work
    prev->bttnFocusChild->Reparent (this);
    // ...
    // }
    // do something with the control on its new parent
    // ...
    // {
    // now it is not needed anymore, so destroy it
    prev->bttnFocusChild->Destroy ();
    prev->bttnFocusChild = NULL;

//     possible solutions in wxWidgets:
//     1. Find the top level parent window of "bttnFocusChild" inside "Reparent" function and reset its "m_winLastFocused" member, if it equals "bttnFocusChild".
//     2. Check the "m_winLastFocused" member of all top level windows inside "Destroy" function and reset them, if they equals "bttnFocusChild".
//     3. Check with the "IsBeingDeleted" function, if the window "childLastFocused" still exists in the "wxSetFocusToChild" function in containr.cpp. But I am not sure, if this will work for a deleted object. 
}


// child frame constructor
LastFocusTestFrame::LastFocusTestFrame(wxWindow *parent, const wxString& title, wxPoint pos)
    : wxFrame(parent, wxID_ANY, title, pos, wxSize (150, 300))
    , bttnFocusChild (NULL)
{
    Show (true);
}

// create button as child window
void LastFocusTestFrame::CreateButton ()
{
    bttnFocusChild = new wxButton (this, wxID_ANY, "Please click me!", wxPoint (), wxSize (150, 300));
    bttnFocusChild->Bind (wxEVT_COMMAND_BUTTON_CLICKED, &MyFrame::OnPushChildButton, dynamic_cast<MyFrame *> (GetParent ()));    
}

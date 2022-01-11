#include "wx/wx.h"
#include <stdio.h>

class MyApp: public wxApp
{
    virtual bool OnInit();
};

class MyScrolledWindow: public wxScrolledWindow
{
public:

	MyScrolledWindow(wxWindow *parent);

    void OnScrollWin(wxScrollWinEvent& event);

    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyScrolledWindow, wxScrolledWindow)
    EVT_SCROLLWIN(MyScrolledWindow::OnScrollWin)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	wxFrame *frame = new wxFrame(NULL, -1, _("Hello World"), wxPoint(50,50), wxSize(400,400) );

	MyScrolledWindow *scrolledWin = new MyScrolledWindow(frame);
    scrolledWin->SetScrollbars(1, 1, 1000, 1000, 300, 300);

    frame->Show(true);
    SetTopWindow(frame);

    return true;
}

MyScrolledWindow::MyScrolledWindow(wxWindow *parent)
: wxScrolledWindow( parent )
{
	wxStaticText *text = new wxStaticText(this, -1, "This should scroll...");
}

void MyScrolledWindow::OnScrollWin(wxScrollWinEvent& event)
{
    printf("Caught event: pos=%d orient=%d\n", event.GetPosition(), event.GetOrientation());
    event.Skip();
}


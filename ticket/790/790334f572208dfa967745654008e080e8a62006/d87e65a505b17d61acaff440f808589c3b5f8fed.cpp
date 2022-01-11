// hworld.cpp
// Version using dynamic event routing

#include <wx/wx.h>

class MyApp : public wxApp
{
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)


class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

enum
{
    ID_About=1
};


bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( _("Hello World"), wxPoint(50, 50),
                                  wxSize(450, 350));

    frame->Connect( ID_About, wxEVT_COMMAND_MENU_SELECTED,
                    (wxObjectEventFunction) &MyFrame::OnAbout );

    frame->Show(true);
    SetTopWindow(frame);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame( NULL, -1, title, pos, size )
{
    wxMenuBar *menuBar = new wxMenuBar;

    wxMenu *menuFile = new wxMenu;

    menuFile->Append( ID_About, _("&Display error message") );

    menuBar->Append(menuFile, _("&File") );

    SetMenuBar(menuBar);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxLogError("this is the error message");
    exit(1);	// quits application before showing the message
    
    // this does not show message either, but quits the app
    //wxLogError("this is the error message");
}



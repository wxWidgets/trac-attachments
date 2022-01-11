// hworld.cpp
// Version using dynamic event routing

#include <wx/wx.h>
#include <wx/log.h>
#include <wx/memory.h>

class MyApp : public wxApp
{
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)


class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnMenu(wxEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

enum
{
    ID_Quit=1,
    ID_About
};


bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( _("Hello World"), wxPoint(50, 50),
                                  wxSize(450, 350));

    frame->Connect( ID_Quit, wxEVT_COMMAND_MENU_SELECTED,
                    (wxObjectEventFunction) &MyFrame::OnQuit );
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

    menuFile->Append( ID_About, _("&About...") );
    menuFile->AppendSeparator();
    menuFile->Append( ID_Quit, _("E&xit") );

    menuFile->Connect( wxEVT_MENU_HIGHLIGHT, wxEventHandler( MyFrame::OnMenu ), NULL, this );
    menuFile->Connect( wxEVT_COMMAND_MENU_SELECTED, wxEventHandler( MyFrame::OnMenu ), NULL, this );
    menuFile->Connect( wxEVT_MENU_CLOSE, wxEventHandler( MyFrame::OnMenu ), NULL, this );

    menuBar->Append(menuFile, _("&File") );

    SetMenuBar(menuBar);

    CreateStatusBar();
        
    SetStatusText( _("Welcome to wxWidgets!") );
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox( _("wxWidgets Hello World example."), 
                  _("About Hello World"),
                  wxOK|wxICON_INFORMATION, this );
}

void MyFrame::OnMenu(wxEvent& event)
{
    if(event.GetEventType() == wxEVT_MENU_HIGHLIGHT )
	wxLogDebug( "highlight" );
    else if(event.GetEventType() == wxEVT_MENU_CLOSE )
	wxLogDebug( "close" );
    else if(event.GetEventType() == wxEVT_COMMAND_MENU_SELECTED )
	wxLogDebug( "selected" );
}


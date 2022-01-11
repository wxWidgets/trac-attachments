#include "wx/wxprec.h"
#include "wx/filename.h"

#define FLAGS wxEXEC_SYNC|wxEXEC_HIDE_CONSOLE

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
    #include "sample.xpm"
#endif

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    Minimal_Quit = wxID_EXIT,
    Minimal_About = wxID_ABOUT,
    Create_Sample_Dir,
    Rmdir_Sample_Dir,
    Minimal_LogWindow,
};

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

class MyDialog : public wxDialog
{
public:
    MyDialog(const wxString& title);

    void OnStartCreateDir(wxCommandEvent& event);
    void OnStartRmdirDir(wxCommandEvent& event);

private:
    DECLARE_EVENT_TABLE()
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
    virtual ~MyFrame();

    void OnQuit(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnStartCreateDir(wxCommandEvent& event);
    void OnStartRmdirDir(wxCommandEvent& event);

private:
    wxTextCtrl *m_logWin;
    wxLog *m_logOld;
    DECLARE_EVENT_TABLE()
};

class MyApp : public wxApp
{
public:
    virtual bool OnInit();

    MyFrame *m_frame;
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------


IMPLEMENT_APP(MyApp)

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    // create the main application window
    m_frame = new MyFrame(wxT("Rmdir Problem Demonstration App"));

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    m_frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
    EVT_BUTTON(Create_Sample_Dir, MyFrame::OnStartCreateDir)
    EVT_BUTTON(Rmdir_Sample_Dir, MyFrame::OnStartRmdirDir)
    EVT_CLOSE(MyFrame::OnClose)
END_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1000,600))
{
    SetIcon(wxICON(sample));

#if wxUSE_MENUS
    wxMenu *menuFile = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, wxT("&About\tF1"), wxT("Show about dialog"));

    menuFile->Append(Minimal_Quit, wxT("E&xit\tAlt-X"), wxT("Quit this program"));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, wxT("&File"));
    menuBar->Append(helpMenu, wxT("&Help"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(wxT("Rmdir problem demonstration program"));
#endif // wxUSE_STATUSBAR

    wxPanel *panel = new wxPanel(this, -1);
    wxButton *button1 = new wxButton( panel, Create_Sample_Dir, wxT("Create dir w/dir symbolic link"), wxPoint(20,20) );
    wxButton *button2 = new wxButton( panel, Rmdir_Sample_Dir, wxT("Call wxFilenName::Rmdir on that dir"), wxPoint(20,70) );

    m_logWin = new wxTextCtrl( panel, wxID_ANY, wxEmptyString, wxDefaultPosition,
                               wxDefaultSize, wxTE_MULTILINE );
    m_logWin->SetEditable(false);
    wxLogTextCtrl* logger = new wxLogTextCtrl( m_logWin );
    m_logOld = logger->SetActiveTarget( logger );
    logger->DisableTimestamp();

    wxBoxSizer *topSizer = new wxBoxSizer( wxVERTICAL );
    topSizer->Add( button1, 0, wxALL, 5 );
    topSizer->Add( button2, 0, wxALL, 5 );
    topSizer->Add( m_logWin, 1, wxEXPAND|wxALL, 5 );

    panel->SetSizer( topSizer );

}

MyFrame::~MyFrame()
{
    delete wxLog::SetActiveTarget(m_logOld);
}


// event handlers

void MyFrame::OnStartCreateDir(wxCommandEvent& WXUNUSED(event))
{
    wxLogMessage( wxT("=========================") );
    wxLogMessage( wxT("Create /tmp/rmdir_problem_dir Dir") );
    wxString fn = wxT("/tmp/rmdir_problem_dir");
    if ( !wxFileName::DirExists(fn) )
    {
        wxExecute("mkdir /tmp/rmdir_problem_dir",FLAGS);
    }
    wxLogMessage( wxT("Create /tmp/rmdir_problem_dir/file_should_remain File") );
    fn = wxT("/tmp/rmdir_problem_dir/file_should_remain");
    if ( !wxFileName::FileExists(fn) )
    {
        wxExecute("touch /tmp/rmdir_problem_dir/file_should_remain",FLAGS);
    }
    wxLogMessage( wxT("Create /tmp/rmdir_problem_dir_with_dir_link Dir") );
    fn = wxT("/tmp/rmdir_problem_dir_with_dir_link");
    if ( !wxFileName::DirExists(fn) )
    {
        wxExecute("mkdir /tmp/rmdir_problem_dir_with_dir_link",FLAGS);
    }
    wxLogMessage( wxT("Symbolic link /tmp/rmdir_problem_dir_with_dir_link/to_rmdir_problem_dir to /tmp/rmdir_problem_dir Dir") );
    fn = wxT("/tmp/rmdir_problem_dir_with_dir_link/to_rmdir_problem_dir");
    if ( !wxFileName::DirExists(fn) )
    {
        wxExecute("ln -s /tmp/rmdir_problem_dir /tmp/rmdir_problem_dir_with_dir_link/to_rmdir_problem_dir",FLAGS);
    }
    wxLogMessage( wxT("") );
}

void MyFrame::OnStartRmdirDir(wxCommandEvent& WXUNUSED(event))
{
    wxLogMessage( wxT("=========================") );
    wxString fn = wxT("/tmp/rmdir_problem_dir_with_dir_link/to_rmdir_problem_dir");
    wxLogMessage( wxT("wxFileName::Rmdir(/tmp/rmdir_problem_dir_with_dir_link/to_rmdir_problem_dir, 0)") );
    wxFileName::Rmdir(fn, 0);
    if ( !wxFileName::DirExists(fn) )
    {
        wxExecute("ln -s /tmp/rmdir_problem_dir /tmp/rmdir_problem_dir_with_dir_link/to_rmdir_problem_dir",FLAGS);
    }
    wxLogMessage( wxT("") );
    fn = wxT("/tmp/rmdir_problem_dir_with_dir_link");
    wxLogMessage( wxT("wxFileName::Rmdir(/tmp/rmdir_problem_dir_with_dir_link, wxPATH_RMDIR_RECURSIVE)") );
    wxFileName::Rmdir(fn, wxPATH_RMDIR_RECURSIVE);
    wxLogMessage( wxT("") );
    fn = wxT("/tmp/rmdir_problem_dir/file_should_remain");
    if ( !wxFileName::FileExists(fn) )
    {
        wxLogMessage( wxT("/tmp/rmdir_problem_dir/file_should_remain has been incorrectly deleted") );
        wxLogMessage( wxT("") );
        wxLogMessage( wxT("/tmp/rmdir_problem_dir_with_dir_link has not been deleted because to_rmdir_problem_dir symbolic link was not correctly deleted") );
        wxLogMessage( wxT("") );
    }
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    wxExecute("rm -fr /tmp/rmdir_problem_dir",FLAGS);
    wxExecute("rm -fr /tmp/rmdir_problem_dir_with_dir_link",FLAGS);
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnClose(wxCloseEvent& event)
{
    wxExecute("rm -fr /tmp/rmdir_problem_dir",FLAGS);
    wxExecute("rm -fr /tmp/rmdir_problem_dir_with_dir_link",FLAGS);
    event.Skip();
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( wxT("This is the About dialog of the Rmdir problem app.\n")
                wxT("Welcome to %s"), wxVERSION_STRING);

    wxMessageBox(msg, wxT("About Rmdir Problem Demonstration"), wxOK | wxICON_INFORMATION, this);
}

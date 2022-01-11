#include "wx/wxprec.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

bool g_OnExitCalled=false;

// create a global object so that we can see when the global destructors are called:
class DummyObj
{
public:
    virtual ~DummyObj()
    {
        printf("global objects cleanup\n");
        wxASSERT_MSG(g_OnExitCalled, "Global cleanup while wxApp::OnExit was not called");
    }
};
DummyObj g_Dummyobj;


class MyApp : public wxApp
{
public:
    void OnQuit(wxCommandEvent &event)
    {
        printf("Application menu wxID_EXIT\n");
        ExitMainLoop();
    }
    virtual bool OnInit()
    {
        printf("MyApp::OnInit\n");
        if ( !wxApp::OnInit() )
            return false;

        // Create a global application menu bar with Quit item:
        wxMenu *fileMenu = new wxMenu;
        fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
        wxMenuBar *menuBar = new wxMenuBar();
        menuBar->Append(fileMenu, "&File");
        Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction) (wxEventFunction)(wxCommandEventFunction) &MyApp::OnQuit);
        wxMenuBar::MacSetCommonMenuBar(menuBar);

        wxApp::SetExitOnFrameDelete(false);

        // uncomment to test with main window:
        // (new wxFrame(NULL, wxID_ANY, "test frame"))->Show(true);
        // wxApp::SetExitOnFrameDelete(true);

        return true;
        
    }
    virtual int OnExit()
    {
        g_OnExitCalled=true;
        printf("MyApp::OnExit\n");
        return wxApp::OnExit();
    }
    virtual ~MyApp()
    {
        printf("~MyApp\n");
    }
    MyApp()
    {
        printf("MyApp constructor\n");
    }
};

IMPLEMENT_APP(MyApp)

/**********************************************************************
A source file to demonstrate re-entry problems - dangling pointer 
"gs_fontDefault" in src/msw/settings.cpp

Run this code in the Visual C++ 6.0 debugger to recreate
the error.
SOLUTION: Add "gs_fontDefault = NULL;" to wxSystemSettingsModule::OnExit()
**********************************************************************/

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

/** Main wxWindows application */
class MyApp: public wxApp
{
public:
  virtual bool OnInit();
};

/** Primary frame in the wxApp */
class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnQuit(wxCommandEvent& event);
private:
    DECLARE_EVENT_TABLE()
};

/** frame event enum */
enum
{
    ID_Quit = 1,
};

/** frame events */
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Quit,  MyFrame::OnQuit)
END_EVENT_TABLE()


bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Hello World", wxPoint(50,50), wxSize(450,340) );
    frame->Show( TRUE );
    SetTopWindow( frame );
    return TRUE;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, -1, title, pos, size) 
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append( ID_Quit, "E&xit" );

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );

    SetMenuBar( menuBar );
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close( TRUE );
}

// setup the main wx application
IMPLEMENT_APP_NO_MAIN(MyApp);

int main() {
    // Closing the window created below will allow wxEntry to return
    // It calls wxTheApp->onExit() and wxApp::Cleanup()
    wxEntry(NULL, NULL, "", SW_SHOWNORMAL);

    // This fails due the dangling pointer gs_fontDefault
    wxEntry(NULL, NULL, "", SW_SHOWNORMAL);

    return 0;
}
 	  	 

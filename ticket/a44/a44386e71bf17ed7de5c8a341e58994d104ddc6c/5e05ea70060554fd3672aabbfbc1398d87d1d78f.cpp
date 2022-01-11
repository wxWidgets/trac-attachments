#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/filedlg.h>


//#include "sample.xpm"


/*
 * Aux
 */

void auxReopenStdout()
{
    /*
    int s = open("/tmp/out", O_RDWR | O_CREAT | O_TRUNC);
    if (s < 0) return;
   
    dup2(s, 0);
    dup2(s, 1);
    dup2(s, 2);
     */
}


/*
 * Application
 */
class mouseTestApp : public wxApp
    {
    public:
        virtual bool OnInit();
    };


/*
 * Frame
 */
class mouseTestFrame : public wxFrame
    {
    public:
        mouseTestFrame(const wxString& title);
       
        void OnQuit(wxCommandEvent& event);
        void OnKeyDown(wxKeyEvent& event);
        void OnSize(wxSizeEvent& event);
        void OnMouseLeftDown(wxMouseEvent& event);
        void OnMouseDragging(wxMouseEvent& event);
        void OnMouse(wxMouseEvent& event);
       
    private:
        DECLARE_EVENT_TABLE()
    };


/*
 * Menu command ID's
 */
enum
{
    MTEST_Quit = wxID_EXIT,
    MTEST_FileOpen,
};


BEGIN_EVENT_TABLE(mouseTestFrame, wxFrame)
EVT_MENU(MTEST_Quit,  mouseTestFrame::OnQuit)
EVT_SIZE(               mouseTestFrame::OnSize) // This is it
EVT_KEY_DOWN(           mouseTestFrame::OnKeyDown)
EVT_MOUSE_EVENTS(       mouseTestFrame::OnMouse)
END_EVENT_TABLE()

IMPLEMENT_APP(mouseTestApp)

/*
 * main
 */
bool mouseTestApp::OnInit()
{
    auxReopenStdout();
   
    if (!wxApp::OnInit())
        return false;
   
    //wxImage::AddHandler(new wxPNGHandler); // initialize PNG
    //wxInitAllImageHandlers();
   
    // create the main application window
    mouseTestFrame *frame = new mouseTestFrame(_T("Mouse test"));
    frame->SetClientSize(1000, 700);
    frame->Show(true);
   
    return true;
}

/*
 * mouseTestFrame
 */
mouseTestFrame::mouseTestFrame(const wxString& title)
:wxFrame(NULL, wxID_ANY, title)
{
   printf("Test frame is at %x\n", this);
    wxMenu *fileMenu = new wxMenu;
    wxMenu *helpMenu = new wxMenu;
   
    fileMenu->Append(MTEST_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));
   
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(helpMenu, _T("&Help"));
   
    SetMenuBar(menuBar);
   
    wxPanel* main_pane = new wxPanel( this, wxID_ANY );
printf("Panel is at %x\n", main_pane);
    main_pane->Connect(wxEVT_MOTION, wxMouseEventHandler(mouseTestFrame::OnMouse));
    main_pane->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(mouseTestFrame::OnMouse));
    main_pane->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(mouseTestFrame::OnMouse));
    main_pane->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(mouseTestFrame::OnKeyDown));
   
    CreateStatusBar(2);
    SetStatusText(_T("Started."));
}


void mouseTestFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void mouseTestFrame::OnMouseLeftDown(wxMouseEvent& event)
{
    return event.Skip();
}


void mouseTestFrame::OnMouseDragging(wxMouseEvent& event)
{
   
    if (event.Dragging()) {
        printf("Dragging\n");
    }
    if (event.LeftIsDown()) {
        printf("Left is down\n");
    }
    printf("----\n");fflush(stdout);
   
    return;
   
    if (event.Dragging() && event.LeftIsDown()) {
    }
}


void mouseTestFrame::OnMouse(wxMouseEvent& event)
{
    printf("Just mouse event\n"); fflush(stdout);
   
    if (event.LeftDown()) {
        printf("LMB down!\n");
        return OnMouseLeftDown(event);
    }
    if(event.LeftUp()) printf("LMB up!\n");
    if (event.Dragging()) {
        return OnMouseDragging(event);
    }
   
    return event.Skip();
}


void mouseTestFrame::OnKeyDown(wxKeyEvent& event)
{
    printf("Key Down in %x\n", this); fflush(stdout);
    return event.Skip();
} 

void mouseTestFrame::OnSize(wxSizeEvent& WXUNUSED(event))
{
   int sx, sy;
   GetClientSize(&sx, &sy);
}
   

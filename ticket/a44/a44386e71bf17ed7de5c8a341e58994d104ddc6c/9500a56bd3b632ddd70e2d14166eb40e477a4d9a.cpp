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
       
    private:
        DECLARE_EVENT_TABLE()
    };


class mouseTestPanel : public wxPanel
{
public:
    mouseTestPanel( wxWindow* parent ) : wxPanel( parent )
    {
    }
    
        void OnKeyDown(wxKeyEvent& event);
        void OnSize(wxSizeEvent& event);
        void OnMouseLeftDown(wxMouseEvent& event);
        void OnMouseDragging(wxMouseEvent& event);
        void OnMouse(wxMouseEvent& event);

    private:
        DECLARE_EVENT_TABLE()

} ;

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
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(mouseTestPanel, wxPanel)
EVT_SIZE(               mouseTestPanel::OnSize) // This is it
EVT_KEY_DOWN(           mouseTestPanel::OnKeyDown)
EVT_MOUSE_EVENTS(       mouseTestPanel::OnMouse)
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
   
    mouseTestPanel* main_pane = new mouseTestPanel( this );
printf("Panel is at %x\n", main_pane);
    CreateStatusBar(2);
    SetStatusText(_T("Started."));
}


void mouseTestFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void mouseTestPanel::OnMouseLeftDown(wxMouseEvent& event)
{
    // if Mouse down is not handled, the complete mouse handling will be passed to the native TrackControl
    // no further dragging or up events will be delivered
    //    return event.Skip();
}


void mouseTestPanel::OnMouseDragging(wxMouseEvent& event)
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


void mouseTestPanel::OnMouse(wxMouseEvent& event)
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


void mouseTestPanel::OnKeyDown(wxKeyEvent& event)
{
    printf("Key Down in %x\n", this); fflush(stdout);
    return event.Skip();
} 

void mouseTestPanel::OnSize(wxSizeEvent& WXUNUSED(event))
{
   int sx, sy;
   GetClientSize(&sx, &sy);
}
   

#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/filedlg.h>


#include "sample.xpm"


/*
 * Aux
 */
void auxReopenStdout()
{
   int s = open("/tmp/out", O_RDWR | O_CREAT | O_TRUNC);
   if (s < 0) return;

   dup2(s, 0);
   dup2(s, 1);
   dup2(s, 2);
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
   MAPVIEW_Quit = wxID_EXIT,
   MAPVIEW_FileOpen,
};


BEGIN_EVENT_TABLE(mouseTestFrame, wxFrame)
   EVT_MENU(MAPVIEW_Quit,  mouseTestFrame::OnQuit)
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
   wxInitAllImageHandlers();

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
   wxMenu *fileMenu = new wxMenu;
   wxMenu *helpMenu = new wxMenu;

   fileMenu->Append(MAPVIEW_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));

   wxMenuBar *menuBar = new wxMenuBar();
   menuBar->Append(helpMenu, _T("&Help"));

   SetMenuBar(menuBar);

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
      return OnMouseLeftDown(event);
   }
   if (event.Dragging()) {
      return OnMouseDragging(event);
   }

   return event.Skip();
}


void mouseTestFrame::OnKeyDown(wxKeyEvent& event)
{
   printf("Key Down\n"); fflush(stdout);
   return event.Skip();
}



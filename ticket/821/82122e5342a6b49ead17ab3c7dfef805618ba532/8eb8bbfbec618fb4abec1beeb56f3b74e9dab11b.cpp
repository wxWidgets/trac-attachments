#include "wx/wxprec.h"
#include "wx/wx.h"

int g_scrnH, g_scrnW;
bool g_bUsrActn = false;

class MyCanvas;
class MyFrame : public wxFrame
{
public:
  MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
  MyCanvas   *m_canvas;
private:
};

class MyApp : public wxApp
{
public:
  virtual bool OnInit() wxOVERRIDE;
  virtual int OnExit() wxOVERRIDE { return 0; }
};
wxIMPLEMENT_APP(MyApp);

class MyCanvas : public wxWindow
{
public:
  MyCanvas( MyFrame *parent, wxSize size );
  void OnPaint(wxPaintEvent &event);
  void OnKeyDown(wxKeyEvent &event);
private:
  MyFrame *m_owner;
  wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyCanvas, wxWindow)
  EVT_PAINT  (MyCanvas::OnPaint)
EVT_KEY_DOWN (MyCanvas::OnKeyDown)
wxEND_EVENT_TABLE()


bool MyApp::OnInit()
{
  if ( !wxApp::OnInit() )
    return false;

  g_scrnW = wxSystemSettings::GetMetric(wxSYS_SCREEN_X,NULL);
  g_scrnH = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y,NULL)-20;
  
  MyFrame *frame = new MyFrame("hex-draw", wxPoint(0,0), wxSize(g_scrnW, g_scrnH));
  frame->Show(true);
  frame->ShowFullScreen(true, wxFULLSCREEN_NOSTATUSBAR );
  return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, wxID_ANY, title, pos, size)
{
    EnableFullScreenView();
    m_canvas = new MyCanvas( this, size );
}

MyCanvas::MyCanvas(MyFrame *parent, wxSize size )
        : wxWindow(parent, wxID_ANY, wxPoint( 0, 0 ), size )
{
    m_owner = parent;
}

void MyCanvas::OnPaint(wxPaintEvent &WXUNUSED(event))
{
  wxPaintDC *pdc = new wxPaintDC(this);
  int width, height;

  // check if it's the intro or a response to a user action
  if( !g_bUsrActn )
  {
    pdc->DrawText("press space bar", g_scrnW/2, g_scrnH/2);
  }
  else // its a response to a user action
  {
    pdc->DrawText("you pressed space bar, press escape to exit", g_scrnW/2, g_scrnH/2);
//    wxMessageBox( "in wxEVT_PAINT handler",wxMessageBoxCaptionStr,wxOK|wxCENTRE,NULL,wxDefaultCoord,wxDefaultCoord );  
  }
  return;
}

void MyCanvas::OnKeyDown(wxKeyEvent &event)
{
  int keyCode = event.GetKeyCode();
  g_bUsrActn = true;
  
  switch( keyCode )
  {
    case 27:
      m_owner->Close( true );
      break;
    case 32:
      g_bUsrActn = true;
      Refresh( true, NULL );
      Update();
      break;
    default:
      break;
  }
  return;
}
// end wx boilerplate
// --------------------------------------------------------------- X ----------------------------------------------------------------

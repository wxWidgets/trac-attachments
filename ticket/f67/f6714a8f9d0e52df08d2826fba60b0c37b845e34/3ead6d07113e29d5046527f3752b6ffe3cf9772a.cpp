#include "wx/wxprec.h"
#include "wx/wx.h"

//screen
int g_scrnW;
int g_scrnH;

unsigned char * g_pucBG3 = NULL;
unsigned char * g_pucBGA = NULL;
wxMemoryDC *g_DCBackground;
wxImage g_imageBackground;
wxBitmap g_bitmapBackground;

unsigned char * g_pucFG3 = NULL;
unsigned char * g_pucFGA = NULL;
wxMemoryDC *g_DCForeground;
wxImage g_imageForeground;
wxBitmap g_bitmapForeground;

bool g_bUsrActn = false;

class MyCanvas;

void draw_background( wxDC &DC );
void draw_foreground( int phase, MyCanvas *pCanvas, wxDC& DC );

enum {PH_INTENT, PH_EXECUTE};

class MyFrame : public wxFrame
{
public:
  MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
  MyCanvas   *m_canvas;
};

class MyCanvas : public wxWindow
{
public:
  MyCanvas( MyFrame *parent, wxSize size );
  void OnPaint(wxPaintEvent &event);
  void OnKeyDown(wxKeyEvent &event);
  void Close();
private:
  MyFrame *m_owner;
  wxDECLARE_EVENT_TABLE();
};
wxBEGIN_EVENT_TABLE(MyCanvas, wxWindow)
  EVT_PAINT  (MyCanvas::OnPaint)
EVT_KEY_DOWN (MyCanvas::OnKeyDown)
wxEND_EVENT_TABLE()

class MyApp : public wxApp
{
public:
  virtual bool OnInit() wxOVERRIDE;
};
wxIMPLEMENT_APP(MyApp);


//pb class definitions
bool MyApp::OnInit()
{
  wxString        str;

  if ( !wxApp::OnInit() )
    return false;      
  
  g_scrnW = wxSystemSettings::GetMetric(wxSYS_SCREEN_X,NULL);
  g_scrnH = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y,NULL)-20;
  
  // init the BG DC
  g_pucBG3 = (unsigned char *) malloc( g_scrnW * g_scrnH * 3 );
  g_pucBGA = (unsigned char *) malloc( g_scrnW * g_scrnH );
  
  unsigned char *pucT3 = g_pucBG3;
  unsigned char *pucTA = g_pucBGA;
  
  for( int i=0; i<g_scrnH; i++ )
  {
    for( int j=0; j<g_scrnW; j++ )
    {
      *pucT3++ = 255; *pucT3++ = 0; *pucT3++ = 0; // RED
      *pucTA++ = 255;
    }
  }
  g_imageBackground = wxImage( g_scrnW,
                    g_scrnH,
                    g_pucBG3,
                    g_pucBGA,
                    false
                     );
  g_bitmapBackground = wxBitmap( g_imageBackground, 32 );
  g_DCBackground = new wxMemoryDC( g_bitmapBackground );
 
  // init the FG DC
  g_pucFG3 = (unsigned char *) malloc( (g_scrnW/3) * (g_scrnH/3) * 3 );
  g_pucFGA = (unsigned char *) malloc( (g_scrnW/3) * (g_scrnH/3) );
  
  pucT3 = g_pucFG3;
  pucTA = g_pucFGA;
  
  for( int i=0; i<g_scrnH/3; i++ )
  {
    for( int j=0; j<g_scrnW/3; j++ )
    {
      *pucT3++ = 255; *pucT3++ = 255; *pucT3++ = 255; 
      *pucTA++ = 0; // transparent
    }
  }
  // draw a black outline
  pucT3 = g_pucFG3;
  pucTA = g_pucFGA;
  for( int i=0; i<g_scrnW/3; i++ )
  {
    *pucT3++ = 0; *pucT3++ = 0; *pucT3++ = 0; *pucTA++ = 255; // black outline
  }
  for( int j=0; j<g_scrnH/3-2; j++ )
  {
    *pucT3++ = 0; *pucT3++ = 0; *pucT3++ = 0; *pucTA++ = 255; // black outline
    pucT3 += ((g_scrnW/3)-2)*3; pucTA += (g_scrnW/3)-2;
    *pucT3++ = 0; *pucT3++ = 0; *pucT3++ = 0; *pucTA++ = 255; // black outline    
  }
  for( int i=0; i<g_scrnW/3; i++ )
  {
    *pucT3++ = 0; *pucT3++ = 0; *pucT3++ = 0; *pucTA++ = 255; // black outline
  }
  
  g_imageForeground = wxImage( g_scrnW/3,
                    g_scrnH/3,
                    g_pucFG3,
                    g_pucFGA,
                    false
                     );
  g_bitmapForeground = wxBitmap( g_imageForeground, 32 );
  g_DCForeground = new wxMemoryDC( g_bitmapForeground );
 

  MyFrame *frame = new MyFrame("minimal", wxPoint(0,0), wxSize(g_scrnW, g_scrnH));
  frame->Show(true);
  frame->ShowFullScreen( true,wxFULLSCREEN_NOSTATUSBAR );

  return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, wxID_ANY, title, pos, size)
{
  EnableFullScreenView();
  m_canvas = new MyCanvas( this, size );
  return;
}

MyCanvas::MyCanvas(MyFrame *parent, wxSize size )
        : wxWindow(parent, wxID_ANY, wxPoint( 0, 0 ), size )
{
    m_owner = parent;
}

void MyCanvas::Close()
{
  m_owner->Close( true );
}

void MyCanvas::OnPaint(wxPaintEvent &WXUNUSED(event))
{
  wxPaintDC DC(this);
  wxRect rectC;
  if( !g_bUsrActn )
  {
    draw_background( DC );
    DC.DrawText( "press escape to exit the app", g_scrnW/2, g_scrnH/2 );
  }
  else // its a response to a user action
  {
    draw_foreground( PH_EXECUTE, NULL, DC );
    g_bUsrActn = false;
  }
  return;
}

void MyCanvas::OnKeyDown(wxKeyEvent &event)
{
  wxMemoryDC DC; // this is a dummy variable
  g_bUsrActn = true;

  if( event.GetKeyCode() == WXK_ESCAPE )
  {
    Close();
  }
  else
  {
    draw_foreground( PH_INTENT, this, DC );
  }
}

void draw_background( wxDC &DC )
{
  DC.Blit( 0, 0, g_scrnW, g_scrnH, 
            g_DCBackground, 
            0, 0, 
            wxCOPY, false, wxDefaultCoord, wxDefaultCoord );
  return;
}

void draw_foreground( int phase, MyCanvas *pCanvas, wxDC& DC )
{
  static wxRect rect;
  
  rect.x = g_scrnW/3; rect.y = g_scrnH/3;
  rect.width = g_scrnW/3; rect.height = g_scrnH/3; 
  if( phase == PH_INTENT )
  {
    pCanvas->Refresh( false, &rect );
  }
  else // PH_EXECUTE
  {
    DC.Blit( rect.x, rect.y, rect.width, rect.height,
              g_DCForeground, 
              0, 0, 
              wxCOPY, false, wxDefaultCoord, wxDefaultCoord );
    
  }
}



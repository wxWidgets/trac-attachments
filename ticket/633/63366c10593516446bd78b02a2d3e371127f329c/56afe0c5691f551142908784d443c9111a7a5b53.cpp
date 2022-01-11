
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

class Main_Frame;

class Simple_App : public wxApp
{

public:

  Main_Frame* main_frame;

  Simple_App ();
  virtual ~Simple_App ();

  virtual bool OnInit ();
  virtual int OnExit ();

  DECLARE_EVENT_TABLE()
};

DECLARE_APP(Simple_App)


class Simple_Window : public wxWindow
{

public:

  Simple_Window();

protected:

  void OnExit (wxCommandEvent&);

  void OnPaint (wxPaintEvent&);
  void OnChar (wxKeyEvent& event);

  void OnEraseBackground (wxEraseEvent&);
  
public:

  DECLARE_EVENT_TABLE()
};

class Main_Frame : public wxFrame
{
  
public:

  Main_Frame (wxWindow *parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString &name);

public:
  
  Simple_Window* simple_window;

  Simple_App* simple_app;

public:

  DECLARE_EVENT_TABLE()

};


IMPLEMENT_APP(Simple_App) // creates instance of the Simple_App


BEGIN_EVENT_TABLE (Simple_App, wxApp)

END_EVENT_TABLE ()

// {{{ 
Simple_App::Simple_App()
  : main_frame (NULL)
  
{

}

// }}}
// {{{ 
Simple_App::~Simple_App()
{

}

// }}}

// {{{ 
bool Simple_App::OnInit ()
{
  //Args args (argc, argv);
  wxSize initial_size (800,600);
  
  main_frame = new Main_Frame (NULL,
                               wxID_ANY,
                               "Simple-WX",
                               wxDefaultPosition,
                               initial_size,
                               wxDEFAULT_FRAME_STYLE,
                               "Simple-WX mainframe");
  
  main_frame->simple_app = this;
  
  main_frame->Show (true);


  return true;
}

// }}}

// {{{ 
int Simple_App::OnExit ()
{
  return wxApp::OnExit ();
}

// }}}

// {{{ message map
BEGIN_EVENT_TABLE (Simple_Window, wxWindow)

  EVT_PAINT (Simple_Window::OnPaint)
  EVT_CHAR (Simple_Window::OnChar)
  
  EVT_MENU (wxID_EXIT,  Simple_Window::OnExit)

  EVT_ERASE_BACKGROUND(Simple_Window::OnEraseBackground)
  
END_EVENT_TABLE ()

// }}}

// {{{ 
Simple_Window::Simple_Window()
{
  
}

// }}}

// {{{ 
void Simple_Window::OnPaint (wxPaintEvent&)
{
  wxPaintDC dc (this);
 
  dc.SetBackground (*wxWHITE_BRUSH);
  dc.Clear ();
  
  dc.SetPen (*wxRED_PEN);
  dc.SetBrush (*wxTRANSPARENT_BRUSH);
  dc.DrawCircle (100, 100, 20);
  dc.DrawCircle (100, 100, 40);
  dc.DrawCircle (100, 100, 60);
  dc.DrawCircle (100, 100, 80);

}

// }}}
// {{{ 
void Simple_Window::OnChar (wxKeyEvent& event)
{
  wxClientDC dc (this);
  
  dc.SetPen (*wxBLUE_PEN);
  dc.SetBrush (*wxTRANSPARENT_BRUSH);
  dc.DrawCircle (100, 100, 21);
  dc.DrawCircle (100, 100, 41);
  dc.DrawCircle (100, 100, 61);
  dc.DrawCircle (100, 100, 81);
}

// }}}


// {{{ 
void Simple_Window::OnExit (wxCommandEvent&)
{
  Destroy ();
}

// }}}

// {{{ 
void Simple_Window::OnEraseBackground (wxEraseEvent&)
{
  
}

// }}}






// {{{ message map
BEGIN_EVENT_TABLE (Main_Frame, wxFrame)

END_EVENT_TABLE ()

// }}}

// {{{ 
Main_Frame::Main_Frame (wxWindow *parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString &name)
  : wxFrame(parent, id, title, pos, size, style, name),
    simple_window (NULL),
    simple_app (NULL)
{
  
  wxRect rect = GetClientRect ();
  
  rect.SetLeft   (rect.GetLeft ()  + 0);
  rect.SetTop    (rect.GetTop ()   + 0);
  rect.SetRight  (rect.GetRight () - 0);
  rect.SetBottom (rect.GetBottom ()- 0);
  
  
  simple_window = new Simple_Window;

  simple_window->Create (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS | wxBORDER_SUNKEN, "Simple window");
  simple_window->Show (true);

}

// }}}



#include <wx/wx.h>

class MyApp : public wxApp
{
  public:
	virtual bool OnInit();
};

class MyFrame : public wxFrame
{
  public:
	MyFrame( const wxChar *title, 
                int xpos, int ypos, 
                int width, int height);
};


IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  MyFrame
   *frame = new MyFrame("SetBackgroundColour test", 50, 50, 450, 300);

  frame->Show(TRUE);
  SetTopWindow(frame);
  return TRUE;	
}

MyFrame::MyFrame (const wxChar *title,
                    int xpos, int ypos,
                    int width, int height)
             : wxFrame
                ( (wxFrame *) NULL,
                   -1,
                   title,
                   wxPoint(xpos, ypos),
                   wxSize(width, height)
                )
{
  wxPanel *panel = new wxPanel(this, -1);
  panel->SetBackgroundColour(wxColour(255, 255, 255));
}

 	  	 

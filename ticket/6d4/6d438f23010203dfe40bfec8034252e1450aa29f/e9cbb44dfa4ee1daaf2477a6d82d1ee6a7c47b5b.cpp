#include "wx/wx.h"

class MyPanel : public wxPanel
{
public:
    MyPanel(wxWindow *parent) : wxPanel(parent) {}

    void OnPaint(wxPaintEvent&)
    {
        wxPaintDC dc(this);

	// left GREEN line
	dc.SetPen(*wxGREEN);
	dc.DrawLine(0,0,100,100);

	// RED text ...
	dc.SetTextForeground(*wxRED);
	dc.DrawText(_T("SetTextForeground(red)"), 70,50);


	// right GREEN line (appears RED now!)
	// Bug: line is painted in current text foreground color (RED)
	//      but the pen color seems to be OK (GREEN)
	dc.DrawLine(150,0,250,100);

	wxColour& c = dc.GetPen().GetColour();
	printf("pen color: R/G/B=%d/%d/%d\n", c.Red(), c.Green(), c.Blue());
    }

    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyPanel, wxPanel)
    EVT_PAINT(MyPanel::OnPaint)
END_EVENT_TABLE()


// -----------------------

class MyFrame : public wxFrame
{
public:
    MyFrame() : wxFrame(NULL, -1, _T("MOTIF Bug demonstrator"),
                 wxPoint(50, 50), wxSize(250, 120))
    {
	new MyPanel(this);
	Show();
    }
};

// ------------------

class MyApp : public wxApp
{
public:
    virtual bool OnInit() {
	new MyFrame;
	return true;
    }
};
IMPLEMENT_APP(MyApp)


 	  	 

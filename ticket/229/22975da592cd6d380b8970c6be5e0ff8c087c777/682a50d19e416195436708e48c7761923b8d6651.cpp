// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#endif

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};
class MyFrame : public wxFrame
{
public:
	MyFrame();
private:
	void OnPaint(wxPaintEvent& event);
};


wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame();
	frame->Show(true);
	return true;
}

MyFrame::MyFrame()
	: wxFrame(NULL, wxID_ANY, "Hello World")
{
        SetBackgroundColour(*wxYELLOW);
        SetBackgroundStyle(wxBG_STYLE_PAINT);
	Bind(wxEVT_PAINT, &MyFrame::OnPaint, this);
}


void MyFrame::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	double scale = 0.9999f; // creates default grey background
	// scale = 1.0; // creates correct yellow background

	dc.SetUserScale(scale, scale);
	dc.Clear();
}

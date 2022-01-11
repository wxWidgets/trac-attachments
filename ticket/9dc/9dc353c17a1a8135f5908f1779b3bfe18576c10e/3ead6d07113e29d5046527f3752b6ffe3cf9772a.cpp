#include <wx/wx.h>
#include "mondrian.xpm"

// with the value of 16 the program works inaccurately under MSW (at least at WinXP SP3 and Vista)
// the last zoomed horizontal line has width 12, not 16
//
// the value of 64 is an absolute disaster (the image gets truncated)
//
// values of 10 and 100 work fine
const int ZoomFactor = 16;

class Frame: public wxFrame
{
	public:
		Frame();
		wxBitmap bitmap;
};

class CanvasHolder: public wxScrolledWindow
{
	public:
		CanvasHolder(Frame *ownerFrame);
};

class Canvas: public wxWindow
{
	public:
		Canvas(CanvasHolder *parent, Frame *ownerFrame);
		void OnPaint(wxPaintEvent &event);
		void OnMouseMove(wxMouseEvent &event);
		void OnLeave(wxMouseEvent &event);
		Frame *owner;
	private:
		DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(Canvas, wxWindow)
	EVT_MOTION			(Canvas::OnMouseMove)
	EVT_PAINT			(Canvas::OnPaint)
	EVT_LEAVE_WINDOW	(Canvas::OnLeave)
END_EVENT_TABLE()

//---------------------------------- Canvas ----------------------------------------
Canvas::Canvas(CanvasHolder *parent, Frame *ownerFrame)
	: wxWindow(parent, wxID_ANY, wxPoint(0, 0), wxSize(ownerFrame->bitmap.GetWidth() * ZoomFactor, ownerFrame->bitmap.GetHeight() * ZoomFactor))
	, owner(ownerFrame)
{
	SetBackgroundColour(*wxWHITE);
}

void Canvas::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	wxMemoryDC memDC(owner->bitmap);
	dc.SetUserScale(ZoomFactor, ZoomFactor);
	dc.Blit(0, 0, owner->bitmap.GetWidth(), owner->bitmap.GetHeight(), &memDC, 0, 0);
}

void Canvas::OnMouseMove(wxMouseEvent &event)
{
	wxPoint point = event.GetPosition();
	wxString str;
	str.Printf(wxT("%d:%d"), point.x, point.y);
	owner->SetStatusText(str);
}

void Canvas::OnLeave(wxMouseEvent &event)
{
	owner->SetStatusText(wxT(""));
}


//-------------------------------- CanvasHolder ------------------------------------

CanvasHolder::CanvasHolder(Frame *ownerFrame)
	: wxScrolledWindow(ownerFrame, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL)
{
	new Canvas(this, ownerFrame);
	SetVirtualSize(ownerFrame->bitmap.GetWidth() * ZoomFactor, ownerFrame->bitmap.GetHeight() * ZoomFactor);
	SetScrollRate(ZoomFactor, ZoomFactor);
}


//---------------------------------- Frame -----------------------------------------

Frame::Frame()
	: wxFrame(0, -1, wxT("Buggy sample"))
	, bitmap(mondrian_xpm)
{
	SetIcon(wxIcon(mondrian_xpm));
	new CanvasHolder(this);
	CreateStatusBar();
	Maximize();
}

//----------------------------------- App ------------------------------------------
class App: public wxApp
{
	public:
		virtual bool OnInit();
};

bool App::OnInit()
{
	Frame *frame = new Frame;
	frame->Show(true);
	return true;
}

IMPLEMENT_APP(App)

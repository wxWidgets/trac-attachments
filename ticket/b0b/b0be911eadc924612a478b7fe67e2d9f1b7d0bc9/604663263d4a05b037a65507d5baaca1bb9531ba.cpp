#include <wx/wx.h>

// -- application --

class MyApp : public wxApp
{
public:
	bool OnInit();
};

DECLARE_APP(MyApp);
IMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{

public:
	MyFrame(wxFrame* parent,
			wxWindowID id,
			const wxString& title,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER);

private:
	int col;
	wxTimer m_timer;
	wxColour NewColour();

public:
	void OnTimer(wxTimerEvent& event) { NewColour(); }
	void OnPaint(wxPaintEvent& event);

	DECLARE_EVENT_TABLE();
};

bool MyApp::OnInit()
{
	wxFrame* frame = new MyFrame(NULL,
									wxID_ANY,
									wxT("Redraw Test"),
									wxDefaultPosition,
									wxSize(800, 600));
	SetTopWindow(frame);
	frame->Show();
	
	return true;
}

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_TIMER(-1, MyFrame::OnTimer)
	EVT_PAINT(MyFrame::OnPaint)
END_EVENT_TABLE()

MyFrame::MyFrame(
				wxFrame* parent,
				wxWindowID id,
				const wxString& title,
				const wxPoint& pos,
				const wxSize& size,
				long style)
		: wxFrame(parent, id, title, pos, size, style)
{
	// The presence of this line makes no difference
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	col =0;
	m_timer.Start(10);
}

wxColour MyFrame::NewColour()
{
	col++;
	wxColour c((col & 3)<<6, ((col>>2) & 3)<<6, ((col >>4) & 3)<<6);
	return c;
}

// Called when window needs to be repainted.
void MyFrame::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	dc.SetBrush(NewColour());
	dc.SetPen(*wxTRANSPARENT_PEN);
	
	wxRegionIterator upd(GetUpdateRegion()); // get the update rect list
	
	while (upd)
	{
		// Alternatively we can do this:
		wxRect rect(upd.GetRect());
		
		// Repaint this rectangle
		dc.DrawRectangle(rect.x, rect.y, rect.width, rect.height);
		
		upd ++ ;
	}
}

 	  	 

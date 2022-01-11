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
	wxWindow *m_ctrl;

};

class MyWindow : public wxWindow
{
public:
	MyWindow::MyWindow(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition,
						const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxPanelNameStr) : 
						col(0), m_timer(this, -1) , wxWindow(parent, id, pos, size, style, name) {m_timer.Start(10); }
private:
	int col;
	wxTimer m_timer;
	wxColour NewColour();

public:
	void OnTimer(wxTimerEvent& event);
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

BEGIN_EVENT_TABLE(MyWindow, wxWindow)
	EVT_TIMER(-1, MyWindow::OnTimer)
	EVT_PAINT(MyWindow::OnPaint)
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
	m_ctrl = new MyWindow(this, -1,
					wxDefaultPosition,
					wxSize(400,300));

	// The presence od this line makes no difference
	m_ctrl->SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

void MyWindow::OnTimer(wxTimerEvent& event)
{
	NewColour();
}

wxColour MyWindow::NewColour()
{
	col++;
	wxColour c((col & 3)<<6, ((col>>2) & 3)<<6, ((col >>4) & 3)<<6);
	return c;
}

// Called when window needs to be repainted.
void MyWindow::OnPaint(wxPaintEvent& event)
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

 	  	 

#include <wx/wx.h>

// This application demonstrates a bug in wxBrush handling.
// The application is meant to generate a different stipple bitmap on each rectangle
// redraw. wxDC::DrawText corrupts the gtk version of the stipple brush whilst leaving
// the wxBrush copy intact. This only seems to appear with stipple brushes.
// Merely saving and restoring the wxBrush around the wxDC::DrawText does not fix
// the problem, as in wx's view, the brush object is unchanged so no call is made
// to gdk to change the brush. In order to fix it, the brush must be changed
// before restore (to ensure the restore brush is definitively different)
//
// To illustrate the bug, load and run the program as is (2.6.3). Wiping a window
// over the screen will show nothing (black, here, though I've seen a hatch pattern).
// To restore the intended behaviour, uncomment the two "SetBrush" calls which
// should clearly do nothing.

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

	wxColour Colour1=NewColour();
	wxColour Colour2=NewColour();

	// Make up a stipple brush
	wxImage BrushImage(16,16);
	int x,y;
	for (y=0; y<16; y++) for (x=0; x<16; x++)
	{
		wxColour pixelcol=((x^y)&1)?Colour1:Colour2;
		BrushImage.SetRGB(x,y,pixelcol.Red(), pixelcol.Green(),pixelcol.Blue());
	}
	wxBitmap BrushBitmap(BrushImage);
	wxBrush StippleBrush(BrushBitmap);

	// Bug only occurs if we use a stipple brush, rather than a solid brush
	dc.SetBrush(StippleBrush);
//	dc.SetBrush(NewColour());

	dc.SetPen(*wxTRANSPARENT_PEN);

	wxBrush SaveBrush = dc.GetBrush();
	int SaveBackgroundMode = dc.GetBackgroundMode();

	// These lines will corrupt the current brush

	dc.SetFont(wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT));
	dc.SetBackgroundMode(wxTRANSPARENT);
	dc.SetTextForeground(*wxBLACK);
	dc.DrawText(wxString(_T("Hello")), 100, 100);

	// Restore the brush. First we have to ensure SetBrush really works. This is
	// because the GTK brush is corrupted whilst the wxWidgets one is still right.
	// So we have to select a different brush or wxWidgets will skip the call
	// that would otherwise fix the GTK brush
	dc.SetBackgroundMode(SaveBackgroundMode);

	// Uncommenting the following two lines fixes the bug
	// dc.SetBrush(*wxTRANSPARENT_BRUSH);
	// dc.SetBrush(wxNullBrush);

	dc.SetBrush(SaveBrush);
	
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

 	  	 

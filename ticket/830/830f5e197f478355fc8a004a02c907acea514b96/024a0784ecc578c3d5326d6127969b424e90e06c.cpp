#include <wx/app.h>
#include <wx/dcclient.h>
#include <wx/tipwin.h>
#include <wx/combobox.h>
#include <wx/button.h>
#include <wx/toolbar.h>
#include <wx/string.h>

class CToolTipTestApp : public wxApp
{
public:
	virtual bool OnInit();
};


class CToolTipTestFrame : public wxFrame
{
public:
	wxTipWindow * tip;
	wxComboBox * combo;
	CToolTipTestFrame();
	void onPaint(wxPaintEvent & event);
	void onMouseMoved(wxMouseEvent & event);
	DECLARE_EVENT_TABLE()
};

bool CToolTipTestApp::OnInit()
{
	CToolTipTestFrame * frame = new CToolTipTestFrame();
	frame->Show(true);
	SetTopWindow(frame);
	return true;
}

BEGIN_EVENT_TABLE(CToolTipTestFrame, wxFrame)
	EVT_PAINT(CToolTipTestFrame::onPaint)
	EVT_MOTION(CToolTipTestFrame::onMouseMoved)
END_EVENT_TABLE()

CToolTipTestFrame::CToolTipTestFrame() : wxFrame(NULL, wxID_ANY, wxString("test"))
{
	tip = NULL;
	CreateToolBar();
	wxButton * button = new wxButton(GetToolBar(), wxID_ANY, "test");
	button->SetToolTip("a test button");
	GetToolBar()->AddControl(button);
	GetToolBar()->AddControl(combo = new wxComboBox(GetToolBar(), wxID_ANY, "test", wxDefaultPosition, wxSize(200, 0)));
	GetToolBar()->Realize();
}

void CToolTipTestFrame::onPaint(wxPaintEvent & event)
{
	wxPaintDC dc(this);
	dc.BeginDrawing();
	dc.DrawRectangle(100, 100, 50, 50);
	dc.EndDrawing();
}

void CToolTipTestFrame::onMouseMoved(wxMouseEvent & event)
{
	wxPoint pt(100, 100);
	wxRect rect(ClientToScreen(pt), wxSize(50,50));
combo->SetValue(wxString::Format("test: %d, %d", ClientToScreen(event.GetPosition()).x, ClientToScreen(event.GetPosition()).y));
	if (rect.Inside(ClientToScreen(event.GetPosition())))
	{
		if (!tip)
		{
			tip = new wxTipWindow(this, "test", 100, & tip);
			tip->SetBoundingRect(rect);
		}
	}
	else
	{
//		if (tip)
//			delete tip;
//		tip = NULL;
	}
}

IMPLEMENT_APP(CToolTipTestApp);


 	  	 

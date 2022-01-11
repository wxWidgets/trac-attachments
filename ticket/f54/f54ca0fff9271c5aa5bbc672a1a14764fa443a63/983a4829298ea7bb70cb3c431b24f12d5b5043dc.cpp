#include "wx/wx.h"

class BugFrame : public wxFrame
{
public:
	BugFrame();

private:
	void sizing(wxSizeEvent& event);

	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(BugFrame, wxFrame)
	EVT_SIZING(BugFrame::sizing)
wxEND_EVENT_TABLE()

BugFrame::BugFrame() : wxFrame(NULL, wxID_ANY, "SizingSetRectBugMinimal")
{
	Show();
}

void BugFrame::sizing(wxSizeEvent& event)
{
	event.SetRect(wxSize(256, 256));
	event.Skip();
}

class BugApp : public wxApp
{
public:
	virtual bool OnInit();
};

wxIMPLEMENT_APP(BugApp);

bool BugApp::OnInit()
{
	BugFrame* frame = new BugFrame();
	return true;
}
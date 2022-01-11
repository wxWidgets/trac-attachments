#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/propgrid/propgrid.h>

class OoDexApp : public wxApp
{
public:
	virtual bool OnInit() wxOVERRIDE;
};

class MyFrame : public wxFrame
{
public:
	MyFrame();

private:
	void OnChanging(wxPropertyGridEvent& inEvent);
	void OnMenuEvent(wxCommandEvent& inEvent);
};

wxIMPLEMENT_APP(OoDexApp);

bool OoDexApp::OnInit()
{
	MyFrame* frame = new MyFrame;
	frame->Show();
	return true;
}

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, _("test app"))
{
	Bind(wxEVT_MENU, &MyFrame::OnMenuEvent, this, 10000);

	wxPropertyGrid* grid = new wxPropertyGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_BOLD_MODIFIED);
	grid->Append(new wxBoolProperty(_("checkbox"), "checkbox", false));
	grid->SetPropertyAttribute("checkbox", wxPG_BOOL_USE_CHECKBOX, 1);
	grid->Bind(wxEVT_PG_CHANGING, &MyFrame::OnChanging, this);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(grid, 1, wxEXPAND);
	SetSizer(sizer);
}

void MyFrame::OnChanging(wxPropertyGridEvent&)
{
	GetEventHandler()->QueueEvent(new wxCommandEvent(wxEVT_MENU, 10000));
}

void MyFrame::OnMenuEvent(wxCommandEvent&)
{
	Freeze();
	Thaw();
	Freeze();
	Thaw();
}

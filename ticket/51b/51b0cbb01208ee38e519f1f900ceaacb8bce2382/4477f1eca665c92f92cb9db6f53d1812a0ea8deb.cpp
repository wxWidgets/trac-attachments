// xSizeProblem by Avi Vahl

// For compilers that support precompilation, includes "wx.h".
#include <wx/wxprec.h>
#include <wx/listctrl.h>	// wxListCtrl

#ifndef WX_PRECOMP
	// Include your minimal set of headers here, or wx.h
	#include <wx/wx.h>
#endif

#ifdef __VISUALC__
	// The wxWidgets library is linked thanks to this include.
	#include <msvc/wx/setup.h>
#endif // __VISUALC__

class xSizeProblem : public wxApp
{
public:
	virtual bool OnInit();
};

IMPLEMENT_APP(xSizeProblem)

class xMainFrame : public wxFrame
{
public:
	xMainFrame();	// Constructor
};

xMainFrame::xMainFrame()
	: wxFrame (NULL, wxID_ANY, wxEmptyString)
{
	wxString appName = wxTheApp->GetAppName();
	SetTitle(appName);

	wxPanel* MainPanel = new wxPanel(this);
	wxBoxSizer* MainSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	ButtonSizer->Add(
		new wxButton(MainPanel, wxID_OPEN, "Load"),
		0,           // make horizontally unstretchable
		wxALL,       // make border all around (implicit top alignment)
		10);         // set border width to 10
	ButtonSizer->Add(
		new wxButton(MainPanel, wxID_SAVE, "Save"),
		0,           // make horizontally unstretchable
		wxALL,       // make border all around (implicit top alignment)
		10);         // set border width to 10

	ButtonSizer->Add(
		new wxCheckBox(MainPanel, wxID_ANY, "Clean"),
		0,           // make horizontally unstretchable
		wxALIGN_CENTER|wxLEFT,
		10);         // set border width to 10

	ButtonSizer->AddSpacer(40);

	ButtonSizer->Add(
		new wxButton(MainPanel, wxID_ABOUT, "About"),
		0,           // make horizontally unstretchable
		wxALL,       // make border all around (implicit top alignment)
		10);         // set border width to 10

	MainSizer->Add(
		ButtonSizer,
		0,                // make vertically unstretchable
		wxALIGN_CENTER);  // no border and centre horizontally

	MainSizer->Add(new wxListCtrl(MainPanel, wxID_ANY, wxDefaultPosition,
		wxDefaultSize, wxLC_REPORT|wxLC_HRULES|wxLC_VRULES|wxLC_SINGLE_SEL),
		1, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM|wxALIGN_CENTER, 10);

	MainPanel->SetSizerAndFit(MainSizer);
	SetSizeHints(GetSize());
}


bool xSizeProblem::OnInit()
{
	if (!wxApp::OnInit())
	{
		return false;
	}
	wxString appName("xSizeProblem");
	SetAppName(appName);
	SetAppDisplayName(appName);
	xMainFrame* Window = new xMainFrame();
	Window->Show();

	return true;
}

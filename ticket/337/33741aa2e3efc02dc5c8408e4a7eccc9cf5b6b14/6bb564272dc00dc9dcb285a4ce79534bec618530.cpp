#include <wx/wx.h>
#include <wx/richtooltip.h>

// Click on panel to create wxRichToolTip on wxPanel and on wxButton
// Clicking top of frame dismisses panel tool tip
// Clicking top of frame again causes access violation crash.

// Clicking panel repeatedly dismisses panel tool tip but not button tool tip.
// Clicking top of frame dismisses the button tool tips one by one until the last which causes crash.

class Test : public wxFrame {
	wxPanel *panel;
	wxButton *button;
public:
	Test(const wxString& title) : wxFrame(NULL, 3, title) {
		panel = new wxPanel(this, 1);
		button = new wxButton(panel, wxID_ANY);
		panel->Bind(wxEVT_LEFT_DOWN, &Test::OnLeftClick, this);
	}
	void OnLeftClick(wxMouseEvent& event) {
		wxRichToolTip tip("Title", "Message");
		tip.SetTimeout(0);
		tip.SetIcon(wxICON_ERROR);
		tip.ShowFor(button);

		wxRichToolTip tip2("Title 2", "Message 2");
		tip2.SetTimeout(0);
		tip2.SetIcon(wxICON_ERROR);
		tip2.ShowFor(panel);
	}
};

class MyApp : public wxApp {
public:
	virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
  Test *open = new Test(wxT("wxRichToolTip Test"));
  open->Show(true);
  return true;
}
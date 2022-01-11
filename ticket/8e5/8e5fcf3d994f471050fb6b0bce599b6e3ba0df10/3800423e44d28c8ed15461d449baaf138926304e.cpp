#include <wx/wx.h>
class M : public wxDialog {
	public:
	wxPanel *make_panel(wxWindow *parent) {
		auto pn = new wxPanel(parent, wxID_ANY);
		new wxButton(pn, wxID_ANY, "Hit me");
		return pn;
	};
	M(void) : wxDialog(NULL, wxID_ANY, "This") {
		auto first = new wxButton(this, wxID_ANY, "Toggle panel");
		auto panel = make_panel(this);
		panel->Disable();
		auto third = new wxButton(this, wxID_ANY, "3rd");
		first->Bind(wxEVT_BUTTON, [=](wxCommandEvent &) {
			panel->Enable(!panel->IsEnabled());
		});
		auto vp = new wxBoxSizer(wxVERTICAL);
		vp->Add(first);
		vp->Add(panel);
		vp->Add(third);
		SetSizer(vp);
		vp->SetSizeHints(this);
	};
};
class A : public wxApp {
	public: bool OnInit(void) { (new M)->Show(); return true; };
};
IMPLEMENT_APP(A);

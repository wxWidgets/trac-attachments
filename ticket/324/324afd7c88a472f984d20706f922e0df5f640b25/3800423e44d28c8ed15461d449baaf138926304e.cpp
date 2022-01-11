#include <wx/wx.h>
#include <wx/listctrl.h>
class L : public wxListCtrl {
	public:
	void resize(wxSizeEvent &event) {
		fprintf(stderr, "%ld\n", GetTopItem());
		fflush(stderr);
		int nw = GetClientSize().GetWidth();
		SetColumnWidth(0, nw);
		event.Skip();
	}
	L(wxWindow *parent) : wxListCtrl(parent, wxID_ANY, wxDefaultPosition,
		wxDefaultSize, wxLC_REPORT | wxLC_HRULES | wxLC_VRULES |
		wxLC_SINGLE_SEL)
	{
		InsertColumn(0, "#");
		for (unsigned int i = 1; i <= 20; ++i)
			InsertItem(i, wxString::Format("%u", i));
		Connect(wxEVT_SIZE, wxSizeEventHandler(L::resize));
	}
};
class F : public wxFrame {
	public:
	F(void) : wxFrame(NULL, wxID_ANY, "") {
		auto sz = new wxBoxSizer(wxVERTICAL);
		auto list = new L(this);
		sz->Add(list, 1, wxEXPAND);
		auto btn = new wxButton(this, wxID_ANY, "Crash me");
		sz->Add(btn);
		SetSizer(sz);
		sz->SetSizeHints(this);
		Bind(wxEVT_BUTTON, [=](wxCommandEvent &) {
			list->ScrollList(0, 9999);
			Maximize();
		}, btn->GetId());
	}
};
class A : public wxApp {
	private: bool OnInit(void) { (new F)->Show(); return 1; }
};
IMPLEMENT_APP(A);

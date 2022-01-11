#include <wx/wx.h>
class M : public wxFrame {
public: M(void) : wxFrame(NULL, wxID_ANY, "") {
	wxBitmap bmp(1, 1, 32);
	{
		wxMemoryDC dc(bmp);
		dc.SetPen(*wxRED);
		dc.DrawPoint(0, 0);
	}
	auto vp = new wxBoxSizer(wxHORIZONTAL);
	auto b = new wxButton(this, wxID_ANY, "x", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	vp->Add(b);
	b = new wxButton(this, wxID_ANY, "x");
	vp->Add(b);
	b = new wxButton(this, wxID_ANY, "x", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	b->SetBitmap(bmp);
	vp->Add(b);
	b = new wxButton(this, wxID_ANY, "x");
	b->SetBitmap(bmp);
	vp->Add(b);
	SetSizer(vp);
	vp->SetSizeHints(this);
}
};
class A : public wxApp {
public: bool OnInit(void) { (new M)->Show(); return true; }
};
IMPLEMENT_APP(A);

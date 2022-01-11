#include <wx/wx.h>
#include <wx/gbsizer.h>
class Loader : public wxApp {
    bool OnInit(void);
};
IMPLEMENT_APP(Loader);
bool Loader::OnInit(void) {
    wxFrame             *f = new wxFrame(NULL, wxID_ANY, wxT("Prog"));
    wxBoxSizer          *v = new wxBoxSizer(wxVERTICAL);
    wxGridBagSizer      *g = new wxGridBagSizer();
    g->AddGrowableCol(0, 0);
    g->AddGrowableCol(1, 5);
    g->Add(new wxStaticText(f, wxID_ANY, wxT("Short")),
            wxGBPosition(0, 0), wxDefaultSpan, wxALL, 3);
    g->Add(new wxTextCtrl(f, wxID_ANY, wxT("hello world")),
            wxGBPosition(0, 1), wxDefaultSpan, wxGROW | wxALL, 3);
    g->Add(new wxStaticText(f, wxID_ANY, wxT("Long long long long text Long long long long text Long long long long text Long long long long text ")),
            wxGBPosition(1, 0), wxGBSpan(1, 2), wxGROW | wxALL, 3);
    v->Add(g, 1, wxGROW);
    f->SetSizer(v);
    v->SetSizeHints(f);
    f->Show();
    return true;
}

 	  	 

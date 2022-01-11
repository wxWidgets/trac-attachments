#include "wx/wx.h"
#include "wx/progdlg.h"

class App : public wxFrame
{
    public:
	App() : wxFrame(NULL, wxID_ANY, wxT("Tooltip Bug"), wxPoint(40, 40),
		wxSize(200, 200), wxDEFAULT_FRAME_STYLE, wxT("Tooltip Bug"))
	{
	    wxPanel *panel = new wxPanel(this);

	    wxBoxSizer *h1 = new wxBoxSizer(wxHORIZONTAL);
	    wxBoxSizer *h2 = new wxStaticBoxSizer(wxHORIZONTAL, panel, wxT("Box"));
	    wxButton *b;

	    h1->AddStretchSpacer(1);
	    h1->Add(b = new wxButton(panel, ID_Button1, wxT("Button 1")),
		    wxSizerFlags(0).Expand());
	    h1->AddStretchSpacer(1);
	    b->SetToolTip(wxT("Button 1 does what button 1 does"));

	    h2->AddStretchSpacer(1);
	    h2->Add(b = new wxButton(panel, ID_Button2, wxT("Button 2")),
		    wxSizerFlags(0).Expand());
	    h2->AddStretchSpacer(1);
	    b->SetToolTip(wxT("Button 2 does what button 2 does"));

	    wxBoxSizer *v = new wxBoxSizer(wxVERTICAL);
	    v->AddStretchSpacer(1);
	    v->Add(h1, wxSizerFlags(0).Expand());
	    v->AddStretchSpacer(1);
	    v->Add(h2, wxSizerFlags(0).Expand());
	    v->AddStretchSpacer(1);

	    wxBoxSizer *h = new wxBoxSizer(wxHORIZONTAL);
	    h->AddStretchSpacer(1);
	    h->Add(v, wxSizerFlags(6).Expand());
	    h->AddStretchSpacer(1);

	    panel->SetSizer(h);
	}
	virtual ~App() {}

	enum {
	    ID_Button1 = wxID_HIGHEST + 1,
	    ID_Button2,
	};

	void OnButton1(wxCommandEvent &WXUNUSED(e)) {
	   std::cerr << "Button 1" << std::endl;
	}
	void OnButton2(wxCommandEvent &WXUNUSED(e)) {
	   std::cerr << "Button 2" << std::endl;
	}

	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(App, wxFrame)
    EVT_BUTTON(ID_Button1, App::OnButton1)
    EVT_BUTTON(ID_Button2, App::OnButton2)
END_EVENT_TABLE()


class MyApp : public wxApp {
   public:
      // if OnInit returns false, the application terminates
      virtual bool OnInit();
      virtual int OnExit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
   App *app;
   app = new App();
   app->Show(true);

   return true;
}

int MyApp::OnExit() {
   return 0;
}

// vim:set sw=3:


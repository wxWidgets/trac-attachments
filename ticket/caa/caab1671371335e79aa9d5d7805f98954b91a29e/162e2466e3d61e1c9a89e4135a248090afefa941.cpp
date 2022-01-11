// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/notebook.h>

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title);
private:
    void OnExit(wxCommandEvent& event);
    DECLARE_EVENT_TABLE();
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)  	
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello World");
    frame->Show( true );
    return true;
}

static void evtcallback_btn(wxCommandEvent &event)
{
	int width = 320, height = 203;
	wxDialog *aboutdlg = new wxDialog(NULL, wxID_ANY, wxT("About RapaGUI"), wxDefaultPosition, wxSize(width + 100, height + 100));
	
	wxPanel *panel = new wxPanel(aboutdlg, -1);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    
    	wxNotebook *nb = new wxNotebook(panel, wxID_ANY);
    	wxPanel *page1 = new wxPanel(nb); 
    
    	wxBoxSizer *vpagesizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *pagesizer = new wxBoxSizer(wxHORIZONTAL);
	
	wxBitmap *bm = new wxBitmap();
	bm->CreateScaled(width, height, 32, aboutdlg->GetContentScaleFactor());
		
	wxStaticBitmap *sb = new wxStaticBitmap(page1, wxID_ANY, *bm);
	delete bm;	
	
	pagesizer->AddStretchSpacer();
	pagesizer->Add(sb);
	pagesizer->AddStretchSpacer();
	
	vpagesizer->AddStretchSpacer();
	vpagesizer->Add(pagesizer, 0, wxEXPAND);
	vpagesizer->AddStretchSpacer();
	
	page1->SetSizer(vpagesizer);
	vpagesizer->Fit(page1);
	
	nb->AddPage(page1, wxT("About"));
	
	wxPanel *page2 = new wxPanel(nb);
	wxBoxSizer *pagesizer2 = new wxBoxSizer(wxVERTICAL);
	wxTextCtrl *tc = new wxTextCtrl(page2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_CENTRE|wxTE_RICH);
	
	tc->SetInitialSize(wxDefaultSize);
	tc->SetSelection(0, 0);
	tc->ShowPosition(0);

	pagesizer2->Add(tc, 1, wxEXPAND);
	
	page2->SetSizer(pagesizer2);
	pagesizer2->Fit(page2);
	
	nb->AddPage(page2, wxT("License"));
		
	vbox->Add(nb, 1, wxEXPAND);
	panel->SetSizerAndFit(vbox); 				
	
	aboutdlg->ShowModal();
		
	delete aboutdlg;
}

MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title)
{	
    wxPanel *panel = new wxPanel(this, -1);
    
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	
    wxListBox *lb = new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_HSCROLL|wxLB_NEEDED_SB);
    wxButton *b = new wxButton(panel, wxID_ANY, wxT("Click me"));
    
    b->Bind(wxEVT_BUTTON, evtcallback_btn, wxID_ANY, wxID_ANY);
                           
    vbox->Add(lb, 1, wxEXPAND);
    vbox->Add(b, 0, wxEXPAND);
    
    panel->SetSizerAndFit(vbox);   
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

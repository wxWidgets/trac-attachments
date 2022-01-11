// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/notebook.h>

static void evtcallback(wxBookCtrlEvent &event) 
{ 
	printf("Page changed\n");
}

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
    MyFrame *frame = new MyFrame("Test");
    frame->Show( true );
    return true;
}

MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title)
{	
    wxPanel *panel = new wxPanel(this, -1);
        
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    
    wxNotebook *nb = new wxNotebook(panel, wxID_ANY);
    wxPanel *page1 = new wxPanel(nb); 
    wxPanel *page2 = new wxPanel(nb); 
    
    wxArrayString strings;
    strings.Add("Human!");
    strings.Add("Elf");
    strings.Add("Dwarf");
    strings.Add("Hobbit");
    strings.Add("Gnome");
    
    wxBoxSizer *pagesizer = new wxBoxSizer(wxHORIZONTAL);
    wxRadioBox *radio = new wxRadioBox(page1, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, strings, 5, wxRA_SPECIFY_ROWS);			    
    pagesizer->Add(0, 0, 1, 0);	
    pagesizer->Add(radio, 0, 0x810, 6);
    pagesizer->Add(0, 0, 1, 0);	
			    
    wxBoxSizer *pagesizer2 = new wxBoxSizer(wxVERTICAL);      
    pagesizer2->Add(0, 0, 1, 0);	
    pagesizer2->Add(pagesizer, 0, wxEXPAND);
    pagesizer2->Add(0, 0, 1, 0);	    
           
    page1->SetSizer(pagesizer2);
    pagesizer2->Fit(page1);
	
    wxBoxSizer *pagesizer3 = new wxBoxSizer(wxHORIZONTAL);
    wxRadioBox *radio2 = new wxRadioBox(page2, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, strings, 5, wxRA_SPECIFY_ROWS);			    
    pagesizer3->Add(0, 0, 1, 0);	
    pagesizer3->Add(radio2, 0, 0x810, 6);
    pagesizer3->Add(0, 0, 1, 0);	
			    
    wxBoxSizer *pagesizer4 = new wxBoxSizer(wxVERTICAL);      
    pagesizer4->Add(0, 0, 1, 0);	
    pagesizer4->Add(pagesizer3, 0, wxEXPAND);
    pagesizer4->Add(0, 0, 1, 0);	    
           
    page2->SetSizer(pagesizer4);
    pagesizer4->Fit(page2);

    nb->AddPage(page1, wxT("Race"), false, -1);
    nb->AddPage(page2, wxT("Page 2"), false, -1);
		
    vbox->Add(nb, 172, 0x2000);

    wxBoxSizer *root = new wxBoxSizer(wxVERTICAL);
    root->Add(vbox, 1, wxALL|wxEXPAND, 8);

    int width, height;

    panel->SetSizer(root);
    SetClientSize(panel->GetBestSize());			
    GetClientSize(&width, &height);
    SetMinClientSize(wxSize(width, height));  

    nb->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, evtcallback);
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/hyperlink.h>

#define myprintf wxMessageOutput::Get()->Printf

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

static wxHyperlinkCtrl *hl1, *hl2;
	
static void evtcallback(wxCommandEvent &event) 
{ 		
    hl1->SetLabel(wxT("http://www.amiga-news.de/"));
    hl2->SetLabel(wxT("http://www.hollywood-mal.com/"));
}
		
MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title)
{	
    wxWindow *panel = new wxPanel(this, -1);
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    
    wxButton *but1 = new wxButton(panel, -1, wxT("Clicky"));
    hl1 = new wxHyperlinkCtrl(panel, wxID_ANY, wxT("http://www.hollywood-mal.com/"), wxT("http://www.hollywood-mal.com/"));
    hl2 = new wxHyperlinkCtrl(panel, wxID_ANY, wxT("http://www.amiga-news.de/"), wxT("http://www.amiga-news.de/"));

    vbox->Add(hl1, 0, wxALIGN_CENTER);
    vbox->Add(hl2, 0, wxALIGN_CENTER); 	 			    
    vbox->Add(but1, 0, wxEXPAND);
         
    hbox->Add(vbox, 1, 0);	    					        	    					    

    but1->Bind(wxEVT_BUTTON, evtcallback, wxID_ANY, wxID_ANY);  
                    
    panel->SetSizer(hbox);    
    SetClientSize(panel->GetBestSize());			
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

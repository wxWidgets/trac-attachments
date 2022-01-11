// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#define myprintf wxMessageOutput::Get()->Printf

static wxFrame *frame2;
static wxWindowDisabler *wd;

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title);
};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello World");
    frame->Show( true );
    return true;
}

static void evtcallback(wxCommandEvent &event) 
{ 	
    wd = new wxWindowDisabler;    	
    frame2->Show(true);
}

static void evtcallback2(wxCloseEvent &event) 
{ 
    frame2->Show(false);
    delete wd;
} 

static void evtcallback3(wxCloseEvent &event) 
{ 
    wxTheApp->ExitMainLoop();
} 
		
MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title)
{	
    wxWindow *panel = new wxPanel(this, -1);
    wxSizer *vbox;
    wxButton *b;
    
    b = new wxButton(panel, -1, wxT("Clicky"));              
    vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(b, 1, wxEXPAND);

    b->Bind(wxEVT_BUTTON, evtcallback, wxID_ANY, wxID_ANY);  
      
    panel->SetSizer(vbox);    
    SetClientSize(panel->GetBestSize());
    Bind(wxEVT_CLOSE_WINDOW, evtcallback3);	
        
    frame2 = new wxFrame(NULL, wxID_ANY, wxT("Frame 2"));
    panel = new wxPanel(frame2, -1);		
    b = new wxButton(panel, -1, wxT("Clicky 2"));              
    vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(b, 1, wxEXPAND);

    panel->SetSizer(vbox);    
    frame2->SetClientSize(panel->GetBestSize());  
    
    frame2->Bind(wxEVT_CLOSE_WINDOW, evtcallback2);	      			
}


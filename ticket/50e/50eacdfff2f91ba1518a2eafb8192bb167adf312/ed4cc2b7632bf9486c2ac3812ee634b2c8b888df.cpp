// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

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

MyFrame *frame;

bool MyApp::OnInit()
{
    frame = new MyFrame("Hello World");
    frame->Show(true);
    wxFrame *frame2 = new wxFrame(NULL, wxID_ANY, wxT("Another frame"));
    frame2->Show(true);
    
    return true;
}

static void evtcallback_b1(wxCommandEvent &event) 
{ 	
    wxFileDialog *openFileDialog = new wxFileDialog(frame);
    openFileDialog->ShowModal();			
} 
	
static void evtcallback_b2(wxCommandEvent &event) 
{ 
    wxDialog *dialog = new wxDialog(frame, wxID_ANY, wxT("Custom dialog"));
    wxPanel *panel = new wxPanel(dialog);
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxTextCtrl *tc = new wxTextCtrl(panel, -1, wxEmptyString, wxDefaultPosition, wxSize(640, 480), wxTE_RICH2|wxTE_MULTILINE);
    
    vbox->Add(tc, 1, wxEXPAND);
    panel->SetSizer(vbox);
    
    dialog->ShowModal();					
} 
	
MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title)
{	
    wxWindow *panel = new wxPanel(this, -1);
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxTextCtrl *tc = new wxTextCtrl(panel, -1, wxEmptyString, wxDefaultPosition, wxSize(640, 480), wxTE_RICH2|wxTE_MULTILINE);
    wxButton *b1 = new wxButton(panel, -1, wxT("File dialog"));
    wxButton *b2 = new wxButton(panel, -1, wxT("Custom dialog"));
    
    b1->Bind(wxEVT_BUTTON, evtcallback_b1, wxID_ANY, wxID_ANY);  
    b2->Bind(wxEVT_BUTTON, evtcallback_b2, wxID_ANY, wxID_ANY);  
            
    vbox->Add(tc, 1, wxEXPAND);       					        	    					    
    vbox->Add(b1, 0, wxEXPAND);
    vbox->Add(b2, 0, wxEXPAND);
                
    panel->SetSizer(vbox);    
    SetClientSize(panel->GetBestSize());		
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

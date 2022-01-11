// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/listctrl.h>

#define myprintf wxMessageOutput::Get()->Printf

static wxListView *lv = NULL;

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

static void evtcallback(wxCommandEvent &event) 
{ 	
    lv->Select(2);		
    lv->SetFocus();
}
	
MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title)
{	
    wxPanel *panel = new wxPanel(this, -1);
        
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
   lv = new wxListView(panel, wxID_ANY, wxDefaultPosition, wxSize(400, 400), wxLC_REPORT);
    wxButton *but1 = new wxButton(panel, -1, wxT("Clicky"));
    
    lv->AppendColumn(wxString("Title"));
    lv->InsertItem(0, wxString("One"));
    lv->InsertItem(1, wxString("Two"));   
    lv->InsertItem(1, wxString("Three"));  
    lv->InsertItem(1, wxString("Four"));           
    lv->SetColumnWidth(0, 200);			
						    
    vbox->Add(lv, 1, wxEXPAND|wxALL, 16);  
    vbox->Add(but1, 0, wxEXPAND);
    
    but1->Bind(wxEVT_BUTTON, evtcallback, wxID_ANY, wxID_ANY);  
            
    panel->SetSizer(vbox);		
    SetClientSize(panel->GetBestSize()); 
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxFrame *frame = new MyFrame("Hello World"); 
    frame->Show( true );
    return true;
}

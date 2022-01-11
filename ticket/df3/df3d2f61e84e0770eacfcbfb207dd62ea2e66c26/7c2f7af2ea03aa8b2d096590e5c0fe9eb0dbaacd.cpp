// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/listctrl.h>

#define myprintf wxMessageOutput::Get()->Printf

static wxMenu *pop;

static void evtcallback_command(wxCommandEvent &event) 
{ 
	myprintf("GOT EVENT!: %d\n", event.GetId());
} 

static void evtcallback_ctxtmenu(wxContextMenuEvent &event) 
{ 
	((wxWindow *) event.GetEventObject())->PopupMenu(pop);		
} 

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

MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title)
{	
    wxPanel *panel = new wxPanel(this, -1);
    wxMenuItem *item1 = new wxMenuItem(NULL, wxID_ANY, wxT("Test 1"));
    wxMenuItem *item2 = new wxMenuItem(NULL, wxID_ANY, wxT("Test 2"));

    pop = new wxMenu();
    pop->Append(item1);
       
    wxMenu *sub = new wxMenu();
    sub->Append(item2);
    pop->AppendSubMenu(sub, wxT("Submenu"));
    
    pop->Bind(wxEVT_MENU, evtcallback_command, item1->GetId(), item1->GetId());
    
#if 0
    // works with context menu but not with frame menu 
    pop->Bind(wxEVT_MENU, evtcallback_command, item2->GetId(), item2->GetId());
#else
    // works with frame menu but not with context menu
    sub->Bind(wxEVT_MENU, evtcallback_command, item2->GetId(), item2->GetId());
#endif
    
    wxMenuBar *mb = new wxMenuBar();
    mb->Append(pop, wxT("Test"));
    SetMenuBar(mb);
    			     
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxListView *lv = new wxListView(panel, wxID_ANY, wxDefaultPosition, wxSize(1000, 800), wxLC_REPORT);

    lv->Bind(wxEVT_CONTEXT_MENU, evtcallback_ctxtmenu);	
										    
    vbox->Add(lv, 1, wxEXPAND|wxALL, 16);  
    
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

// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

static wxSlider *sl;

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

static void evtcallback(wxCommandEvent &event) 
{
	sl->SetMax(65536);
}

MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title)
{	
    wxPanel *panel = new wxPanel(this, -1);
        
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    sl = new wxSlider(panel, wxID_ANY, 0, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_VALUE_LABEL); //|wxSL_MIN_MAX_LABELS);     
    wxButton *btn1 = new wxButton(panel, wxID_ANY, wxT("Button 1"));

    vbox->Add(sl, 1, wxEXPAND);
    vbox->Add(btn1, 1, wxEXPAND);
                            
    panel->SetSizer(vbox);  
    SetClientSize(panel->GetBestSize());
    SetMinClientSize(vbox->GetMinSize());
    
    btn1->Bind(wxEVT_BUTTON, evtcallback, wxID_ANY, wxID_ANY);
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

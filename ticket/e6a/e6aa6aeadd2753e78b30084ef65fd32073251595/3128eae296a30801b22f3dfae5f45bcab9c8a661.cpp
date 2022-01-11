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
    
    return true;
}

MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title)
{	
    wxWindow *panel = new wxPanel(this, -1);
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    
    wxSlider *sl = new wxSlider(panel, wxID_ANY, 0, 0, 64, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_VALUE_LABEL);    
    wxTextCtrl *tc = new wxTextCtrl(panel, -1, wxEmptyString, wxDefaultPosition, wxSize(640, 480), wxTE_RICH2|wxTE_MULTILINE);
    
    hbox->Add(sl, 0, wxEXPAND);
    hbox->Add(tc, 1, wxEXPAND);
                  
    panel->SetSizer(hbox);    
    SetClientSize(panel->GetBestSize());		
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

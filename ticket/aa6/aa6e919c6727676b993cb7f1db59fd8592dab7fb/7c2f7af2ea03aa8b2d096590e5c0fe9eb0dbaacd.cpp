// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/treectrl.h>

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

MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title)
{	
    wxPanel *panel = new wxPanel(this, -1);
    
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxTreeCtrl *tc = new wxTreeCtrl(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_HIDE_ROOT);

    wxTreeItemId id = tc->AddRoot("Root");   
    
    tc->AppendItem(id, wxT("CPU"));
    tc->AppendItem(id, wxT("Machine"));
    tc->AppendItem(id, wxT("Expansion buses"));
    tc->AppendItem(id, wxT("Libraries"));
    tc->AppendItem(id, wxT("Devices"));
    tc->AppendItem(id, wxT("Tasks"));
                           
    vbox->Add(tc, 1, wxEXPAND);

    panel->SetSizerAndFit(vbox);    
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

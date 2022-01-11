// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/persist.h>
#include <wx/persist/toplevel.h>

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
    wxBoxSizer *vbox2 = new wxBoxSizer(wxVERTICAL);
				
    wxSlider *sl = new wxSlider(panel, wxID_ANY, 50, 0, 100);
                           
    vbox->Add(sl, 0, wxEXPAND);
    vbox2->Add(vbox, 0, wxALL|wxEXPAND, 8);
				
    panel->SetSizer(vbox2);   
    
    wxSize bestsize = panel->GetBestSize();
    SetClientSize(bestsize); 
       
    SetSize(wxSize(400, -1));
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

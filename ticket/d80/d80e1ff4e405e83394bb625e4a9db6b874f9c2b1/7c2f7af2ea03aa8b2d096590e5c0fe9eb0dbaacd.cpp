// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

//#define PRIVATEPANEL

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxFrame *frame = new wxFrame(NULL, wxID_ANY, wxT("Hello World"));
    wxPanel *panel = new wxPanel(frame);
    wxWindow *parent;

    wxTextCtrl *tcc = new wxTextCtrl(panel, wxID_ANY);

    wxStaticBoxSizer *vbox = new wxStaticBoxSizer(wxVERTICAL, panel, wxT("Foobar"));   

#if 0
    parent = panel;
#else
    parent = vbox->GetStaticBox();
#endif

    wxButton *btn1 = new wxButton(parent, wxID_ANY, wxT("Button 1"));
    wxButton *btn2 = new wxButton(parent, wxID_ANY, wxT("Button 2"));
    wxButton *btn3 = new wxButton(parent, wxID_ANY, wxT("Button 3"));
    wxButton *btn4 = new wxButton(parent, wxID_ANY, wxT("Button 4"));
    wxButton *btn5 = new wxButton(parent, wxID_ANY, wxT("Button 5"));
    vbox->Add(btn1, 0, wxEXPAND);
    vbox->Add(btn2, 0, wxEXPAND|wxTOP, 10);
    vbox->Add(btn3, 0, wxEXPAND|wxTOP, 10);
    vbox->Add(btn4, 0, wxEXPAND|wxTOP, 10);
    vbox->Add(btn5, 0, wxEXPAND|wxTOP, 10);

    wxTextCtrl *tc = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);                                   

    wxBoxSizer *vbox2 = new wxBoxSizer(wxVERTICAL);
    vbox2->Add(tcc, 0, wxEXPAND); 
    vbox2->Add(vbox, 0, wxEXPAND);
    vbox2->Add(tc, 1, wxEXPAND);   

    panel->SetSizerAndFit(vbox2);          
    frame->Show( true );
    return true;
}

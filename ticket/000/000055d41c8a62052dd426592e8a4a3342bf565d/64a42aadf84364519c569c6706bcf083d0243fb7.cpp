#include "wx/wx.h"   
#include <wx/sizer.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/panel.h>
/**** MyFrame ****/
class MyFrame : public wxFrame {
public:
    MyFrame()
        : wxFrame(NULL, wxID_ANY, "Test")
    {                     
    wxNotebook *notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition,  	wxSize(800, 600));


	wxTreeCtrl *panel1= new wxTreeCtrl(notebook,  wxID_ANY);
	panel1->AddRoot("just a test");
	panel1->UnselectAll();
	
	wxPanel *panel2= new wxPanel(notebook, wxID_ANY);  
	
	
    notebook->AddPage(panel1, wxT("panel 1"));
    notebook->AddPage(panel2, wxT("panel 2"));

    wxSizer *sizerV = new wxBoxSizer(wxVERTICAL);
    sizerV->Add(notebook, wxSizerFlags(1).Expand());

    SetSizerAndFit(sizerV);
	}    
};

/**** MyApp ****/
class MyApp : public wxApp {
public:   
    bool OnInit()
    {
        MyFrame* newframe = new MyFrame();               
        newframe->Show();
        return true;
    }
};

IMPLEMENT_APP(MyApp)

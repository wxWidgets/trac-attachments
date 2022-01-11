#include "wx/wx.h"   
#include <wx/treectrl.h>
class MyFrame : public wxFrame {
public:
  
    MyFrame()
        : wxFrame(NULL, wxID_ANY, "Test")
    {                     
	tree1= new  wxTreeCtrl(this,  wxID_ANY);
	  wxTreeItemId temp=tree1->AddRoot("test");
	    temp=tree1->AppendItem(temp, "test1");
	      tree1->AppendItem(temp, "test2");
	tree1->ExpandAll();
	      
	tree2= new  wxTreeCtrl(this,  wxID_ANY);
	temp=tree2->AddRoot("test");
	    temp=tree2->AppendItem(temp, "test1");
	      tree2->AppendItem(temp, "test2");
	tree2->ExpandAll();
	      
	 wxFont font = tree2->GetFont();
	 font.SetPointSize(35);
	 tree2->SetFont(font);
	      
    button=new wxButton(this, wxID_ANY, "Restore Font");  
    Bind(wxEVT_BUTTON, &MyFrame::RestoreFont, this);
    
    wxBoxSizer *sizer=new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(tree1, 0, wxEXPAND,10);
    sizer->Add(tree2, 0, wxEXPAND,10);
    sizer->Add(button, 0, wxALL,10);
    SetSizerAndFit(sizer);
    } 
    
    void RestoreFont(wxCommandEvent& event)
    {
     wxFont font = tree2->GetFont();
     font.SetPointSize(     wxSystemSettings::GetFont(wxSYS_SYSTEM_FONT).GetPointSize()     );
     tree2->SetFont(font);
    }

	
private:
  wxTreeCtrl *tree1;
  wxTreeCtrl *tree2;
  wxButton *button;
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

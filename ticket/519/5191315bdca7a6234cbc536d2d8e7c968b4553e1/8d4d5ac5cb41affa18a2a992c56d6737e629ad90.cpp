#include "wx/wx.h"


class TestApp : public wxApp
{
public:
    virtual bool OnInit() {
    	wxFrame *frame = new wxFrame(NULL, -1, _T("Test"));

    	wxFlexGridSizer *sizer = new wxFlexGridSizer(3, 1, 0, 0);
    	
    	sizer->Add(new wxListBox(frame, -1, wxDefaultPosition, wxSize(200,100)), 1, wxGROW);
    	sizer->Add(new wxButton(frame, -1, _T("Hello")), 1, wxGROW);
    	sizer->Add(new wxTextCtrl(frame, -1, _T("dummy"), wxDefaultPosition, wxSize(200, 100)), 1, wxGROW);
    	sizer->AddGrowableRow(0, 1);
    	sizer->AddGrowableRow(1, 1);
       	sizer->AddGrowableRow(2, 3);
        sizer->AddGrowableCol(0, 1);
	
    	frame->SetSizer(sizer);
    	sizer->SetSizeHints(frame);
    	
    	frame->Show();
    	SetTopWindow(frame);
        
        
    	frame = new wxFrame(NULL, -1, _T("Test 2"));

    	wxBoxSizer *sizer2 = new wxBoxSizer( wxVERTICAL );
    	
    	sizer2->Add(new wxListBox(frame, -1, wxDefaultPosition, wxSize(200,100)), 1, wxGROW);
    	sizer2->Add(new wxButton(frame, -1, _T("Hello")), 1, wxGROW);
    	sizer2->Add(new wxTextCtrl(frame, -1, _T("dummy"), wxDefaultPosition, wxSize(200, 100)), 3, wxGROW);
	
    	frame->SetSizer(sizer2);
    	sizer2->SetSizeHints(frame);
    	
    	frame->Show();
        
    	
    	return true;
    }
};

IMPLEMENT_APP(TestApp)

 	  	 

#include "wx/wx.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

class Dialog1 : public wxDialog
{
public:
	Dialog1() : wxDialog(NULL, -1, wxT("Dialog1"))
	{
	    wxButton *btn=new wxButton(this, -1, wxT("Click me"));
	 	btn->Bind(wxEVT_BUTTON, &Dialog1::OnButton, this);
	}

	void OnButton(wxCommandEvent&) 
	{
		wxMessageBox(wxT("Hello"), wxT("Hello"), wxOK|wxICON_ERROR);
	}
};


bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() ) return false;

    Dialog1 dlg1;
    dlg1.ShowModal();

    return false;
}

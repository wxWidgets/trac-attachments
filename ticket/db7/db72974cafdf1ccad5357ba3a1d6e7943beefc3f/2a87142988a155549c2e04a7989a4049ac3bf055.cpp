// wxDlgTest.cpp : Defines the entry point for the application.
//
#include <wx/app.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>

class CDlgTestApp : public wxApp
{
public:
	virtual bool OnInit();
};


class CDlgTestDlg : public wxDialog
{
public:
	CDlgTestDlg();
};


bool CDlgTestApp::OnInit()
{
	CDlgTestDlg * dlg = new CDlgTestDlg();
	dlg->ShowModal();
	return FALSE;
}

CDlgTestDlg::CDlgTestDlg() : wxDialog(NULL, wxID_ANY, wxString("test"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	wxFlexGridSizer * sizer = new wxFlexGridSizer(2);
	sizer->AddGrowableCol(1);
	sizer->Add(new wxStaticText(this, wxID_ANY, wxT("Test:")), 0, wxALIGN_RIGHT);
	sizer->Add(new wxTextCtrl(this, wxID_ANY), 1, wxEXPAND);
	sizer->Add(new wxStaticText(this, wxID_ANY, wxT("&Test:")), 0, wxALIGN_RIGHT);
	sizer->Add(new wxTextCtrl(this, wxID_ANY), 1, wxEXPAND);

	SetSizer(sizer);
	sizer->SetSizeHints(this);
}

IMPLEMENT_APP(CDlgTestApp);

 	  	 

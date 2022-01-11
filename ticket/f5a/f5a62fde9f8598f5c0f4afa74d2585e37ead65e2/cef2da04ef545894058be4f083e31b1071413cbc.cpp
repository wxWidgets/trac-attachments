// wxDlgTest.cpp : Defines the entry point for the application.
//
#include <wx/app.h>
#include <wx/gbsizer.h>
#include <wx/textctrl.h>

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
	wxGridBagSizer * sizer = new wxGridBagSizer();
	sizer->AddGrowableCol(0);
	sizer->Add(new wxTextCtrl(this, wxID_ANY), wxGBPosition(0, 0), wxDefaultSpan, wxEXPAND);
	sizer->Add(new wxTextCtrl(this, wxID_ANY), wxGBPosition(0, 1), wxDefaultSpan);

	wxBoxSizer * box = new wxBoxSizer(wxHORIZONTAL);
	box->Add(new wxTextCtrl(this, wxID_ANY), 1, wxEXPAND);
	box->Add(new wxTextCtrl(this, wxID_ANY), 1, wxEXPAND);
	box->Add(new wxTextCtrl(this, wxID_ANY), 1, wxEXPAND);
	sizer->Add(box, wxGBPosition(1, 0), wxGBSpan(1, 2), wxEXPAND);

	SetSizer(sizer);
	sizer->SetSizeHints(this);
}

IMPLEMENT_APP(CDlgTestApp);

 	  	 

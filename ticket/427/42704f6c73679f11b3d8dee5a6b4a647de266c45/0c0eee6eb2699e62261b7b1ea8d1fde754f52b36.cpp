#include <wx/app.h>
#include <wx/gbsizer.h>
#include <wx/textctrl.h>

class CTextCtrlTestApp : public wxApp
{
public:
	virtual bool OnInit();
};


class CTextCtrlTestDlg : public wxDialog
{
public:
	CTextCtrlTestDlg();
};


bool CTextCtrlTestApp::OnInit()
{
	CTextCtrlTestDlg * dlg = new CTextCtrlTestDlg();
	dlg->ShowModal();
	return FALSE;
}

CTextCtrlTestDlg::CTextCtrlTestDlg() : wxDialog(NULL, wxID_ANY, wxString("test"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	wxGridBagSizer * sizer = new wxGridBagSizer();
//	wxFlexGridSizer * sizer = new wxFlexGridSizer(1);
//	wxGridSizer * sizer = new wxGridSizer(1);
	wxTextCtrl * ctrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_TAB | wxTE_MULTILINE);
	sizer->AddGrowableCol(0);
	sizer->AddGrowableRow(0);
	sizer->Add(ctrl, wxGBPosition(0, 0), wxGBSpan(1, 1), wxEXPAND | wxALL, 3);
//	sizer->Add(ctrl, 1, wxEXPAND | wxALL, 3);
	SetSizer(sizer);
	sizer->SetSizeHints(this);
}

IMPLEMENT_APP(CTextCtrlTestApp);

 	  	 

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#if !defined(__WXMSW__) && !defined(__WXPM__)
    #include "../sample.xpm"
#endif

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyDialog : public wxDialog
{
public:
    MyDialog(const wxString& title);
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    MyDialog *dlg = new MyDialog("Minimal wxWidgets App");
    dlg->ShowModal();
	dlg->Destroy();
    return true;
}

MyDialog::MyDialog(const wxString& title)
       : wxDialog(NULL, wxID_ANY, title)
{
	wxString choices[] = {wxT("1"), wxT("2"), wxT("3")};
	wxComboBox* combo = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, -1), 3, choices, wxCB_READONLY);
	wxTextCtrl* txt = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, -1));
	wxSizer* buttons = CreateSeparatedButtonSizer(wxOK | wxCANCEL);
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(combo);
	sizer->Add(txt);
	sizer->Add(buttons);
	SetSizerAndFit(sizer);
}


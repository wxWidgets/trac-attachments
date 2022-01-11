#include "wx/wx.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

DEFINE_EVENT_TYPE(myEVT_AFTERSHOW)
DECLARE_EVENT_TYPE(myEVT_AFTERSHOW, -1);

class ProgressDialog : public wxDialog
{
public:
	ProgressDialog() : wxDialog(NULL, -1, wxT("Please wait..."))
	{
		Bind(myEVT_AFTERSHOW, &ProgressDialog::OnAfterShow, this);
	}

	void Exec()
	{
	    AddPendingEvent(wxCommandEvent(myEVT_AFTERSHOW));
	    ShowModal();
	}

	void OnAfterShow(wxEvent&) 
	{
		// do lengthy processing here:
		// ...
		// when done close the dialog:
		EndModal(0);		
	}
};

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() ) return false;

    ProgressDialog dlg1;
    dlg1.Exec();

    return false;
}

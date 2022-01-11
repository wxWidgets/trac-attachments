// wxDlgTest.cpp : Defines the entry point for the application.
//
#include <wx/app.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>

class CDlgTestApp : public wxApp
{
public:
	virtual bool OnInit();
};


class CDlgTestFrame : public wxFrame
{
	public:
		CDlgTestFrame(const wxString & title, const wxPoint & pos, const wxSize & size);
		void OnQuit(wxCommandEvent & event);
		void OnTest(wxCommandEvent & event);

	private:
		DECLARE_EVENT_TABLE()
};

class CDlgTestDlg : public wxDialog
{
public:
	CDlgTestDlg(wxWindow * parent);
};


bool CDlgTestApp::OnInit()
{
	CDlgTestFrame * frame = new CDlgTestFrame("test", wxPoint(50,50), wxSize(450,340));
	frame->Show(TRUE);
	SetTopWindow(frame);
	return TRUE;
}

BEGIN_EVENT_TABLE(CDlgTestFrame, wxFrame)
  EVT_MENU    (wxID_OPEN, CDlgTestFrame::OnTest)
  EVT_MENU    (wxID_EXIT, CDlgTestFrame::OnQuit)
END_EVENT_TABLE()


CDlgTestFrame::CDlgTestFrame(const wxString & title, const wxPoint & pos, const wxSize & size)
	: wxFrame((wxFrame *)NULL, wxID_ANY, title, pos, size)
{
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(wxID_OPEN, "&Me...");
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&Click");
	SetMenuBar( menuBar );
}


void CDlgTestFrame::OnQuit(wxCommandEvent& WXUNUSED( event ))
{
	Close(TRUE);
}

void CDlgTestFrame::OnTest(wxCommandEvent& WXUNUSED( event ))
{
	CDlgTestDlg test(this);
	test.ShowModal();
}

CDlgTestDlg::CDlgTestDlg(wxWindow * parent) : wxDialog(parent, wxID_ANY, wxString("test"))
{
	wxBoxSizer * topsizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer * sizer2 = new wxBoxSizer(wxHORIZONTAL);
	//wxStaticBoxSizer * rightSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Check Boxes:");
	wxBoxSizer * rightSizer = new wxBoxSizer(wxVERTICAL);
	rightSizer->Add(new wxCheckBox(this, wxID_ANY, "Check Bo&x 1"), 0, wxALL, 1);
	rightSizer->Add(new wxCheckBox(this, wxID_ANY, "Check Box &2"), 0, wxALL, 1);
	sizer2->Add(rightSizer, 0, wxALIGN_RIGHT | wxALL, 3);
	topsizer->Add(sizer2, 0, wxALIGN_TOP);
	wxBoxSizer * button_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton * button;
	button_sizer->Add(button = new wxButton(this, wxID_OK, "&OK"), 0, wxALL, 3);
	button->SetDefault();
	button_sizer->Add(new wxButton( this, wxID_CANCEL, "&Cancel"), 0, wxALL, 3);
	topsizer->Add(button_sizer, 0, wxALIGN_RIGHT);
	SetSizer(topsizer);
	topsizer->SetSizeHints(this);
}


IMPLEMENT_APP(CDlgTestApp);

 	  	 

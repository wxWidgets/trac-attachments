
#include "wx/wx.h"
#include "wx/toolbar.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit() wxOVERRIDE;
};

class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString &);
	void OnQuit(wxCommandEvent &);
	void OnModal(wxCommandEvent &);

private:
	wxToolBar * m_ToolBar;

	enum
	{
		ID_TEST_QUIT = wxID_EXIT,
		ID_TEST_SHOW_MODAL = 1
	};
};

class Modal : public wxDialog
{
public:
	Modal(class wxWindow *);
	void OnModal(wxCommandEvent &);

private:
	wxToolBar * m_ToolBar;

	enum
	{
		ID_MODAL_SHOW = 1
	};
};

// ---------------------------------------------------------------------------


wxIMPLEMENT_APP(MyApp);


bool MyApp::OnInit()
{
	if( !wxApp::OnInit() )
	{
		return false;
	}

	MyFrame *frame = new MyFrame("Test");
	frame->Show(true);

	return true;
}
MyFrame::MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title)
{
	wxMenu *fileMenu = new wxMenu;
	fileMenu->Append(ID_TEST_QUIT, "E&xit\tAlt-X", "Quit this program");

	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, "&File");
	SetMenuBar(menuBar);

	//

	m_ToolBar = new wxToolBar
	(
		this, wxID_ANY,
		wxDefaultPosition, wxDefaultSize,
		wxTB_HORIZONTAL | wxTB_HORZ_TEXT
	);
	m_ToolBar->AddTool
	(
		ID_TEST_SHOW_MODAL, _("ShowModal"), wxNullBitmap
	);
	m_ToolBar->Realize();

	m_ToolBar->Bind
	(
		wxEVT_COMMAND_TOOL_CLICKED,
		&MyFrame::OnModal, this, ID_TEST_SHOW_MODAL
	);
}
void MyFrame::OnQuit(wxCommandEvent & Event)
{
	Close(true);
}
void MyFrame::OnModal(wxCommandEvent & Event)
{
	Modal l_Modal(this);
	l_Modal.ShowModal();
}

// ---------------------------------------------------------------------------

Modal::Modal(wxWindow * Parent)
	: wxDialog(Parent, wxID_ANY, "Modal",
				wxDefaultPosition, wxDefaultSize,
				wxDEFAULT_DIALOG_STYLE)
{
	m_ToolBar = new wxToolBar
	(
		this, wxID_ANY,
		wxDefaultPosition, wxDefaultSize,
		wxTB_HORIZONTAL | wxTB_HORZ_TEXT
	);
	m_ToolBar->AddTool
	(
		ID_MODAL_SHOW, _("ShowModal"),
		wxNullBitmap
	);

	m_ToolBar->Realize();

	m_ToolBar->Bind
	(
		wxEVT_COMMAND_TOOL_CLICKED,
		&Modal::OnModal, this, ID_MODAL_SHOW
	);
	this->CenterOnParent();
}
void Modal::OnModal(wxCommandEvent & Event)
{
	Modal l_Modal(this);
	l_Modal.ShowModal();
}

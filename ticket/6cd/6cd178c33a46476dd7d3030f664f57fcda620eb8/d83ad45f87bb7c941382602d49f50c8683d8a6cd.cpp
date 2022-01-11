#include <wx/aui/auibook.h>
#include <wx/button.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/propgrid/propgrid.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/wx.h>

enum {
	ID_NEW = 1,
	ID_SWITCH,
	ID_CLEAR,
};

class TestPanel: public wxPanel
{
	public:
		TestPanel(wxWindow *parent);
};

TestPanel::TestPanel(wxWindow *parent): wxPanel(parent)
{
	wxNotebook *v_tools = new wxNotebook(this, wxID_ANY);
	
	wxPanel *page_panel = new wxPanel(v_tools);
	wxBoxSizer *page_sz = new wxBoxSizer(wxVERTICAL);
	
	// WORKS CORRECTLY
	// v_tools->AddPage(page_panel, "YYY", true);
	
	wxPropertyGrid *pgrid = new wxPropertyGrid(page_panel, wxID_ANY);
	page_sz->Add(pgrid, 1, wxEXPAND);
	
	page_panel->SetSizerAndFit(page_sz);
	
	// GENERATES EXTRA EVENTS AND CORRUPTS wxAuiNotebook::m_curPage
	v_tools->AddPage(page_panel, "YYY", true);
}

class TestFrame: public wxFrame
{
	public:
		TestFrame();
		
	private:
		wxAuiNotebook *notebook;
		wxTextCtrl *log;
		
		void OnNew(wxCommandEvent &event);
		void OnSwitch(wxCommandEvent &event);
		void OnClear(wxCommandEvent &event);
		
		void OnPageChanged(wxAuiNotebookEvent& event);
		void OnPageChanging(wxAuiNotebookEvent& event);
		
	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(TestFrame, wxFrame)
	EVT_BUTTON(ID_NEW,    TestFrame::OnNew)
	EVT_BUTTON(ID_SWITCH, TestFrame::OnSwitch)
	EVT_BUTTON(ID_CLEAR,  TestFrame::OnClear)
	
	EVT_AUINOTEBOOK_PAGE_CHANGED(wxID_ANY,  TestFrame::OnPageChanged)
	EVT_AUINOTEBOOK_PAGE_CHANGING(wxID_ANY, TestFrame::OnPageChanging)
END_EVENT_TABLE()

TestFrame::TestFrame():
	wxFrame(NULL, wxID_ANY, "wxAuiNotebook test")
{
	wxBoxSizer *frame_sz = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer *btn_sz = new wxBoxSizer(wxHORIZONTAL);
	frame_sz->Add(btn_sz);
	
	wxButton *new_btn = new wxButton(this, ID_NEW, "Create tab");
	btn_sz->Add(new_btn);
	
	wxButton *switch_btn = new wxButton(this, ID_SWITCH, "Create tab and switch to");
	btn_sz->Add(switch_btn);
	
	wxButton *clear_btn = new wxButton(this, ID_CLEAR, "Clear log");
	btn_sz->Add(clear_btn);
	
	notebook = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		(wxAUI_NB_TOP | wxAUI_NB_TAB_MOVE | wxAUI_NB_SCROLL_BUTTONS | wxAUI_NB_CLOSE_ON_ALL_TABS));
	frame_sz->Add(notebook, 1, wxEXPAND);
	
	log = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, (wxTE_MULTILINE | wxTE_READONLY));
	frame_sz->Add(log, 1, wxEXPAND);
	
	SetSizerAndFit(frame_sz);
	
	SetSize(wxSize(600, 400));
}

void TestFrame::OnNew(wxCommandEvent &event)
{
	int pc = notebook->GetPageCount();
	
	*log << "About to add page " << pc << "\n";
	
	TestPanel *panel = new TestPanel(notebook);
	notebook->AddPage(panel, "XXX", false);
	
	*log << "Added page " << pc << "\n";
}

void TestFrame::OnSwitch(wxCommandEvent &event)
{
	int pc = notebook->GetPageCount();
	
	*log << "About to add (and switch to) page " << pc << "\n";
	
	TestPanel *panel = new TestPanel(notebook);
	notebook->AddPage(panel, "XXX", true);
	
	*log << "Added page " << pc << "\n";
}

void TestFrame::OnClear(wxCommandEvent &event)
{
	log->SetValue("");
}

void TestFrame::OnPageChanged(wxAuiNotebookEvent& event)
{
	*log << "wxEVT_AUINOTEBOOK_PAGE_CHANGED: "
		<< "GetSelection() = " << event.GetSelection()
		<< " GetOldSelection() = " << event.GetOldSelection() << "\n";
}

void TestFrame::OnPageChanging(wxAuiNotebookEvent& event)
{
	*log << "wxEVT_AUINOTEBOOK_PAGE_CHANGING: "
		<< "GetSelection() = " << event.GetSelection()
		<< " GetOldSelection() = " << event.GetOldSelection() << "\n";
}

class TestApp: public wxApp
{
	public:
		virtual bool OnInit();
};

IMPLEMENT_APP(TestApp);

bool TestApp::OnInit()
{
	TestFrame *frame = new TestFrame();
	frame->Show();
	
	return true;
}

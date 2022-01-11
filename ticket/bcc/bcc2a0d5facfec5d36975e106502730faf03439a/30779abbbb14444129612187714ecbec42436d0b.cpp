#include <wx/wx.h>
#include <wx/log.h>
#include "wx/notebook.h"

class DemoFrame : public wxFrame
{
    wxNotebook *notebook;
    wxButton   *button_remove_page;
    wxTextCtrl *log_text_ctrl;
    wxWindow   *deleted_page;
    wxLog      *log_target;
public:
    DemoFrame(const wxString &title);
private:
    DECLARE_EVENT_TABLE()
    void OnPageChanged(wxNotebookEvent &event);
    void update_page_texts();
    void remove_current_page(wxCommandEvent &event);
    void check_page(wxNotebookEvent &event);

    enum {
	ID_REMOVE_CURRENT_PAGE = wxID_HIGHEST + 1,
    };
};

BEGIN_EVENT_TABLE(DemoFrame, wxFrame)
    EVT_NOTEBOOK_PAGE_CHANGED(wxID_ANY, DemoFrame::OnPageChanged)
    EVT_BUTTON(ID_REMOVE_CURRENT_PAGE, DemoFrame::remove_current_page)
END_EVENT_TABLE()

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    if (!wxApp::OnInit())
	return false;
    wxFrame *frame = new DemoFrame("Notebook test");
    frame->Show(true);
    return true;
}


DemoFrame::DemoFrame(const wxString &title)
    : wxFrame(NULL, wxID_ANY, title)
{
    log_text_ctrl = new wxTextCtrl(this, wxID_ANY,
				   "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    log_target = new wxLogTextCtrl(log_text_ctrl);
    wxLog::SetActiveTarget(log_target);
    
    notebook = new wxNotebook(this, wxID_ANY);
    for (int i = 0; i < 10; i++) {
	notebook->AddPage(new wxPanel(notebook),
			  wxString::Format("Page %d", i));
    }

    button_remove_page = new wxButton(this, ID_REMOVE_CURRENT_PAGE, "Remove current page");
    wxSizer *sz = new wxBoxSizer(wxVERTICAL);
    sz->Add(notebook, 1.0, wxEXPAND);
    sz->Add(button_remove_page, 0, wxEXPAND);
    sz->Add(log_text_ctrl, 0, wxEXPAND);
    SetSizer(sz);
    SetSize(800, 500);
}

void DemoFrame::update_page_texts()
{
    int pages = notebook->GetPageCount();
    for (int i = 0; i < pages; i++) {
	notebook->SetPageText(i, wxString::Format("Page %d", i));
    }
}

void DemoFrame::OnPageChanged(wxNotebookEvent &event)
{
    event.Skip();
    int oldpage = event.GetOldSelection();
    int page = event.GetSelection();
    int pages = notebook->GetPageCount();
    wxLogMessage("Page changed: %d -> %d (%d pages).", oldpage, page, pages);
    wxWindow *widget = notebook->GetPage(page);
    wxLogMessage("New selected page widget: %p.", widget);
}

void DemoFrame::remove_current_page(wxCommandEvent &event)
{
    int current_page = notebook->GetSelection();
    wxWindow *current_page_widget = notebook->GetPage(current_page);
    wxLogMessage("Current page before removing it: %d (%p).", current_page, current_page_widget);
    notebook->Bind(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, &DemoFrame::check_page, this);
    deleted_page = current_page_widget;
    notebook->DeletePage(current_page);
    update_page_texts();
}

void DemoFrame::check_page(wxNotebookEvent &event)
{
    event.Skip();
    wxWindow *page = notebook->GetPage(event.GetSelection());
    if (page == deleted_page) {
	wxLogWarning("Whoops: Removed page still visible to PAGE_CHANGED event, marked as new selection.");
    }
    notebook->Unbind(wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, &DemoFrame::check_page, this);
}

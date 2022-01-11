#include <wx/wx.h>

class parentFrame : public wxFrame
{
public:
	parentFrame(const wxString& title);
    void OnShowChild( wxCommandEvent& event );
    void OnChildDestroyed( wxWindowDestroyEvent& event );
private:
    wxFrame *m_child;
};

class app : public wxApp
{
public:
	virtual bool OnInit();
};

IMPLEMENT_APP(app)

bool app::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

	parentFrame*	f = new parentFrame("Parent Frame");
	f->Show(true);
	return (true);
}

parentFrame::parentFrame(const wxString& title) :
    wxFrame(0, wxID_ANY, title), m_child(0)
{
    wxButton    *button = new wxButton(this, wxID_ANY, "Show Child", wxPoint(10, 10), wxSize(100, 23));
    button->Bind(wxEVT_BUTTON, &parentFrame::OnShowChild, this);
}

void parentFrame::OnShowChild( wxCommandEvent& event )
{
    // Test that the condition of being deleted can be handled
    if (m_child)
    {
        m_child->Close();
    
        if (wxPendingDelete.Member(m_child) && !m_child->IsBeingDeleted())
            wxLogDebug("Child window in pending delete list but not marked as being deleted");
    }
    
    if (!m_child || m_child->IsBeingDeleted())
    {
        m_child = new wxFrame(this, wxID_ANY, "Child Frame", wxDefaultPosition, wxDefaultSize, wxCAPTION|wxCLOSE_BOX|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL);
        m_child->Bind(wxEVT_DESTROY, &parentFrame::OnChildDestroyed, this);
    }
    
    if (m_child)
    {
        m_child->InitDialog();
        m_child->Show();
        m_child->SetFocus();
    }
}

void parentFrame::OnChildDestroyed( wxWindowDestroyEvent& event )
{
    m_child = 0;
}

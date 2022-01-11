#include <wx/app.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/filedlg.h>

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
	wxFileDialog fileDlg(this, "Test", ".", "", "all files|*.*", wxSAVE/* | wxOVERWRITE_PROMPT*/);
	fileDlg.ShowModal();
}

IMPLEMENT_APP(CDlgTestApp);

 	  	 

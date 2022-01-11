#include <wx/app.h>
#include <wx/frame.h>
#include <wx/combobox.h>
#include <wx/button.h>
#include <wx/toolbar.h>
#include <wx/string.h>

class CToolBarTestApp : public wxApp
{
public:
	virtual bool OnInit();
};


class CToolBarTestFrame : public wxFrame
{
public:
	CToolBarTestFrame();
	void onMouseMoved(wxMouseEvent & event);
	DECLARE_EVENT_TABLE()
private:
	wxComboBox * combo;
};

bool CToolBarTestApp::OnInit()
{
	CToolBarTestFrame * frame = new CToolBarTestFrame();
	frame->Show(true);
	SetTopWindow(frame);
	return true;
}

BEGIN_EVENT_TABLE(CToolBarTestFrame, wxFrame)
	EVT_MOTION(CToolBarTestFrame::onMouseMoved)
END_EVENT_TABLE()

CToolBarTestFrame::CToolBarTestFrame() : wxFrame(NULL, wxID_ANY, wxString("test"))
{
	CreateToolBar();
	wxButton * button = new wxButton(GetToolBar(), wxID_ANY, "test");
	button->SetToolTip("a test button");
	GetToolBar()->AddControl(button);
	GetToolBar()->AddControl(combo = new wxComboBox(GetToolBar(), wxID_ANY, "test", wxDefaultPosition, wxSize(200, -1)));
	GetToolBar()->Realize();
}

void CToolBarTestFrame::onMouseMoved(wxMouseEvent & event)
{
	combo->SetValue(wxString::Format("test: %d, %d", ClientToScreen(event.GetPosition()).x, ClientToScreen(event.GetPosition()).y));
}

IMPLEMENT_APP(CToolBarTestApp);
	
 	  	 

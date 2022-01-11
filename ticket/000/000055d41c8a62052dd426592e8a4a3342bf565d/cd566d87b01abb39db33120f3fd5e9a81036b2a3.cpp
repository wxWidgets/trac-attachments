#include "wx/wx.h"
#include <wx/sizer.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/panel.h>

/**** MyNotebook ****/
class MyNotebook : public wxNotebook {
public:
	MyNotebook(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
		: wxNotebook(parent, id, pos, size)
	{}

private:
	void OnMouseButtonRelease(wxMouseEvent& event)
	{
		long xpos, ypos;
		event.GetPosition(&xpos, &ypos);

		long flags = 0;
		int tab = HitTest(wxPoint(xpos, ypos), &flags);

		if ((tab != -1) && (flags == wxNB_HITTEST_ONLABEL))
		{
			DeletePage(tab);
		}
	}

	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyNotebook, wxNotebook)
	EVT_MIDDLE_UP(MyNotebook::OnMouseButtonRelease)
END_EVENT_TABLE()


/**** MyFrame ****/
class MyFrame : public wxFrame {
public:
	MyFrame()
		: wxFrame(NULL, wxID_ANY, wxT("Test"))
	{
		wxNotebook *notebook = new MyNotebook(this, wxID_ANY, wxDefaultPosition, wxSize(800, 600));

		wxTreeCtrl *panel1 = new wxTreeCtrl(notebook, wxID_ANY);
		panel1->AddRoot(wxT("just a test"));
		panel1->UnselectAll();

		wxPanel *panel2 = new wxPanel(notebook, wxID_ANY);

		notebook->AddPage(panel1, wxT("panel 1"));
		notebook->AddPage(panel2, wxT("panel 2"));

		wxSizer *sizerV = new wxBoxSizer(wxVERTICAL);
		sizerV->Add(notebook, wxSizerFlags(1).Expand());

		SetSizerAndFit(sizerV);
	}
};

/**** MyApp ****/
class MyApp : public wxApp {
public:
	bool OnInit()
	{
		MyFrame* newframe = new MyFrame();
		newframe->Show();
		return true;
	}
};

IMPLEMENT_APP(MyApp)

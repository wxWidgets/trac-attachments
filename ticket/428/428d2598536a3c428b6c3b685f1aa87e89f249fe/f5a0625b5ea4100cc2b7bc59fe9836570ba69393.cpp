// Build: g++ buggy.cpp -Wall $(wx-config --cxxflags --libs core,base)
#include <wx/wx.h>
#include <wx/spinctrl.h>

class CDialog : public wxDialog
{
public:
	CDialog(const wxString & sTitle) : wxDialog(NULL, wxID_ANY, sTitle) {
		int x0 = 10, y0 = 10, dx = 50, dy = 40;
		// a static text
		new wxStaticText(this, wxID_STATIC, "Apple", wxPoint(x0, y0));
		// a text control and its label
		new wxStaticText(this, wxID_STATIC, "&Banana", wxPoint(x0, y0 + dy));
		new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(x0 + dx, y0 + dy));
		// a spin control and its label
		new wxStaticText(this, wxID_STATIC, "&Cherry", wxPoint(x0, y0 + 2 * dy));
		new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxPoint(x0 + dx, y0 + 2 * dy));
		// a choice control and its label
		new wxStaticText(this, wxID_STATIC, "&Durian", wxPoint(x0, y0 + 3 * dy));
		wxString wxsChoices[] = { "Hello World!", "Goodbye World!" };
		(new wxChoice(this, wxID_ANY, wxPoint(x0 + dx, y0 + 3 * dy), wxDefaultSize, sizeof(wxsChoices)/sizeof(wxString), wxsChoices, 0))->SetSelection(0);
		// a checkbox control
		new wxCheckBox(this, wxID_ANY, "&Eggplant", wxPoint(x0, y0 + 4 * dy));
	}
};

class CApp : public wxApp
{
public:
	bool OnInit() {
		CDialog * dlg = new CDialog("buggy");
		dlg->ShowModal();
		return false;
	}
};
DECLARE_APP(CApp)
IMPLEMENT_APP(CApp)


#include <wx/wx.h>

class MyDialog : public wxDialog
{
public:
	MyDialog(wxWindow *parent, bool showAddfilter = true);
private:
	DECLARE_EVENT_TABLE()
};

MyDialog::MyDialog(wxWindow *parent, bool showAddFilter)
: wxDialog(parent, -1, "Url", wxDefaultPosition)
{
	wxBoxSizer *mainsizer = new wxBoxSizer(wxVERTICAL);
	wxString choices[] = { "Web site", "Secure web site", "News feed", "File" };
	mainsizer->Add(typeRadioBox = new wxRadioBox(this, ID_TYPE, "Resource type", wxDefaultPosition, wxDefaultSize, 4, choices, 2), 0, wxEXPAND | wxALL, 4);

	SetAutoLayout(TRUE);
	SetSizer(mainsizer);
	mainsizer->SetSizeHints(this);
	CenterOnParent();
}

 	  	 

// Build: g++ buggy.cpp -Wall $(wx-config --cxxflags --libs core,base)
#include <wx/wx.h>
#include <wx/spinctrl.h>

class CApp : public wxApp
{
public:
	bool OnInit() {
		wxDialog dlg(NULL, wxID_ANY, "buggy");
		wxTextCtrl * ctrl = new wxTextCtrl(&dlg, wxID_ANY, wxEmptyString, wxPoint(10, 10));

		wxTextValidator validator(wxFILTER_INCLUDE_LIST, &m_val);
		ctrl->SetValidator(validator);
		wxArrayString includes;
		includes.push_back(wxT("apple"));
		includes.push_back(wxT("banana"));
		includes.push_back(wxT("cherry"));
		validator.SetIncludes(includes);

		ctrl->SetValidator(validator);
		new wxButton(&dlg, wxID_OK, "&Ok", wxPoint(150, 10));
		dlg.ShowModal();
		return false;
	}
private:
	wxString m_val;
};
DECLARE_APP(CApp)
IMPLEMENT_APP(CApp)


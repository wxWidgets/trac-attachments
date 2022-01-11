
#include <wx/wx.h>
#include <wx/filename.h>

class DupFinderApp :public wxApp {
public:
	virtual bool OnInit();
};


IMPLEMENT_APP(DupFinderApp)


bool DupFinderApp::OnInit() {
	wxString path = _T("C:\\Program Files\\");

	wxFileName dirname = wxFileName::DirName(path);

	// this produces a wrong result
	dirname.Normalize(wxPATH_NORM_ALL | wxPATH_NORM_CASE);

	wxMessageBox(dirname.GetFullPath());

	wxFileName dirname2 = wxFileName::DirName(path);

	// this produces the right result
	dirname2.Normalize(wxPATH_NORM_ALL);
	dirname2.Normalize(wxPATH_NORM_CASE);

	wxMessageBox(dirname2.GetFullPath());

	return false;

}






















 	  	 

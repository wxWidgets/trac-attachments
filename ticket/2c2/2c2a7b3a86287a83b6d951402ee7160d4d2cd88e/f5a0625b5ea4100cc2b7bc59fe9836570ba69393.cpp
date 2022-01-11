// Build: g++ buggy.cpp -Wall $(wx-config --cxxflags --libs core,base --debug=yes)
#include <wx/wx.h>
#include <wx/filepicker.h>

class CApp : public wxApp
{
public:
	bool OnInit() {
		wxFrame * frame = new wxFrame(NULL, wxID_ANY, wxT("buggy"));
		// The wxFilePickerCtrl object will be released as expected, but its child control, a wxFileDialog, will not.
		// If builded with --debug=yes, an option of shell script wx-config, then the resource leak report will
		// show up after the application exits, assumed your version of wxGTK supports leak reports.
		// This happens on wxGTK-2.8.12.tar.gz of which the MD5 is B12C78D947D89E1120443761F1B7693B
		new wxFilePickerCtrl(frame, wxID_ANY);
		frame->Show(true);
		return true;
	}
};
DECLARE_APP(CApp)
IMPLEMENT_APP(CApp)

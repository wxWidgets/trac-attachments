#include <wx/wx.h>

struct CApp : public wxApp
{
	bool OnInit() {
		// wxDD_DIR_MUST_EXIST can't stop [Create Folder] button from showing up. It will appears after we browse to somewhere else.
		wxDirDialog dlg(
			NULL,
			"[in]message:wxString=wxDirSelectorPromptStr",
			wxEmptyString,
			wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST
		);
		dlg.ShowModal();
		return false;
	}
};
DECLARE_APP(CApp)
IMPLEMENT_APP(CApp)

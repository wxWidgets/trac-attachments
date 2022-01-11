#include <wx/wx.h>

class wx_test : public wxApp
{
	public: virtual bool OnInit()
	{
		// no problem

		wxString sep_1 = wxLocale::GetInfo(wxLOCALE_DECIMAL_POINT, wxLOCALE_CAT_NUMBER);
		wxPrintf(wxT("decimal point '") + sep_1 + wxT("'\n"));

		// debug alert

		wxLocale language;
		language.Init(wxLANGUAGE_FRENCH);

		wxString sep_2 = wxLocale::GetInfo(wxLOCALE_DECIMAL_POINT, wxLOCALE_CAT_NUMBER);
		wxPrintf(wxT("decimal point '") + sep_2 + wxT("'\n"));

		return false;
	}
};

IMPLEMENT_APP(wx_test)

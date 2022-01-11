#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/statbmp.h>

#include "time.cpng"

class PngTestApp : public wxApp
{
public:
	bool OnInit()
	{
		wxInitAllImageHandlers();
		wxFrame *frm = new wxFrame(NULL, wxID_ANY, "SchedCtrl", wxDefaultPosition, wxSize(300,200));
		frm->SetBackgroundColour( *wxWHITE );
		wxStaticBitmap *bitmap = new wxStaticBitmap( frm,  wxID_ANY, wxBITMAP_PNG_FROM_DATA( time ) );

		frm->Show();
		return true;
	}
};

IMPLEMENT_APP( PngTestApp );
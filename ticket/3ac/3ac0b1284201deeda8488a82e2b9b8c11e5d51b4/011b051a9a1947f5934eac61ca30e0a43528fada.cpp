#include <wx/wx.h>
#include <wx/log.h>

class HttpFrame : public wxFrame
{
 public:
	HttpFrame(const wxChar *title, int xpos, int ypos, int width, int height);
};

HttpFrame::HttpFrame(const wxChar *title, int xpos, int ypos, int width, int height)
: wxFrame((wxFrame *) NULL, -1, title, wxPoint(xpos, ypos), wxSize(width, height)) 
{
	wxTextCtrl * mp_BrowseSource = new wxTextCtrl (this, -1, wxString("Ici devrait se trouver\nle source de l'url."));
}

class wxCurl : public wxApp
{
 public:
	bool OnInit();
};

IMPLEMENT_APP(wxCurl)

bool wxCurl::OnInit () {

	HttpFrame *frame = new HttpFrame((wxChar*) "Hello World",-1,-1,-1,-1);
	frame->Show(TRUE);
	SetTopWindow(frame);
	return true;
}

 	  	 

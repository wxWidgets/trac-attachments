#include <wx/wx.h>
#include <wx/fontdlg.h>

class MyApp : public wxApp {
  virtual bool OnInit() {
    wxFrame *const frame = new wxFrame();
    wxFontDialog fontDialog(frame);
    return TRUE;
  }
};

IMPLEMENT_APP(MyApp)

 	  	 

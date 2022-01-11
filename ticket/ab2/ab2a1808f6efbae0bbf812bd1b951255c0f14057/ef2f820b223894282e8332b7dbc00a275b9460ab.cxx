
#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>

class MyApp: public wxApp {
    virtual bool OnInit();
};

bool MyApp::OnInit() {
    wxFrame *frame = new wxFrame( NULL, -1, "Hello World",
				  wxPoint(0,0), wxSize(200,200));
    wxSplitterWindow *splitter =
	new wxSplitterWindow(frame, -1,
			     wxPoint(0, 0), wxSize(180, 180),
			     wxSP_3D);
    
    wxTextCtrl *tw = new wxTextCtrl(splitter, -1, "top");
    wxTextCtrl *bw = new wxTextCtrl(splitter, -1, "botton");
    tw->Show(); bw->Show();
    splitter->SplitHorizontally(tw, bw);
    frame->Show(TRUE);
    SetTopWindow(frame);
    return TRUE;
}

IMPLEMENT_APP(MyApp)


 	  	 

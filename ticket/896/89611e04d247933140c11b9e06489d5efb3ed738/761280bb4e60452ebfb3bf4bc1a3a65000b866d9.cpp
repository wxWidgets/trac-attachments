
#define wxUSE_UNICODE 1

#include <wx/wx.h>
#include <wx/app.h>
#include <wx/frame.h>
#include <stdio.h>

// g++ bug.cpp `wx-config --cxxflags --libs `  -o bug && ./bug

enum {
	ID_FS = 100,
	ID_D,
};

class MyDialog : public wxDialog {
	public:
	MyDialog (wxWindow* parent) : wxDialog ( 
		parent , wxID_ANY, _("Dialog"), wxDefaultPosition, wxSize( 500,200 )
		, wxCAPTION|wxCLOSE_BOX|wxSTAY_ON_TOP
		) {

		}
	
};

class MyFrame: public wxFrame {
	public:
	MyFrame () :wxFrame( NULL, -1, _("Bug")) {
		wxMenu * m;
		wxMenuBar * mb;
		m= new wxMenu;
		m->Append (ID_FS, _("Full screen"));
		m->Append (ID_D, _("Dialog"));
		mb = new wxMenuBar;
		mb->Append(m,_("Menu"));
		SetMenuBar(mb);
	}
	~MyFrame() { }
	void fs(wxCommandEvent & evt) {
		if (IsFullScreen()) {
			ShowFullScreen(0,0);
		} else {
			ShowFullScreen(1,0);
		}
	}
	void dialog(wxCommandEvent & evt) {
		MyDialog * d;
		d = new MyDialog(this);
		d->ShowModal();
		delete d;
	}
        DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyFrame,wxFrame)
EVT_MENU(ID_FS, MyFrame::fs)
EVT_MENU(ID_D, MyFrame::dialog)
END_EVENT_TABLE()

class MyApp: public wxApp {
	virtual bool OnInit() {
		MyFrame * frame = new MyFrame ();
		frame->Show();
		SetTopWindow(frame);
		return true;
	}
};

IMPLEMENT_APP(MyApp)


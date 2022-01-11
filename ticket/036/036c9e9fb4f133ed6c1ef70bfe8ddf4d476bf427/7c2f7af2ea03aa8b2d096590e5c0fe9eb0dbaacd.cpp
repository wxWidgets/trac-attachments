#include "wx/wx.h"

class Frame : public wxFrame{
public:
	Frame::Frame() 
		:wxFrame((wxWindow *)NULL,-1,"foo",wxDefaultPosition,wxSize(320,200))
	{	
		wxStatusBar *sb = CreateStatusBar(2);

		bool test1 = sb->SetForegroundColour( wxColour(255,0,0));
		sb->SetOwnForegroundColour(wxColour(0,255,0));
		
		sb->SetStatusText("Test1",0);
		sb->SetStatusText("Test2",1);
	}

};

class App : public wxApp{

public: 
	virtual bool App::OnInit(){
		Frame *pFrame = new Frame();
		pFrame->Show(TRUE);
		SetTopWindow(pFrame);
		return TRUE;
	}
};

DECLARE_APP(App)
IMPLEMENT_APP(App)
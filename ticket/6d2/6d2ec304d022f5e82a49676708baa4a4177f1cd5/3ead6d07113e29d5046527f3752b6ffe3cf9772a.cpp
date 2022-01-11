#include "wx/wx.h"

class MyFrame : public wxFrame
{
public:
	void OnHide(wxCommandEvent &event)
	{
		Show(false);
	}
	MyFrame()
		: wxFrame(NULL, wxID_ANY, "My frame")
	{
		wxMenuBar* menuBar = new wxMenuBar;
		wxMenu* menu = new wxMenu;
		menu->Append(wxID_CLOSE, _("Hide this window"), wxEmptyString, wxITEM_NORMAL);
		menuBar->Append(menu, _("FrameMenuBar"));
		Connect(wxID_CLOSE, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction) (wxEventFunction)(wxCommandEventFunction) &MyFrame::OnHide);
	    SetMenuBar(menuBar);
	}
};

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
	{
	    if ( !wxApp::OnInit() ) return false;

		wxMenuBar* menuBar = new wxMenuBar;
		wxMenu* menu = new wxMenu;
		menuBar->Append(menu, _("GlobalMenuBar"));
		wxMenuBar::MacSetCommonMenuBar(menuBar);

		(new MyFrame())->Show();

	    return true;
	}
};

IMPLEMENT_APP(MyApp)


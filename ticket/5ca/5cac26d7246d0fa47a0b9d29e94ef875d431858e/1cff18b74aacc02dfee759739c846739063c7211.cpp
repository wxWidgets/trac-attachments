#include <wx/app.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <iostream>

class Panel : public wxPanel
{
public:
	Panel(wxWindow* parent) : wxPanel(parent, wxID_ANY)
	{
		wxNotebook* nb = new wxNotebook(this, wxID_ANY);
	}
};

class MainFrame : public wxFrame
{
public:
	MainFrame() : wxFrame(NULL, wxID_ANY, "wxWidgets Ctrl^C bug")
	{
		wxWindow* panel = new Panel(this);
	}
};

class App : public wxApp
{
	bool OnInit()
	{
		std::cout << "Type Ctrl^C to trigger the bug." << std::endl
			<< "If no wx.Notebook() have been created, the app will terminate properly." << std::endl
			<< "Otherwise, it will fail first in ::UnregisterClass(\"_wx_SysTabCtl32\")," << std::endl
			<< "(in wx/msw/private.h, line 801)	triggering a log attempt which in turn" << std::endl
			<< "triggers a failure in ::SendMessage(NULL), which itself" << std::endl
			<< "logs the error ... you see the infinite loop here. Ultimately, this" << std::endl
			<< "results in a stack overflow." << std::endl;

		wxFrame* frame = new MainFrame();
		frame->Show(true);
		SetTopWindow(frame);
		return true;
	}
};

wxIMPLEMENT_APP_CONSOLE(App);

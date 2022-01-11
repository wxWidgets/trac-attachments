#include <wx/wx.h>

class MyFrame : public wxFrame
{
public:
	MyFrame()
		: wxFrame(nullptr, wxID_ANY, wxEmptyString)
	{
		new wxTextCtrl(new wxPanel(this), wxID_ANY);
		Show(true);
	}
};

class MyApp : public wxApp
{
public:
	virtual bool OnInit()
	{
		new MyFrame();
		return true;
	}
};

wxIMPLEMENT_APP(MyApp);

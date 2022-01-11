#include <wx/wx.h>

//////////////////////////////////////////////////////////////////////////

class TestFrame: public wxFrame
{
private:

	wxTimer timer;

public:

	TestFrame()
	:
		wxFrame((wxFrame *)NULL, wxID_ANY, wxT("frame")),
		timer(this)
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
		sizer->Add(new wxButton(this, wxID_ANY, wxT("show dialog")));
		SetSizer(sizer);

		Bind(wxEVT_TIMER, &TestFrame::OnTimer, this);
		Bind(wxEVT_COMMAND_BUTTON_CLICKED, &TestFrame::OnButton, this);
	}

	void OnButton(wxCommandEvent&)
	{
		timer.Start(2000, true);

		wxDialog(this, wxID_ANY, wxT("dialog")).ShowModal();
	}

	void OnTimer(wxTimerEvent&)
	{
		Close();
	}
};

//////////////////////////////////////////////////////////////////////////

class TestApp: public wxApp
{
public:

	bool OnInit()
	{
		return (new TestFrame())->Show();
	}
};

IMPLEMENT_APP(TestApp);
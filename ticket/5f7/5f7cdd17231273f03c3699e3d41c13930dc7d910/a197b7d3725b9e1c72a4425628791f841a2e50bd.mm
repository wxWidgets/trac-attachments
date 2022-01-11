#include <wx/wx.h>

class Frame : public wxFrame
{
public:
	Frame()
		: wxFrame(NULL, wxID_ANY, "sample")
	{
		m_panel = new wxPanel(this);
		m_panel->SetBackgroundColour(*wxBLACK);
		EnableFullScreenView();
	}

private:
	void OnSize(wxSizeEvent&)
	{
		m_panel->SetSize(GetSize() + wxSize(1, 1));
	}

	wxDECLARE_EVENT_TABLE();

	wxPanel* m_panel;
};

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
	EVT_SIZE(Frame::OnSize)
wxEND_EVENT_TABLE()

class App : public wxApp
{
public:
	App()
		: m_frame(NULL)
	{}

	virtual bool OnInit()
	{
		m_frame = new Frame();
		m_frame->Show(true);
		return wxApp::OnInit();
	}

private:
	Frame* m_frame;
};

wxIMPLEMENT_APP(App);

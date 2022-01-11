#include "wx/wx.h" 

class MyApp: public wxApp
{
	// Methods
	public:
		virtual	bool			OnInit();

	protected:
	private:
};

class MyFrame: public wxFrame
{
	// Methods
	public:
								MyFrame();
							   ~MyFrame();

				void			Create(wxWindow* p_Parent);
	protected:
	private:
				void			OnFirstTextCtrl(wxCommandEvent& p_Event);
				void			OnSecondTextCtrl(wxCommandEvent& p_Event);
				void			OnSetFocus(wxFocusEvent& p_Event);
				void			OnKillFocus(wxFocusEvent& p_Event);
				void			OnClose(wxCloseEvent& p_Event);

	// Attributes
	public:
	protected:
	private:
				wxTextCtrl*		m_FirstTextCtrl;
				wxTextCtrl*		m_SecondTextCtrl;
				wxListBox*		m_LogListBox;
};

IMPLEMENT_APP(MyApp)

bool
MyApp::OnInit()
{
    if (!wxApp::OnInit()) return false;

	MyFrame* l_Frame = new MyFrame;
	l_Frame->Create(NULL);
	l_Frame->Show(true);
    return TRUE;
} 

MyFrame::MyFrame()
{
}

MyFrame::~MyFrame()
{
}

void
MyFrame::Create(wxWindow* p_Parent)
{
	wxFrame::Create(p_Parent, wxID_ANY, "FocusTest");
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MyFrame::OnClose), NULL, this);

	wxBoxSizer* l_TopSizer = new wxBoxSizer(wxVERTICAL);

	// First wxTextCtrl...
	m_FirstTextCtrl = new wxTextCtrl(this, wxID_ANY, "First wxTextCtrl");
	l_TopSizer->Add(m_FirstTextCtrl, 0, wxALL | wxEXPAND, 5);
	m_FirstTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyFrame::OnFirstTextCtrl), NULL, this);
	m_FirstTextCtrl->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(MyFrame::OnSetFocus), NULL, this);
	m_FirstTextCtrl->Connect(wxEVT_KILL_FOCUS, wxFocusEventHandler(MyFrame::OnKillFocus), NULL, this);

	// Second wxTextCtrl...
	m_SecondTextCtrl = new wxTextCtrl(this, wxID_ANY, "Second wxTextCtrl");
	l_TopSizer->Add(m_SecondTextCtrl, 0, wxALL | wxEXPAND, 5);
	m_SecondTextCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyFrame::OnSecondTextCtrl), NULL, this);
	m_SecondTextCtrl->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(MyFrame::OnSetFocus), NULL, this);
	m_SecondTextCtrl->Connect(wxEVT_KILL_FOCUS, wxFocusEventHandler(MyFrame::OnKillFocus), NULL, this);

	// Log window...
	m_LogListBox = new wxListBox(this, wxID_ANY);
	l_TopSizer->Add(m_LogListBox, 1, wxALL | wxEXPAND, 5);
	l_TopSizer->SetMinSize(wxSize(300, 300));

	SetSizer(l_TopSizer);
	l_TopSizer->SetSizeHints(this);
}

void
MyFrame::OnFirstTextCtrl(wxCommandEvent& p_Event)
{
}

void
MyFrame::OnSecondTextCtrl(wxCommandEvent& p_Event)
{
}

void
MyFrame::OnSetFocus(wxFocusEvent& p_Event)
{
	wxObject* l_Object = p_Event.GetEventObject();
	if (l_Object==m_FirstTextCtrl)
	{
		m_LogListBox->Append("First got focus...");
	}
	else
	if (l_Object==m_SecondTextCtrl)
	{
		m_LogListBox->Append("Second got focus...");
	}
	p_Event.Skip();
}

void
MyFrame::OnKillFocus(wxFocusEvent& p_Event)
{
	wxObject* l_Object = p_Event.GetEventObject();
	if (l_Object==m_FirstTextCtrl)
	{
		m_LogListBox->Append("First lost focus...");
	}
	else
	if (l_Object==m_SecondTextCtrl)
	{
		m_LogListBox->Append("Second lost focus...");
	}
	p_Event.Skip();
}

void
MyFrame::OnClose(wxCloseEvent& p_Event)
{
	Destroy();
}

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

const long ID_BUTTON1 = wxNewId();
const long ID_BUTTON2 = wxNewId();

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

	void OnButtonAddClick(wxCommandEvent& event);
	void OnButtonDelClick(wxCommandEvent& event);
 
private:

    wxButton *Button1, *Button2;
    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)
/////////////////////////////////////////////////////
bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

	MyFrame *frame = new MyFrame(wxT("ToolTip wxWidgets sample"),
                                 wxPoint(50, 50), wxSize(450, 340));
    if (frame) frame->Show(true);
    return true;
}

/////////////////////////////////
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, wxID_ANY, title, pos, size)
{
	Button1 = new wxButton(this, ID_BUTTON1, _("+"), wxPoint(10,120), wxSize(24,24), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Button2 = new wxButton(this, ID_BUTTON2, _("-"), wxPoint(34,120), wxSize(24,24), 0, wxDefaultValidator, _T("ID_BUTTON2"));

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MyFrame::OnButtonAddClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MyFrame::OnButtonDelClick);

	SetToolTip(wxT("1"));
}

// event handlers
void MyFrame::OnButtonAddClick(wxCommandEvent& WXUNUSED(event))
{
	wxString text = GetToolTipText();
	SetToolTip(text+wxT(" 1"));
}

void MyFrame::OnButtonDelClick(wxCommandEvent& WXUNUSED(event))
{
	wxString text = GetToolTipText();
	if (text.Len()>1)
		SetToolTip(text.SubString(0, text.Len()-2));
}

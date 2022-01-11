#include "wx/wx.h"

class MyApp: public wxApp
{
public:
	bool OnInit();
};

class MyFrame: public wxFrame
{
public:
    MyFrame();

    void OnSize(wxSizeEvent& event);
    void Init();
    void OnOpen(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_SIZE(MyFrame::OnSize)
    EVT_MENU(wxID_OPEN, MyFrame::OnOpen)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxApp::OnInit();
    MyFrame* frame = new MyFrame;
    frame->Init();
    return true;
}

MyFrame::MyFrame() : wxFrame(0, 0, wxEmptyString)
{
	SetClientSize(800, 256);
}

void MyFrame::Init()
{
	Show(true);
	Update();
	GetEventHandler()->AddPendingEvent(wxCommandEvent(wxEVT_COMMAND_MENU_SELECTED, wxID_OPEN));
}

void MyFrame::OnSize(wxSizeEvent& event)
{
	printf("Size: %d %d\n", event.GetSize().GetWidth(), event.GetSize().GetHeight());
}

void MyFrame::OnOpen(wxCommandEvent& event)
{
        SetClientSize(wxSize(608, 686));
	printf("New Size: %d %d\n", GetSize().GetWidth(), GetSize().GetHeight());
        SetMaxSize(GetSize());
	Center(wxBOTH);
}

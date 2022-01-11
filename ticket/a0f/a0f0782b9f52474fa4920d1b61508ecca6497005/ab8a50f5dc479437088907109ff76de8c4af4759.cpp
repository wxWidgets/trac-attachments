
#include <wx/wx.h>

// compile with g++ $(wx-config-3.0 --cxxflags --libs) label-size.cpp

class MyFrame: public wxFrame {
public:
    MyFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition,
        const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);

    void OnTimer(wxTimerEvent& event);

private:
    wxDECLARE_EVENT_TABLE();

protected:
    wxStaticText* text1;
    wxStaticText* text2;
    wxTimer* timer;
};

enum {
    TIMER_ID = wxID_HIGHEST
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_TIMER(TIMER_ID, MyFrame::OnTimer)
wxEND_EVENT_TABLE()

MyFrame::MyFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, style)
{
    text1 = new wxStaticText(this, wxID_ANY, "label1");
    text2 = new wxStaticText(this, wxID_ANY, "label2");
    timer = new wxTimer(this, TIMER_ID);

    text1->SetBackgroundColour("white");
    text2->SetBackgroundColour("pink");

    SetTitle("LabelSize");
    SetSize(wxSize(200, 200));

    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
    hbox->Add(text1, 0, 0, 0);
    hbox->Add(text2, 0, 0, 0);
    SetSizer(hbox);
    Layout();

    timer->Start(100);
}

void MyFrame::OnTimer(wxTimerEvent& event)
{
    text1->SetLabel("label1");
    text2->SetLabel("label2");
    Layout();
}

class MyApp: public wxApp {
public:
    bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();
    MyFrame* frame = new MyFrame(NULL, wxID_ANY, wxEmptyString);
    SetTopWindow(frame);
    frame->Show();
    return true;
}


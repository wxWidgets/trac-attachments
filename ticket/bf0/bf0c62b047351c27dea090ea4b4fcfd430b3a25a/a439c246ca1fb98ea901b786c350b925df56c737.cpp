// example demonstrating problems with setting text attributes inside EVT_TEXT handler.
// Application is supposed to alternate between red and green text color upon every change in text.
// However, this doesn't work for text inserted by WriteText().
// (see further comments in code)

#include <wx/wx.h>

class MyApp : public wxApp
{
  public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
    wxTextCtrl *text;
    void OnText(wxCommandEvent& event);
    void OnButton(wxCommandEvent& event);
public:
    MyFrame();
};

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame() : wxFrame(0, -1, wxT("EVT_TEXT"), wxDefaultPosition, wxSize(500, 300))
{
    text = new wxTextCtrl(this, -1, wxT("initial text"), wxPoint(0, 0), wxSize(500, 200), wxTE_MULTILINE);
    text->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyFrame::OnText), 0, this);

    wxButton *button = new wxButton(this, -1, wxT("Insert text"), wxPoint(10, 210), wxSize(180, 20));
    button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnButton), 0, this);

    // default style thru entire runtime is blue text color
    text->SetDefaultStyle(wxTextAttr(*wxBLUE));
}

// on every EVT_TEXT (wx_EVT_COMMAND_TEXT_UPDATED), always try to colorize entire text with alternating red / green color.
// this works well for text typed by user, or pasted text which doesn't have color info associated.
void MyFrame::OnText(wxCommandEvent& event)
{
    static bool flip_color = true;
    flip_color = !flip_color;
    wxTextAttr attr(flip_color ? *wxRED : *wxGREEN);
    text->SetStyle(0, text->GetLastPosition(), attr);
}

// this will trigger handler, which will colorize entire text (including inserted text) to red or green
// but afterwards, the WriteText() will change color of inserted text to default (blue color)
void MyFrame::OnButton(wxCommandEvent& event)
{
    text->WriteText(wxT(" <inserted by button> "));
}


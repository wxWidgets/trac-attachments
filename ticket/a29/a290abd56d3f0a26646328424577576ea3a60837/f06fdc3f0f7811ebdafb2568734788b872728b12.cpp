#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
};
wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Test", wxPoint(50, 50), wxSize(450, 340) );
    frame->Show( true );
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{

    wxPanel *panel = new wxPanel(this, -1);

    wxColour bgColour(255, 255, 175, 255);
    wxColour fgColour(0, 0, 0, 255);
    wxFont font(11, 70, 90, 90, false, "Cantarell");

    wxTextCtrl *textCtrl = new wxTextCtrl(this, -1);
    textCtrl->SetBackgroundColour(bgColour);
    textCtrl->SetForegroundColour(fgColour);
    textCtrl->SetFont(font);
    textCtrl->Hide();

    textCtrl->SetSize(30, 30, 150, -1);
    textCtrl->Show();
}


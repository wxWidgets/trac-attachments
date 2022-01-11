#include <wx/wx.h>
#include <wx/stc/stc.h>

class App : public wxApp
{
public:
    bool OnInit();
};

IMPLEMENT_APP(App)

class Frame : public wxFrame
{
public:
    Frame() : wxFrame(NULL, wxID_ANY, _T("test"))
    {
        new wxStyledTextCtrl(this, wxID_ANY);
    }
};

bool App::OnInit()
{
    Frame *frame = new Frame;
    frame->Show();
    return true;
}

 	  	 

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


#include <wx/app.h>
#include <wx/clipbrd.h>
#include <wx/defs.h>


// AssertHandler --------------------------------------------


void assertHandler(
    const wxString &file, int line, const wxString &func,
    const wxString &cond, const wxString &msg)
{
    std::cout << "assertion failed: "
        << file << " / "
        << line << " / "
        << func << " / "
        << cond << " / "
        << msg << std::endl;
}


// Frame ----------------------------------------------------


class CustomFrame : public wxFrame
{
public:
    CustomFrame()
    : wxFrame(NULL, 1, wxT("CustomFrame"))
    {
        wxTimer *timer = new wxTimer(this, 1);
        timer->Start(10);

        wxSleep(2);

        // simple clipboard operation (calls wxGUIEventLoop::YieldFor)
        wxTheClipboard->IsSupported(wxDF_TEXT);
    }

    void OnTimerTimeout(wxTimerEvent& event)
    {
        // simple clipboard operation (reentry)
        wxTheClipboard->IsSupported(wxDF_TEXT);
    }

    DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(CustomFrame, wxFrame)
  EVT_TIMER(1, CustomFrame::OnTimerTimeout)
END_EVENT_TABLE()


// App ------------------------------------------------------


class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        wxSetAssertHandler(assertHandler);
        CustomFrame *frame = new CustomFrame();
        frame->Show();

        return true;
    }
};


IMPLEMENT_APP(MyApp);



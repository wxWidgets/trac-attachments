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
    {}
    
    void OnShow(wxShowEvent& event)
    {
        // simple clipboard operation with reentry
        wxTheClipboard->IsSupported(wxDF_TEXT);
    }
    
    DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(CustomFrame, wxFrame)
  EVT_SHOW(CustomFrame::OnShow)
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
        
        // Activate or deactivate the following line to switch
        // between the 2 stacktraces:
        // With sleep:    Stacktrace through g_timeout_dispatch
        //                and request_frame_extents_timeout
        // Without sleep: Stacktrace through wxgtk_main_do_event
        wxSleep(3);

        return true;
    }
    
    virtual void OnEventLoopEnter(wxEventLoopBase *loop)
    {
        // simple clipboard operation (calls wxGUIEventLoop::YieldFor)
        wxTheClipboard->IsSupported(wxDF_TEXT);
        
        // Note: It may be unorthodox to do clipboard operations
        // in OnEventLoopEnter, but this is not the root of the
        // problem. There are a thousand other ways to reproduce the
        // problem, but they all depend heavily on the timing and are
        // therefore not suitable for this bug report (unreliable).
    }
};


IMPLEMENT_APP(MyApp);



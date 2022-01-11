#include "wx/wx.h"

class MyApp: public wxApp
{
    virtual bool OnInit();
    
    wxFrame *frame;
	
};

#define kNumTimersPerFrame 10
#define kNumFrames         10

class TimerFrame:  public wxFrame
{
public:
    TimerFrame(wxWindow *parent,
               wxWindowID winid,
               const wxString& title,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize);
    virtual ~TimerFrame(){}
  	void OnTimer(wxTimerEvent& e);
    
private:
    
    wxTimer* mTimer[kNumTimersPerFrame];
    
public:
    DECLARE_EVENT_TABLE()
    
};

IMPLEMENT_APP(MyApp)


BEGIN_EVENT_TABLE(TimerFrame, wxFrame)
EVT_TIMER(100, TimerFrame::OnTimer)
END_EVENT_TABLE()


TimerFrame::TimerFrame(wxWindow *parent,
                       wxWindowID winid,
                       const wxString& title,
                       const wxPoint& pos,
                       const wxSize& size):
wxFrame(parent,winid,title,pos,size)
{
    int i;
    for(i = 0; i < kNumTimersPerFrame; i++){
        mTimer[i] = new wxTimer(this, 100);
        mTimer[i]->Start(i*20 + 20);
    }
}

bool MyApp::OnInit()
{
    int i;
    wxPanel* panel;
    
    
    frame = new wxFrame(NULL, -1,  wxT("Hello wxWidgets"), wxPoint(50,50), wxSize(800,600));
	
    frame->Show();
    for(i = 0;i < kNumFrames;i++){
        
        frame = new TimerFrame(frame, -1,  wxT("timerframe"), wxPoint(50+i*20,50), wxSize(800,600));
        panel = new wxPanel(frame, -1, wxPoint(i*80,i*60),wxSize(80,60));
        frame->Show();
    }
    return true;
}

void TimerFrame::OnTimer(wxTimerEvent& e)
{
}
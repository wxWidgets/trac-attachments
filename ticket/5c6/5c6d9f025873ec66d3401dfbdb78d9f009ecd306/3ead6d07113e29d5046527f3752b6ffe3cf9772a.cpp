#include "wx/wx.h"

#define BUTTON_SELECT  1000
#define BUTTON_SELECT2 1001
//#define SAME_IDS

class Frame: public wxFrame
{
public:
    Frame(): wxFrame(NULL, wxID_ANY, _T("Frame"),
                     wxDefaultPosition, wxSize(450, 340))
    {
        wxButton *b;

        b = new wxButton(this, BUTTON_SELECT, _T("sin"), wxPoint(5, 5));
        b->SetBackgroundColour(wxColour(200, 200, 150));
#ifdef SAME_IDS
        b = new wxButton(this, BUTTON_SELECT, _T("cos"), wxPoint(5, 105));
#else
        b = new wxButton(this, BUTTON_SELECT2, _T("cos"), wxPoint(5, 105));
#endif
        b->SetBackgroundColour(wxColour(50, 150, 150));
    }

private:
    void OnButton(wxCommandEvent& event)
    {
        wxLogMessage(((wxButton*)event.GetEventObject())->GetLabel());
    }

    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(Frame, wxFrame)
#ifdef SAME_IDS
    EVT_BUTTON(BUTTON_SELECT, Frame::OnButton)
#else
    EVT_COMMAND_RANGE(BUTTON_SELECT, BUTTON_SELECT2, wxEVT_COMMAND_BUTTON_CLICKED, Frame::OnButton)
#endif
END_EVENT_TABLE()

class App: public wxApp
{
    bool OnInit()
    {
        Frame *frame = new Frame();
        frame->Show(true);
        return true;
    }
};

IMPLEMENT_APP(App)

 	  	 

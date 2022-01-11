#include "wx/wx.h"
#include "wx/timer.h"
#include <iostream>

#define TIMER_ID 1000 
 
class ScrolledWidgetsPane : public wxScrolledWindow
{
public:
    ScrolledWidgetsPane(wxWindow* parent, wxWindowID id) : 
		wxScrolledWindow(parent, id),
		m_timer(this, TIMER_ID)
    {
		SetScrollbars(10, 10, 100, 100, 0, 0);

        for (int w=1; w<=120; w++)
        {
            wxCheckBox* b = new wxCheckBox(this, wxID_ANY, wxT(""), wxPoint(w*15, w*15));
        }
 
		//DoAdjustScollbars();                                   // Instant
		//CallAfter(&ScrolledWidgetsPane::DoAdjustScollbars);    // Almost instant
		m_timer.Start(5000);                                     // Later (5 seconds)
    }

	void DoAdjustScollbars()
	{
		SetScrollbars(10, 10, 100, 100, 0, 10);
	}

	void OnTimer(wxTimerEvent& event)
	{
		DoAdjustScollbars();
		m_timer.Start(5000);
	}

	DECLARE_EVENT_TABLE()

private: 
	 wxTimer m_timer;
 
};

class MyApp: 
	public wxApp
{
public:
 
    bool OnInit()
    {
        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
        frame = new wxFrame((wxFrame *)NULL, -1,  wxT("Scrolling Widgets"), wxPoint(50,50), wxSize(650,650));
 
        ScrolledWidgetsPane* my_image = new ScrolledWidgetsPane(frame, wxID_ANY);
        sizer->Add(my_image, 1, wxEXPAND);
        frame->SetSizer(sizer);
 
        frame->Show();
        return true;
    } 

private:
    wxFrame *frame;
};
 
BEGIN_EVENT_TABLE(ScrolledWidgetsPane, wxScrolledWindow)
	EVT_TIMER(TIMER_ID, ScrolledWidgetsPane::OnTimer) 
END_EVENT_TABLE()
 
IMPLEMENT_APP(MyApp)

// Build command: g++ a.cpp -Wall $(wx-config --cxxflags --libs core)
#include <wx/wx.h>
#include <wx/busyinfo.h>

class CApp : public wxApp
{
public:
	bool OnInit() {
		// Create a busy info.
		wxBusyInfo wait("Please wait, working...");
		wxSleep(3); // Simulate doing something lengthy.
		// Don't need to enter the message loop.
		return false;
	}
};
DECLARE_APP(CApp)
IMPLEMENT_APP(CApp)

/*	Compile & run this with the command line:
 *		g++ a.cpp $(wx-config --cxxflags --libs base) && ./a.out
 */
#include <wx/wx.h>
#include <wx/stackwalk.h>

class CStackWalker : public wxStackWalker
{
protected:
	void OnStackFrame(const wxStackFrame & frame) {
		::wxLogMessage(wxT("%u: %s(%i)\t%s"),
			frame.GetLevel(),
			frame.GetFileName().c_str(),
			frame.GetLine(),
			frame.GetName().c_str()
		);
	}
};

struct CApp : public wxApp
{
	int OnRun() {
		CStackWalker sw;
		sw.Walk(); // Show call stack
		return 0;
	}
};
DECLARE_APP(CApp)
IMPLEMENT_APP(CApp)

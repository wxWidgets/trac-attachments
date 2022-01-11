// Valgrind might be needed to observe the memory leaks.
// You can download Valgrind it from http://valgrind.org/
#include <wx/wx.h>
#include <wx/fs_inet.h>

class CApp : public wxApp
{
public:
	bool OnInit() {
		// Initialization
		wxInitAllImageHandlers();
		wxFileSystem::AddHandler(new wxInternetFSHandler);
		// Acquire an image from Internet.
		wxFileSystem fs;
		wxFSFile * file = fs.OpenFile("http://trac.wxwidgets.org/chrome/site/logo9.jpg");
		m_bmp = wxImage(*file->GetStream());
		delete file;
		wxFileSystem::CleanUpHandlers();
		// Create a frame and then enter the message loop.
		wxFrame * frame = new wxFrame(NULL, wxID_ANY, "buggy");
		frame->Centre(wxBOTH);
		frame->Show(true);
		return true;
	}
protected:
	void frame_OnPaint(wxPaintEvent & evt) {
		wxPaintDC dc(dynamic_cast<wxFrame *>(evt.GetEventObject()));
		dc.DrawBitmap(m_bmp, 0, 0);
	}
private:
	wxBitmap m_bmp;
DECLARE_EVENT_TABLE()
};
DECLARE_APP(CApp)
IMPLEMENT_APP(CApp)
BEGIN_EVENT_TABLE(CApp, wxApp)
	EVT_PAINT(CApp::frame_OnPaint)
END_EVENT_TABLE()

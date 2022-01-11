#include <wx/app.h>
#include <wx/frame.h>
#include <wx/dcmemory.h>

/*****************************************************************************/

class GUITest : public wxApp
	{
	public:
		bool OnInit();
	};

DECLARE_APP(GUITest)

/*****************************************************************************/

class TestWindow : public wxFrame
	{
	public:
		TestWindow(const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = wxT("frame"));
		~TestWindow();
	
	protected:
		void OnPaint(wxPaintEvent& ev);
		
		DECLARE_EVENT_TABLE()
	};

/*****************************************************************************/

IMPLEMENT_APP(GUITest)

bool GUITest::OnInit()
	{
	SetAppName(wxT("GUITest"));
	
	if (!wxApp::OnInit())
		return (false);
	
	TestWindow* w = new TestWindow(GetAppName());
	w->Show();
	
	SetTopWindow(w);
	
	return (true);
	}

/*****************************************************************************/

TestWindow::TestWindow(const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxFrame(NULL, wxID_ANY, title, pos, size, style, name)
	{
	SetSize(320, 200);
	}

TestWindow::~TestWindow()
	{
	}

void TestWindow::OnPaint(wxPaintEvent& ev)
	{
	wxPaintDC dc(this);
	
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
	
	const int w = 98;
	const int h = 98;
	
	wxBitmap bmp(w, h);
	wxBitmap mask(w, h, 1);
	wxMemoryDC mdc;
	
	mdc.SelectObject(bmp);
	mdc.SetBackground(*wxRED_BRUSH);
	mdc.Clear();
	
	mdc.SelectObject(mask);
	mdc.SetBackground(*wxBLACK_BRUSH);
	mdc.Clear();
	mdc.SetBrush(*wxWHITE_BRUSH);
	mdc.DrawCircle(w / 2, h / 2, w / 4);
	
	bmp.SetMask(new wxMask(mask));
	
	mdc.SelectObject(bmp);
	dc.Blit(10, 10, w, h, &mdc, 0, 0, wxCOPY, true);
	
	mdc.SelectObject(mask);
	mdc.SetBackground(*wxWHITE_BRUSH);
	mdc.Clear();
	mdc.SetBrush(*wxBLACK_BRUSH);
	mdc.DrawCircle(w / 2, h / 2, w / 4);
	
	bmp.SetMask(new wxMask(mask));
	
	mdc.SelectObject(bmp);
	dc.Blit(w+20, 10, w, h, &mdc, 0, 0, wxCOPY, true);
	}

BEGIN_EVENT_TABLE(TestWindow, wxFrame)
	EVT_PAINT(TestWindow::OnPaint)
END_EVENT_TABLE()

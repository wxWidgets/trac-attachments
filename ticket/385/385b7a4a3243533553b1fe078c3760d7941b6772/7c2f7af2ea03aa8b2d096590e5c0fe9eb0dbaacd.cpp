#include <wx/app.h>
#include <wx/bitmap.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/aui/auibar.h>
#include <wx/aui/framemanager.h>
#include <wx/artprov.h>

class MyApp : public wxApp
{
public:
	bool OnInit() wxOVERRIDE;
};

wxDECLARE_APP(MyApp);
wxIMPLEMENT_APP(MyApp);

#if 0
class FixedToolbar : public wxAuiToolBar
{
public:
	using wxAuiToolBar::wxAuiToolBar;
protected:
	void DoSetSize(int x, int y, int w, int h, int f) override
	{
		wxWindow::DoSetSize(x, y, w, h, f);
	}
};
#else
typedef wxAuiToolBar FixedToolbar;
#endif

class TestPanel : public wxPanel
{
public:
	enum IDS
	{
		ID_SampleItem = 1000
	};

	TestPanel(wxWindow* p) : wxPanel(p)
	{
		m_mgr.SetManagedWindow(this);
		m_mgr.SetFlags(wxAUI_MGR_DEFAULT | wxAUI_MGR_LIVE_RESIZE);

		wxAuiToolBar* tb1 = new FixedToolbar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
			wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW);
		tb1->SetToolBitmapSize(wxSize(48, 48));
		tb1->AddTool(ID_SampleItem + 1, wxT("Test"), wxArtProvider::GetBitmap(wxART_ERROR));
		tb1->AddSeparator();
		tb1->AddTool(ID_SampleItem + 2, wxT("Test"), wxArtProvider::GetBitmap(wxART_QUESTION));
		tb1->AddTool(ID_SampleItem + 3, wxT("Test"), wxArtProvider::GetBitmap(wxART_INFORMATION));
		tb1->AddTool(ID_SampleItem + 4, wxT("Test"), wxArtProvider::GetBitmap(wxART_WARNING));
		tb1->AddTool(ID_SampleItem + 5, wxT("Test"), wxArtProvider::GetBitmap(wxART_MISSING_IMAGE));
		tb1->Realize();

		m_mgr.AddPane(tb1, wxAuiPaneInfo().ToolbarPane().Top().
			LeftDockable(true).RightDockable(true).BottomDockable(false).Floatable(false));
		m_mgr.AddPane(new wxPanel(this), wxAuiPaneInfo().CenterPane());
		m_mgr.Update();
	}

	~TestPanel()
	{
		m_mgr.UnInit();
	}

private:
	wxAuiManager m_mgr;
};

class Test : public wxFrame
{
public:

	Test()
		: wxFrame(nullptr, wxID_ANY, "Test Window")
	{
		m_mgr.SetManagedWindow(this);
		m_mgr.SetFlags(wxAUI_MGR_DEFAULT | wxAUI_MGR_LIVE_RESIZE);

		m_mgr.AddPane(new TestPanel(this), wxAuiPaneInfo().Left().
			LeftDockable(true).RightDockable(true).BottomDockable(false).Floatable(false));
		m_mgr.AddPane(new wxPanel(this), wxAuiPaneInfo().CenterPane());
		m_mgr.Update();
	}

	~Test()
	{
		m_mgr.UnInit();
	}

private:
	wxAuiManager m_mgr;
};


bool MyApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	Test* t = new Test();
	t->Show();

	return true;
}
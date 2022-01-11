/////////////////////////////////////////////////////////////////////////////
// Name:        toolbarbug.cpp
// Purpose:     Minimalistic Example which demonstrates the following bug
//              when wxToolBar is used together with wxAui.
// Author:      Michael Heilmann
// Modified by:
// Created:     12/07/2008
// Copyright:   (c) Michael Heilmann
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/artprov.h>
#include <wx/aui/aui.h>

/*---------------------------------------------------------------------------------------------------------*/
// HEADER

enum
{
	ID_ShowNormal = wxID_HIGHEST,
    ID_ShowBug,
    ID_ShowWorkaround,
};

class MyApp : public wxApp
{
public:
	bool OnInit();
};

class MyFrame : public wxFrame
{
public:
	MyFrame(wxFrame *parent,
		wxWindowID id = wxID_ANY,
		const wxString& title = _T("wxToolBar Bug Demo"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_FRAME_STYLE|wxCLIP_CHILDREN|wxNO_FULL_REPAINT_ON_RESIZE);
	virtual ~MyFrame();
	void OnShowNormal(wxCommandEvent& WXUNUSED(event));
	void OnShowBug(wxCommandEvent& WXUNUSED(event));
	void OnShowWorkaround(wxCommandEvent& WXUNUSED(event));
	wxToolBar *m_tb;
	wxAuiManager m_mngr;

	DECLARE_EVENT_TABLE()
};

/*---------------------------------------------------------------------------------------------------------*/
// SOURCE

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	MyFrame* frame = new MyFrame((wxFrame *) NULL, wxID_ANY,
		_T("wxToolbar Bug Demo"),
		wxPoint(100, 100), wxSize(550, 300));

	frame->Show(true);

	wxInitAllImageHandlers();

	SetTopWindow(frame);

	return true;
}

BEGIN_EVENT_TABLE(MyFrame,wxFrame)
	EVT_MENU(ID_ShowNormal, MyFrame::OnShowNormal)
    EVT_MENU(ID_ShowBug, MyFrame::OnShowBug)
    EVT_MENU(ID_ShowWorkaround,	MyFrame::OnShowWorkaround)
END_EVENT_TABLE()

MyFrame::MyFrame(wxFrame* parent,
				 wxWindowID id,
				 const wxString& title,
				 const wxPoint& pos,
				 const wxSize& size,
				 long style)
				 : wxFrame(parent, id, title, pos, size, style),m_tb(0)
{
	m_mngr.SetManagedWindow(this);
	wxMenu *menuFile=new wxMenu;
	menuFile->Append(ID_ShowNormal,wxT("Show Normal"));
	menuFile->Append(ID_ShowBug,wxT("Show Bug"));
	menuFile->Append(ID_ShowWorkaround,wxT("Show Workaround"));
	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(menuFile,wxT("Mode"));
	SetMenuBar(menuBar);
	m_mngr.Update();
}

void MyFrame::OnShowNormal(wxCommandEvent& WXUNUSED(event))
{
	// Revert MyFrame to original state: no toolbar or anything added
	if(m_tb) 
	{ 
		// This part is anyway weird and feels pretty much buggy:
		// Basically it seems like, that if DetachPane is called for a
		// toolbar it is still associated with the frame but it is not
		// returns by GetToolBar. I hope this will not crash under Mac/Linux.
		//
		// For the user which does not try a lot, the docs are not sufficient.
		m_mngr.DetachPane(m_tb);
		m_tb->Reparent(NULL);
		m_tb->Destroy();m_tb=NULL;
		m_mngr.Update();
	}

	m_tb=new wxToolBar(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTB_FLAT|wxTB_NODIVIDER);
	m_tb->AddTool(wxID_ANY,wxT("tool1"),wxArtProvider::GetBitmap(wxART_FILE_OPEN,wxART_TOOLBAR));
	m_tb->AddTool(wxID_ANY,wxT("tool2"),wxArtProvider::GetBitmap(wxART_FILE_SAVE,wxART_TOOLBAR));
	m_tb->Realize();
	wxAuiPaneInfo pi = wxAuiPaneInfo()	.Name(wxT("toolbar"))
										.Caption(wxT("toolbar"))
										.ToolbarPane()
										.Floatable()
										.Direction(wxAUI_DOCK_TOP) // see also ticket #9722
										.LeftDockable(false)
										.RightDockable(false);
	m_mngr.AddPane(m_tb,pi);
	m_mngr.Update();
}

void MyFrame::OnShowBug(wxCommandEvent& WXUNUSED(event))
{
	// Revert MyFrame to original state: no toolbar or anything added
	if(m_tb) 
	{ 
		// This part is anyway weird and feels pretty much buggy:
		// Basically it seems like, that if DetachPane is called for a
		// toolbar it is still associated with the frame but it is not
		// returns by GetToolBar. I hope this will not crash under Mac/Linux.
		//
		// For the user which does not try a lot, the docs are not sufficient.
		m_mngr.DetachPane(m_tb);
		m_tb->Reparent(NULL);
		m_tb->Destroy();m_tb=NULL;
		m_mngr.Update();
	}
	
	m_tb=new wxToolBar(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTB_FLAT|wxTB_NODIVIDER);
	wxAuiPaneInfo pi = wxAuiPaneInfo()	.Name(wxT("toolbar"))
										.Caption(wxT("toolbar"))
										.ToolbarPane()
										.Floatable()
										.Direction(wxAUI_DOCK_TOP) // see also ticket #9722
										.LeftDockable(false)
										.RightDockable(false);
	m_mngr.AddPane(m_tb,pi);
	m_mngr.Update();

	m_tb->AddTool(wxID_ANY,wxT("tool1"),wxArtProvider::GetBitmap(wxART_FILE_OPEN,wxART_TOOLBAR));
	m_tb->AddTool(wxID_ANY,wxT("tool2"),wxArtProvider::GetBitmap(wxART_FILE_SAVE,wxART_TOOLBAR));
	m_tb->Realize();
	
	m_mngr.Update();

	// Result: toolbar is not displayed properly.
}

void MyFrame::OnShowWorkaround(wxCommandEvent& WXUNUSED(event))
{
	// Revert MyFrame to original state: no toolbar or anything added
	if(m_tb) 
	{ 
		// This part is anyway weird and feels pretty much buggy:
		// Basically it seems like, that if DetachPane is called for a
		// toolbar it is still associated with the frame but it is not
		// returns by GetToolBar. I hope this will not crash under Mac/Linux.
		//
		// For the user which does not try a lot, the docs are not sufficient.
		m_mngr.DetachPane(m_tb);
		m_tb->Reparent(NULL);
		m_tb->Destroy();m_tb=NULL;
		m_mngr.Update();
	}
	
	m_tb=new wxToolBar(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTB_FLAT|wxTB_NODIVIDER);
	wxAuiPaneInfo pi = wxAuiPaneInfo()	.Name(wxT("toolbar"))
										.Caption(wxT("toolbar"))
										.ToolbarPane()
										.Floatable()
										.Direction(wxAUI_DOCK_TOP) // see also ticket #9722
										.LeftDockable(false)
										.RightDockable(false);
	m_mngr.AddPane(m_tb,pi);
	m_tb->AddTool(wxID_ANY,wxT("tool1"),wxArtProvider::GetBitmap(wxART_FILE_OPEN,wxART_TOOLBAR));
	m_tb->AddTool(wxID_ANY,wxT("tool2"),wxArtProvider::GetBitmap(wxART_FILE_SAVE,wxART_TOOLBAR));
	m_tb->Realize();
	
	// Start Workaround: Detach and reattach
	m_mngr.DetachPane(m_tb);
	m_mngr.AddPane(m_tb,pi);
	// End Workaround: Detach and reattach

	m_mngr.Update();
}

MyFrame::~MyFrame()
{
	m_mngr.UnInit();
}
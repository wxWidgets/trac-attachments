#pragma warning ( push, 0 )
#include <wx/wxprec.h>
#pragma warning ( pop )

class wxTestApp;

// ----------------------------------------------------------------------------


enum 
{
	MENU_CHECK_ITEM = 300
};


class CMainFrame : public wxFrame
{
public:
	CMainFrame();
	~CMainFrame();

private:
	wxMenuBar * m_MenuBar;

	void OnMenuItem( wxCommandEvent & event );
	void OnMouseRightDown( wxMouseEvent & event );

	DECLARE_EVENT_TABLE()
	DECLARE_NO_COPY_CLASS( CMainFrame );
};


BEGIN_EVENT_TABLE( CMainFrame, wxFrame )
	EVT_MENU( MENU_CHECK_ITEM, CMainFrame::OnMenuItem )
	EVT_RIGHT_DOWN( CMainFrame::OnMouseRightDown )
END_EVENT_TABLE()


CMainFrame::CMainFrame()
	: wxFrame( 0, wxID_ANY, _( "wxTestApp" ))
	, m_MenuBar( new wxMenuBar())
{
	wxMenu * menu = new wxMenu();
	menu->AppendCheckItem( MENU_CHECK_ITEM, _( "checkable" ));
	m_MenuBar->Append( menu, _( "test" ));
	SetMenuBar( m_MenuBar );
}


CMainFrame::~CMainFrame()
{
}


void 
CMainFrame::OnMouseRightDown( wxMouseEvent & event )
{
	wxMenu * menu = new wxMenu();
	menu->AppendCheckItem( MENU_CHECK_ITEM, _( "checkable" ));
	menu->Check( MENU_CHECK_ITEM, m_MenuBar->IsChecked( MENU_CHECK_ITEM ));
	PopupMenu( menu, event.GetX(), event.GetY());
}


void 
CMainFrame::OnMenuItem( wxCommandEvent & event )
{
	wxString message;
	message << _( "event says: " ) << ( event.IsChecked() ? _( "checked" ) : _( "unchecked" ));
	message << _( "\nmenu says: ") << ( m_MenuBar->IsChecked( MENU_CHECK_ITEM ) ? _( "checked" ) : _( "unchecked" ));
	wxMessageBox( message );
}


// ----------------------------------------------------------------------------


class wxTestApp : public wxApp
{
public:
	wxTestApp() {}

private:
	virtual bool	OnInit();

	CMainFrame *	m_MainFrame;

	DECLARE_NO_COPY_CLASS( wxTestApp );
};


bool	
wxTestApp::OnInit()
{
	m_MainFrame = new CMainFrame();
	m_MainFrame->Show();
	return true;
}


DECLARE_APP( wxTestApp );
IMPLEMENT_APP( wxTestApp )

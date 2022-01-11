
//
// MoveTest sample, test on GTK.
// 
// Shows a dialog and red box should match bounds 
// of the window. The green box should show the client
// area. If they mismatch they show that top-level window
// positioning is not working OK (the case for wxGTK).
//
// See patch ID: 1742755 on 
// http://sourceforge.net/tracker/index.php?func=detail&aid=1742755&group_id=9863&atid=309863


#include "main.h"

#include "wx/log.h"

#define ID_MOVE_NEW		1001
#define ID_MOVE_SAME 	1002

class MoveDialog: public wxDialog {
public:
	MoveDialog( wxWindow *prnt, int id, const wxChar *title, wxPoint pos, wxSize size ) :
		wxDialog(prnt,id,title,pos,size), m_rset(pos,size) { 
		m_pmove_new = new wxButton( this, ID_MOVE_NEW, _T("Move to new rectangle"), wxPoint(0,0) );
		m_pmove_self = new wxButton( this, ID_MOVE_SAME, _T("Move to identical rectangle"), wxPoint(0,40) );
		m_rscreen_set = new wxStaticText( this, wxID_ANY, _T("Requested rect: (a,b),(c,d)   "), wxPoint(0,80) );
		m_rscreen_set->SetLabel( wxString::Format(_T("Requested rect: (%d,%d),(%d,%d)"), m_rset.x,m_rset.y,m_rset.width,m_rset.height) );
		m_rscreen_get = new wxStaticText( this, wxID_ANY, _T("Read back rect: (a,b),(c,d)   "), wxPoint(0,100) );
		m_rclient = new wxStaticText( this, wxID_ANY, _T("Client rect: (a,b,c,d)   "), wxPoint(0,120) );
		m_info_red = new wxStaticText( this, wxID_ANY, _T("Red: Read back area"), wxPoint(0,140) );
		m_info_green = new wxStaticText( this, wxID_ANY, _T("Green: Read back client area"), wxPoint(0,160) );
		
		m_timer.SetOwner(this);
		m_timer.Start( 100, false );
	}
	
	virtual ~MoveDialog(){ }
	void OnSizeMove( );
	
private:
	void OnSize( wxSizeEvent& e );
	void OnMove( wxMoveEvent& e );
	void OnTimer( wxTimerEvent& e );
	void OnMoveNew( wxCommandEvent &event );
	void OnMoveSame( wxCommandEvent &event );

	wxButton 	*m_pmove_new;
	wxButton 	*m_pmove_self;
	wxButton 	*m_pok;
	wxStaticText	*m_rscreen_set;
	wxStaticText	*m_rscreen_get;
	wxStaticText   *m_rclient;
	wxStaticText   *m_info_red;
	wxStaticText   *m_info_green;
	
	wxTimer m_timer;
	
	wxRect m_rset;	// Screen rectangle given to SetSize 
	wxRect m_rget;	// Screen rectangle from GetScreenRect

	DECLARE_EVENT_TABLE();
};


BEGIN_EVENT_TABLE(MoveDialog, wxDialog)
	EVT_SIZE(MoveDialog::OnSize)
	EVT_MOVE(MoveDialog::OnMove)
	EVT_TIMER(wxID_ANY,MoveDialog::OnTimer)
	EVT_BUTTON(ID_MOVE_NEW,MoveDialog::OnMoveNew)
	EVT_BUTTON(ID_MOVE_SAME,MoveDialog::OnMoveSame)
END_EVENT_TABLE()


void MoveDialog::OnSizeMove(  ){
	// Read back the screen rect
	m_rget = GetScreenRect();
	m_rscreen_get->SetLabel( wxString::Format(_T("Read back rect: (%d,%d),(%d,%d)"), m_rget.x,m_rget.y,m_rget.width,m_rget.height) );
	
	// Read the client rect
	wxSize sz_client = GetClientSize();
	wxRect rcl(ClientToScreen(wxPoint(0,0)),sz_client);
	m_rclient->SetLabel( wxString::Format(_T("Client rect: (%d,%d),(%d,%d)"), rcl.x,rcl.y,rcl.width,rcl.height) );
	
	wxScreenDC dc;
	int x=0,y=0;
	ClientToScreen( &x, &y );
	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	wxPen pr(wxColour(150,0,0),1);
	wxPen pg(wxColour(0,150,0),1);
	dc.SetPen(pr);
	dc.DrawRectangle(m_rget);
	dc.SetPen(pg);
	dc.DrawRectangle(rcl);
}


void MoveDialog::OnSize( wxSizeEvent& e ){
    // Give chance for things to settle down
    m_timer.Start( 100, false );
	//OnSizeMove();
}

void MoveDialog::OnMove( wxMoveEvent& e ){
    // Give chance for things to settle down
    m_timer.Start( 100, false );
	//OnSizeMove();
}

void MoveDialog::OnTimer( wxTimerEvent& e ){
	OnSizeMove();
}

void MoveDialog::OnMoveSame( wxCommandEvent& e ){
	// Set the previous coordinates
	wxRect r = GetScreenRect();
	SetSize( r );
}

#include <stdlib.h>
void MoveDialog::OnMoveNew( wxCommandEvent& e ){
	// Move to random position
	wxRect r = m_rset;
	r.x = rand()%800;
	r.y = rand()%600;
	SetSize( r );
	m_rscreen_set->SetLabel( wxString::Format(_T("Requested rect: (%d,%d),(%d,%d)   "), r.x,r.y,r.width,r.height) );
}

wxLogStderr *g_log_stderr;
wxLog *g_log_old;
class MyApp : public wxApp {
public:
	MyApp(){ }
	virtual ~MyApp(){ 
        g_log_old = wxLog::SetActiveTarget( g_log_old );
        delete g_log_stderr;
    }

	virtual bool OnInit() {
        g_log_stderr = new wxLogStderr;
        g_log_old = wxLog::SetActiveTarget( g_log_stderr );
		MoveDialog dlg(NULL,wxID_ANY,_T("Move Test"), wxPoint(200,200), wxSize(300,220));
		dlg.ShowModal();
	}
	
	DECLARE_EVENT_TABLE();
};

IMPLEMENT_APP(MyApp);

BEGIN_EVENT_TABLE(MyApp, wxApp)
    //EVT_DO_DIALOG(MyApp::OnDoDialog)
END_EVENT_TABLE()


 	  	 

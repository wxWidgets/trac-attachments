#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame 
{
private:
	
protected:
 wxRichTextCtrl* m_richText1;
 wxTextCtrl* m_textCtrl7;
 wxTextCtrl* m_textCtrl8;
 wxTextCtrl* m_textCtrl9;
 wxTextCtrl* m_textCtrl10;
 wxTextCtrl* m_textCtrl11;
 wxTextCtrl* m_textCtrl12;
 wxTextCtrl* m_textCtrl13;
 wxTextCtrl* m_textCtrl14;
	
public:
		
 MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
 ~MyFrame1();
	
};

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
 this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
 wxBoxSizer* bSizer1;
 bSizer1 = new wxBoxSizer( wxVERTICAL );
	
 m_richText1 = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
 bSizer1->Add( m_richText1, 1, wxEXPAND | wxALL, 5 );
	
 wxGridSizer* gSizer1;
 gSizer1 = new wxGridSizer( 4, 4, 0, 0 );
	
 m_textCtrl7 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
 gSizer1->Add( m_textCtrl7, 0, wxALL, 5 );
	
 m_textCtrl8 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
 gSizer1->Add( m_textCtrl8, 0, wxALL, 5 );
	
 m_textCtrl9 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
 gSizer1->Add( m_textCtrl9, 0, wxALL, 5 );
	
 m_textCtrl10 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
 gSizer1->Add( m_textCtrl10, 0, wxALL, 5 );
	
 m_textCtrl11 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
 gSizer1->Add( m_textCtrl11, 0, wxALL, 5 );
	
 m_textCtrl12 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
 gSizer1->Add( m_textCtrl12, 0, wxALL, 5 );
	
 m_textCtrl13 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
 gSizer1->Add( m_textCtrl13, 0, wxALL, 5 );
	
 m_textCtrl14 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
 gSizer1->Add( m_textCtrl14, 0, wxALL, 5 );
	
 bSizer1->Add( gSizer1, 1, wxEXPAND, 5 );
	
 this->SetSizer( bSizer1 );
 this->Layout();
	
 this->Centre( wxBOTH );
}

MyFrame1::~MyFrame1()
{
}

class MyApp : public wxApp {
public:
 virtual	bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool
MyApp::OnInit() {
	
 // create the main application window.
 MyFrame1 *frame = new MyFrame1( NULL );
	
 // show it.
 frame->Show(true);
	
 // start the event loop.
 return true;
}

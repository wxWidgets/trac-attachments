
 
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
 
#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif


class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};


class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title);

	void KeyEvent( wxKeyEvent& event );

private:

	bool show2;
	bool show3;
	wxBoxSizer*	sizer1;
	wxBoxSizer*	sizer2;
	wxBoxSizer* sizer3;

    DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_KEY_DOWN(MyFrame::KeyEvent )
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)


bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    // create the main application window
    MyFrame *frame = new MyFrame(_T("wxBoxSizer and wxFlexGridSizer problem"));

    frame->Show(true);

    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{

	// Show the problem with Sizer's and their borders not being taken out in the scrolled window
	sizer1 = new wxBoxSizer(wxVERTICAL);
	sizer2 = new wxBoxSizer(wxVERTICAL);
	sizer3 = new wxBoxSizer(wxVERTICAL);


	// Add some text into sizer2 and sizer3
	sizer2->Add( new wxStaticText( this, -1, _T("Contents of Sizer2") ), 0, wxALL | wxEXPAND, 5 );
	wxBoxSizer* newsizer = new wxBoxSizer( wxHORIZONTAL );
	sizer2->Add( newsizer, 0, wxALL | wxEXPAND, 5);

	sizer3->Add( new wxStaticText( this, -1, _T("Contents of Sizer3") ), 0, wxALL | wxEXPAND, 5 );
	newsizer = new wxBoxSizer( wxHORIZONTAL );
	sizer3->Add( newsizer, 0, wxALL | wxEXPAND, 5);


	// Add sizer2 and sizer3 onto sizer1
	sizer1->Add( new wxStaticText( this, -1, _T("Stuff before sizer2/3") ), 0, 0, 0 );
	sizer1->Add( sizer2, 0, wxALL | wxEXPAND, 25);	
	sizer1->Add( sizer3, 0, wxALL | wxEXPAND, 25);
	sizer1->Add( new wxStaticText( this, -1, _T("Stuff after sizer2/3") ), 0, 0, 0 );

	SetSizer( sizer1 );
	Layout();

	show2 = true;
	show3 = true;
}

void MyFrame::KeyEvent( wxKeyEvent& event )
{
	if( event.GetKeyCode() == WXK_SPACE  )
	{
		show2 = !show2;
		show3 = !show3;
		sizer1->Show( sizer2, show2, true );
		sizer1->Show( sizer3, show3, true );
	}

	Fit();
}

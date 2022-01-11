#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dynlib.h"
#include "test.h"

BEGIN_EVENT_TABLE( testFrame, wxFrame )
	EVT_MENU( Menu_File_Quit, testFrame::OnQuit )
	EVT_MENU( Menu_File_About, testFrame::OnAbout )
END_EVENT_TABLE()

IMPLEMENT_APP(testapp)
	
typedef void (*TestFunc)();

bool testapp::OnInit()
{
	testFrame *frame = new testFrame( wxT( "Hello World" ), wxPoint(50,50), wxSize(450,340) );

	frame->Show(TRUE);
	SetTopWindow(frame);
	return TRUE;
} 

testFrame::testFrame( const wxString& title, const wxPoint& pos, const wxSize& size )
	: wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
	wxMenu *menuFile = new wxMenu;
	
	menuFile->Append( Menu_File_About, wxT( "&About..." ) );
	menuFile->AppendSeparator();
	menuFile->Append( Menu_File_Quit, wxT( "E&xit" ) );
	
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append( menuFile, wxT( "&File" ) );
	
	SetMenuBar( menuBar );
	
	CreateStatusBar();
	SetStatusText( wxT( "Welcome to Kdevelop wxWidgets app!" ) );
}

void 
testFrame::OnQuit( wxCommandEvent& WXUNUSED( event ) )
{
	Close(TRUE);
}

void 
testFrame::OnAbout( wxCommandEvent& WXUNUSED( event ) )
{
	wxDynamicLibrary lib;
	if( lib.Load( "/home/igor/so_test/debug/src/libsotest/.libs/libso_test.so" ) )
	{
		TestFunc func = (TestFunc) lib.GetSymbol( "test" );
		if( func )
			func();
	}
	else
		wxMessageBox( "Problem loading dll!" );
	wxMessageBox( wxT( "This is a wxWidgets Hello world sample" ),
			wxT( "About Hello World" ), wxOK | wxICON_INFORMATION, this );
}


#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/app.h>
#include <wx/msgdlg.h>



class mframe : public wxFrame{
public:
	mframe( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString )
	: wxFrame( parent, id, title )
	{
		wxMenu* FileMenu = new wxMenu( wxT( "File" ) );
		wxMenuItem* mnuitm = FileMenu->Append( wxID_ANY, wxT( "Pressme" ) );
		wxMenuBar* bar = new wxMenuBar();
		bar->Append( FileMenu, wxT( "File" ) );
		SetMenuBar( bar );
		Connect(
			mnuitm->GetId(),
			wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( mframe::e_pressed ) );
	}
	void e_pressed( wxCommandEvent& event ){
    event.Skip();
		wxMessageBox( wxT( "Pressme pressed" ) );
	}
};

class MyApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{

	// MyFrame* frame = new MyFrame( wxT( "myframe" ), wxPoint( 200, 200 ), wxSize( 450, 340 ) );
	mframe* frame = new mframe( NULL );
	SetTopWindow( frame );

	frame->Show( true );

	return true;
}

int MyApp::OnExit()
{
	return wxApp::OnExit();
}

 	  	 

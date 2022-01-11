#include "wx/wx.h"
#include <wx/choicebk.h>
#include <wx/notebook.h>

class TestApp : public wxApp
{
public:

    virtual bool OnInit();
};

bool TestApp::OnInit()
{
   if( !wxApp::OnInit() )
		return false;

	wxFrame* frame = new wxFrame( NULL, wxID_ANY, "Choicebook Test" );
	
	wxNotebook* notebookCtrl = new wxNotebook( frame, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	wxPanel* panel = new wxPanel( notebookCtrl, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxChoicebook* choiceBook = new wxChoicebook( panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxCHB_DEFAULT );
	
	wxBoxSizer* boxSizer = new wxBoxSizer( wxVERTICAL );
	boxSizer->Add( choiceBook, 1, wxEXPAND | wxALL, 5 );

	panel->SetSizerAndFit( boxSizer );
	notebookCtrl->AddPage( panel, wxT("a page"), false );

	frame->Show(true);
	SetTopWindow( frame );

	return true;
}

IMPLEMENT_APP(TestApp)
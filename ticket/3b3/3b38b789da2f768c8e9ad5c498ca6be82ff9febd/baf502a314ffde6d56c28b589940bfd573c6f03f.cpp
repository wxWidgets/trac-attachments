// wx_sizer_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class MyDialog : public wxDialog
{
public:
	MyDialog()  
		: wxDialog(NULL, wxID_ANY, wxString(wxT("Test")), wxDefaultPosition, wxSize(600,400))
	{
		wxBoxSizer *topsizer = new wxBoxSizer( wxVERTICAL );

		topsizer->Add(new wxStaticText(this, -1, "Try selecting all of the text in each of these text boxes\nby clicking in the bottom right of the text area and dragging up and left and out of the control.\nThe rich text deselects as soon as the mouse\nis out of the text area.\n\n"));

		topsizer->Add(new wxStaticText(this, -1, "Works (wxTextCtrl):"));

		topsizer->Add(
			new wxTextCtrl( this, -1, "My text.", wxDefaultPosition, wxSize(100,60), wxTE_MULTILINE),
			1,            // make vertically stretchable
			wxEXPAND |    // make horizontally stretchable
			wxALL,        //   and make border all around
			10 );         // set border width to 10

		topsizer->Add(new wxStaticText(this, -1, "Doesn't work (wxRichTextCtrl):"));

		// create text ctrl with minimal size 100x60
		topsizer->Add(
			new wxRichTextCtrl( this, -1, "My text.", wxDefaultPosition, wxSize(100,60), wxTE_MULTILINE),
			1,            // make vertically stretchable
			wxEXPAND |    // make horizontally stretchable
			wxALL,        //   and make border all around
			10 );         // set border width to 10

		wxBoxSizer *button_sizer = new wxBoxSizer( wxHORIZONTAL );
		button_sizer->Add(
			new wxButton( this, wxID_OK, "OK" ),
			0,           // make horizontally unstretchable
			wxALL,       // make border all around (implicit top alignment)
			10 );        // set border width to 10
		button_sizer->Add(
			new wxButton( this, wxID_CANCEL, "Cancel" ),
			0,           // make horizontally unstretchable
			wxALL,       // make border all around (implicit top alignment)
			10 );        // set border width to 10

		topsizer->Add(
			button_sizer,
			0,                // make vertically unstretchable
			wxALIGN_CENTER ); // no border and centre horizontally

		SetSizer( topsizer );      // use the sizer for layout

		topsizer->SetSizeHints( this );   // set size hints to honour minimum size
	}
};

class MyApp : public wxApp
{
public:
	bool OnInit()
	{
		wxApp::OnInit();
		MyDialog dlg;
		dlg.ShowModal();
		return false;
	}
};

DECLARE_APP(MyApp)
IMPLEMENT_APP_CONSOLE(MyApp)

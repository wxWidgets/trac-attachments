#include <wx/wx.h>

class MyApp : public wxApp
{
	virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)


class MyFrame : public wxFrame
{
public:
	MyFrame();
	virtual void Click(wxCommandEvent & event);
private:
	wxComboBox * combo;
	wxChoice * choice;
	wxStaticText * combo_label, *choice_label, *combo_text_label, *choice_text_label;
	wxTextCtrl * combo_text, * choice_text;
	wxButton * button;
};

const int ID_PUSH = 2;

bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame();

	frame->Show(TRUE);
	SetTopWindow(frame);
	return TRUE;
}

MyFrame::MyFrame()
	: wxFrame((wxFrame*)NULL,-1,wxT("nosmart demo"))
{
	// We just create some frame with the grid sizer and some stuff.
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxGridSizer* group_sizer;
	group_sizer = new wxGridSizer( 2, 2, 0, 0 );
				
	combo_label = new wxStaticText( this, wxID_ANY, wxT("Combo:"));
	group_sizer->Add( combo_label, 0, wxALL, 5 );
							
	combo = new wxComboBox( this, wxID_ANY, wxT("one"));
	combo->Append( wxT("one") );
	group_sizer->Add( combo, 0, wxALL, 5 );
										
	choice_label = new wxStaticText( this, wxID_ANY, wxT("Choice:"));
	choice_label->Wrap( -1 );
	group_sizer->Add( choice_label, 0, wxALL, 5 );
													
	wxString m_choice1Choices[] = { wxT("one"), wxT("two") };
	int m_choice1NChoices = sizeof( m_choice1Choices ) / sizeof( wxString );
	choice = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1NChoices, m_choice1Choices, 0 );
	choice->SetSelection( 0 );
	group_sizer->Add( choice, 0, wxALL, 5 );
	button = new wxButton( this, wxID_ANY, wxT("Refresh"));
	group_sizer->Add( button, 0, wxALL, 5 );
																				
	group_sizer->Add( 0, 0, 1, wxEXPAND, 5 );
	combo_text_label = new wxStaticText( this, wxID_ANY, wxT("combo->GetStringSelection():"));
	group_sizer->Add( combo_text_label, 0, wxALL, 5 );
	combo_text = new wxTextCtrl( this, wxID_ANY );
	group_sizer->Add( combo_text, 0, wxALL, 5 );
	choice_text_label = new wxStaticText( this, wxID_ANY, wxT("choice->GetStringSelection():"));
	choice_text_label->Wrap( -1 );
	group_sizer->Add( choice_text_label, 0, wxALL, 5 );
	choice_text = new wxTextCtrl( this, wxID_ANY);
	group_sizer->Add( choice_text, 0, wxALL, 5 );
	this->SetSizer( group_sizer );

	this->Layout();
	// And we connect the events
	button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::Click), NULL, this );
}

// Refresh button is clicked...
void MyFrame::Click(wxCommandEvent & event)
{
	combo_text->SetValue(combo->GetStringSelection());
	choice_text->SetValue(choice->GetStringSelection());
	event.Skip();
}

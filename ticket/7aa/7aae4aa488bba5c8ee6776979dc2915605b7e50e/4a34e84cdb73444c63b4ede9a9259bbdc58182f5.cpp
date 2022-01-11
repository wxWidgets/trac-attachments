#include "wx/dialog.h"
#include "wx/listbox.h"
#include "wx/checkbox.h"
#include "wx/button.h"
#include "wx/sizer.h"

class TestDialog : public wxDialog
{
    TestDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style);
};

TestDialog::TestDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, style)
{
    wxPanel *m_panel = new wxPanel( this, wxID_ANY );
    wxListBox *m_tables = new wxListBox( m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_MULTIPLE );
    wxCheckBox *m_showSystem = new wxCheckBox( m_panel, wxID_ANY, _( "&Show system tables" ) );
    wxButton *m_open = new wxButton( m_panel, wxID_ANY, _( "&Open" ) );
    wxButton *m_new = new wxButton( m_panel, wxID_ANY, _( "&New..." ) );
    wxButton *m_cancel = new wxButton( m_panel, wxID_CANCEL, _( "&Cancel" ) );
    wxButton *m_help = new wxButton( m_panel, wxID_ANY, _( "&Help" ) );
    for( int i = 0; i < 24; i++ )
        m_tables->Append( "A" );
    wxBoxSizer* sizer_1 = new wxBoxSizer( wxHORIZONTAL );
    wxBoxSizer* sizer_4 = new wxBoxSizer( wxHORIZONTAL );
    wxBoxSizer* sizer_5 = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer* sizer_6 = new wxBoxSizer( wxHORIZONTAL );
    wxBoxSizer* sizer_8 = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer* sizer_7 = new wxBoxSizer( wxVERTICAL );
    sizer_4->Add( 5, 5, 0, wxEXPAND, 0 );
    sizer_5->Add( 5, 5, 0, wxEXPAND, 0 );
    sizer_7->Add( m_tables, 0, wxEXPAND, 0 );
    sizer_7->Add( 5, 5, 0, wxEXPAND, 0 );
    sizer_7->Add( m_showSystem, 0, wxEXPAND, 0 );
    sizer_6->Add( sizer_7, 1, 0, 0 );
    sizer_6->Add( 5, 5, 0, wxEXPAND, 0 );
    sizer_8->Add( m_open, 0, wxALIGN_CENTER_HORIZONTAL, 0 );
    sizer_8->Add( 5, 5, 0, wxEXPAND, 0 );
    sizer_8->Add( m_new, 0, wxALIGN_CENTER_HORIZONTAL, 0 );
    sizer_8->Add( 5, 5, 0, wxEXPAND, 0 );
    sizer_8->Add( m_cancel, 0, wxALIGN_CENTER_HORIZONTAL, 0 );
    sizer_8->Add( 5, 5, 0, wxEXPAND, 0 );
    sizer_8->Add( m_help, 0, wxALIGN_CENTER_HORIZONTAL, 0 );
    sizer_8->Add( 30, 30, 0, wxEXPAND, 0 );
    sizer_6->Add( sizer_8, 1, 0, 0 );
    sizer_5->Add( sizer_6, 1, 0, 0 );
    sizer_5->Add( 5, 5, 0, wxEXPAND, 0 );
    sizer_4->Add( sizer_5, 1, 0, 0 );
    sizer_4->Add( 5, 5, 0, wxEXPAND, 0 );
    m_panel->SetSizer( sizer_4 );
    sizer_1->Add( m_panel, 1, 0, 0 );
    SetSizer( sizer_1 );
    sizer_1->Fit( this );
    Layout();
}


MyDialog::MyDialog( wxWidnow *parent, int id, const wxString title, const wxPoint &pos, const wxSize &size, long style) : wxDialog( parent, id, title, pos,size, wxDEFULT_DIALOG_STYLE)
{
    bitmap_button_1 = new wxBitmapButton( this, wxID_ANY, wxBitmap(), wxBITMAP_TYPE_ANY );
    bitmap_button_1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyDialog::OnEnter), NULL, this );
    SetTitle( "test" );
    bitmap_button_1->SetSize( bitmap_button_1->GetBestSize() );
    wxBoxSizer *sizer = new wxBoxSizer( wxHORIZONTAL );
    sizer->Add( bitmap_button_1, 0, 0, 0 );
    SetSizer( sizer );
    sizer->Fit( this );
    Layout();
}

void MyDialog::OnEnter(wxCommandEvent &event)
{
}
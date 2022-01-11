class MyDialog1 : public wxDialog
{
   public:

      MyDialog1(wxWindow* parent)
            :wxDialog(parent, wxID_ANY, "Test")
      {
         this->SetSizeHints( wxDefaultSize, wxDefaultSize );

         wxBoxSizer* bSizer1;
         bSizer1 = new wxBoxSizer( wxVERTICAL );

         gbSizer1 = new wxGridBagSizer( 0, 0 );
         gbSizer1->SetFlexibleDirection( wxBOTH );
         gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

         bSizer1->Add( gbSizer1, 1, wxEXPAND, 5 );

         m_button1 = new wxButton( this, wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0 );
         bSizer1->Add( m_button1, 0, wxALL, 5 );

         this->SetSizer( bSizer1 );
         this->Layout();
         bSizer1->Fit( this );

         this->Centre( wxBOTH );

         m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog1::OnButton ), NULL, this );
      }

      void OnButton( wxCommandEvent& event )
      {

         wxGridBagSizer* gbSizer2;
         gbSizer2 = new wxGridBagSizer( 0, 0 );
         gbSizer2->SetFlexibleDirection( wxBOTH );
         gbSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

         gbSizer1->Add( gbSizer2, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );

         gbSizer1->Layout();
      }

   private:

      wxButton* m_button1;
      wxGridBagSizer* gbSizer1;
};
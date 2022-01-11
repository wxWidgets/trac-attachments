// called with this = dlg
void MyFrame::OnChangeSize(wxCommandEvent& event)
{
	FindWindow( ID_TREECTRL )->SetMinSize( wxSize(500,500) );
	FindWindow( ID_TREECTRL )->InvalidateBestSize();
	wxWindow *panel = FindWindow(ID_PANEL);
	
    panel->Fit();
	wxSize size = panel->GetSize();
	panel->SetMinSize( size );

    Fit();
}


 	  	 

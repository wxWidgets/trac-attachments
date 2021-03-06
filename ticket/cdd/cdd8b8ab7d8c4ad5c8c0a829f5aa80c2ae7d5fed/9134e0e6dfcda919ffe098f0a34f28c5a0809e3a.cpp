// -*- C++ -*- generated by wxGlade 0.5 on Sun Jan 29 16:05:50 2012

#include "test_bug.h"

CDialog::CDialog(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long WXUNUSED(style)):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE)
{
    // begin wxGlade: CDialog::CDialog
    panel_1 = new wxPanel(this, wxID_ANY);
    radio_btn_1 = new wxRadioButton(panel_1, wxID_ANY, wxT("Radio 1"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	radio_btn_1->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(CDialog::OnRadio1Clicked), NULL, this );
    text_ctrl_1 = new wxTextCtrl(panel_1, wxID_ANY, wxEmptyString);
    radio_btn_2 = new wxRadioButton(panel_1, wxID_ANY, wxT("Radio 2"));
	radio_btn_2->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(CDialog::OnRadio2Clicked), NULL, this );
    button_1 = new wxButton(panel_1, wxID_OK, wxT("OK"));
    button_2 = new wxButton(panel_1, wxID_CANCEL, wxT("Cancel"));

    set_properties();
    do_layout();
    // end wxGlade
}


void CDialog::set_properties()
{
    // begin wxGlade: CDialog::set_properties
    SetTitle(wxT("Test dialog"));
    radio_btn_1->SetValue(1);
    button_1->SetDefault();
    // end wxGlade
}


void CDialog::do_layout()
{
    // begin wxGlade: CDialog::do_layout
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_6 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_3 = new wxBoxSizer(wxHORIZONTAL);
    sizer_2->Add(20, 20, 0, wxEXPAND, 0);
    sizer_3->Add(20, 20, 0, wxEXPAND, 0);
    sizer_3->Add(radio_btn_1, 0, 0, 0);
    sizer_3->Add(20, 20, 0, wxEXPAND, 0);
    sizer_2->Add(sizer_3, 1, wxEXPAND, 0);
    sizer_2->Add(20, 20, 0, wxEXPAND, 0);
    sizer_4->Add(20, 20, 0, wxEXPAND, 0);
    sizer_4->Add(text_ctrl_1, 0, 0, 0);
    sizer_4->Add(20, 20, 0, wxEXPAND, 0);
    sizer_2->Add(sizer_4, 1, wxEXPAND, 0);
    sizer_2->Add(20, 20, 0, wxEXPAND, 0);
    sizer_5->Add(20, 20, 0, wxEXPAND, 0);
    sizer_5->Add(radio_btn_2, 0, 0, 0);
    sizer_5->Add(20, 20, 0, wxEXPAND, 0);
    sizer_2->Add(sizer_5, 1, wxEXPAND, 0);
    sizer_2->Add(20, 20, 0, wxEXPAND, 0);
    sizer_6->Add(20, 20, 0, wxEXPAND, 0);
    sizer_6->Add(button_1, 0, 0, 0);
    sizer_6->Add(20, 20, 0, wxEXPAND, 0);
    sizer_6->Add(button_2, 0, 0, 0);
    sizer_6->Add(20, 20, 0, wxEXPAND, 0);
    sizer_2->Add(sizer_6, 1, wxEXPAND, 0);
    sizer_2->Add(20, 20, 0, wxEXPAND, 0);
    panel_1->SetSizer(sizer_2);
    sizer_1->Add(panel_1, 1, wxEXPAND, 0);
    SetSizer(sizer_1);
    sizer_1->Fit(this);
    Layout();
    // end wxGlade
}

void CDialog::OnRadio1Clicked(wxCommandEvent &event)
{
	radio_btn_1->GetValue();
	radio_btn_2->GetValue();
}

void CDialog::OnRadio2Clicked(wxCommandEvent &event)
{
	radio_btn_1->GetValue();
	radio_btn_2->GetValue();
}

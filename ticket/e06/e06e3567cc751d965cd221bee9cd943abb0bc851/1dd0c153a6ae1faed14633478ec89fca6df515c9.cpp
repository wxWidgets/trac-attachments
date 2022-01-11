#include "wx/wx.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

wxRadioButton* MakeNotebookPage(wxNotebook* notebook, wxString name)
{
  wxPanel* panel = new wxPanel(notebook, wxID_ANY,
                                    wxDefaultPosition, wxDefaultSize);
  wxStaticBox* itemStaticBoxSizer5Static = new wxStaticBox(panel, wxID_ANY,
                                                           _("Static"));
  wxStaticBoxSizer* itemStaticBoxSizer5 = new wxStaticBoxSizer(itemStaticBoxSizer5Static,
                                                               wxVERTICAL);
  panel->SetSizer(itemStaticBoxSizer5);

  wxRadioButton *broken = new wxRadioButton(panel, wxID_ANY,
                                              _("[") + name + _("] ") +
                                              _("Should not be selected"),
                                              wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
  broken->SetValue(FALSE);
  itemStaticBoxSizer5->Add(broken, 0, wxALIGN_LEFT|wxALL, 5);

  wxRadioButton *to_be_selected = new wxRadioButton(panel, wxID_ANY,
                                                      _("[") + name + _("] ") +
                                                      _("Should be selected"),
                                                      wxDefaultPosition, wxDefaultSize,
                                                      0 );

  to_be_selected->SetValue(FALSE);
  itemStaticBoxSizer5->Add(to_be_selected, 0, wxALIGN_LEFT|wxALL, 5);

  notebook->AddPage(panel, _("Tab"));

  return to_be_selected;
}

bool MyApp::OnInit()
{
  wxFrame* other = new wxFrame(NULL, wxID_ANY, "click on the other window",
                               wxDefaultPosition, wxSize(300,50));

  wxDialog* parent = new wxDialog(other, wxID_ANY, "Radio button focus test",
                                  wxDefaultPosition, wxDefaultSize);

  wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
  parent->SetSizer(itemBoxSizer2);

  wxNotebook* itemNotebook3 = new wxNotebook(parent, wxID_ANY,
                                             wxDefaultPosition, wxDefaultSize, wxNB_TOP );

  //the broken page
  wxRadioButton *to_be_selected = MakeNotebookPage(itemNotebook3, "First");

  //the working (default selected) page
  wxRadioButton *second_to_be_selected = MakeNotebookPage(itemNotebook3, "Second");

  itemBoxSizer2->Add(itemNotebook3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

  itemNotebook3->SetSelection(1);

  //this one will appear to have not worked when it's page is selected
  to_be_selected->SetValue(TRUE);

  //this one will work even after focusing the window (did not before the original patch)
  second_to_be_selected->SetValue(TRUE);

  itemBoxSizer2->Fit(parent);
  itemBoxSizer2->SetSizeHints(parent);
  parent->Centre();

  parent->Show(true);

  other->Show(true);
  
  return true;
}

 	  	 

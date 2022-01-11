#include <wx/wx.h>
#include <wx/image.h>

class TestApp: public wxApp
{
  virtual bool OnInit();
};

class AcceleratorBug: public wxFrame {
 public:
  AcceleratorBug(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);

 private:
  void set_properties();
  void do_layout();

 protected:
  wxStaticText* lblName;
  wxTextCtrl* txtName;
  wxStaticText* lblWebPage;
  wxTextCtrl* txtWebPage;
  wxStaticText* lblNote;
  wxTextCtrl* txtNote;
  wxButton* btnNote;
  wxStaticText* lblEnable;
  wxCheckBox* chkEnabled;
  wxButton* btnSave;
  wxButton* btnCancel;
  wxPanel* panel;

}; 

IMPLEMENT_APP(TestApp)

bool TestApp::OnInit()
{
	
  AcceleratorBug *frame = new AcceleratorBug(NULL, wxID_ANY, _T("kipuamutay AcceleratorBug wxMSW-2.8"), wxDefaultPosition, wxSize(450, 450));
  frame->Show(true);
  SetTopWindow(frame);
  return true;
}

AcceleratorBug::AcceleratorBug(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE)
{

  panel = new wxPanel(this, wxID_ANY);
  lblName = new wxStaticText( panel, wxID_ANY, wxT("&Name"), wxDefaultPosition, wxDefaultSize, 0 );
  txtName = new wxTextCtrl( panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
  lblWebPage = new wxStaticText(panel, wxID_ANY, wxT("&Web Page"));
  txtWebPage = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);
  lblNote = new wxStaticText(panel, wxID_ANY, wxT("Note"));
  txtNote = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
  btnNote = new wxButton(panel, wxID_ANY, wxT("..."));
  lblEnable = new wxStaticText(panel, wxID_ANY, wxT("&Enabled"));
  chkEnabled = new wxCheckBox(panel, wxID_ANY, wxEmptyString);
  btnSave = new wxButton(panel, wxID_ANY, wxT("&Save"));
  btnCancel = new wxButton(panel, wxID_ANY, wxT("&Cancel"));

  set_properties();
  do_layout();
}


void AcceleratorBug::set_properties()
{
  SetTitle(wxT("Simple Edition"));
  btnNote->SetDefault();
  chkEnabled->SetValue(1);
}


void AcceleratorBug::do_layout()
{
  wxBoxSizer* frame_sz = new wxBoxSizer(wxVERTICAL);
  wxFlexGridSizer* panel_sz = new wxFlexGridSizer(0, 2, 5, 5);
  wxGridSizer* buttons_sz = new wxGridSizer(1, 2, 0, 5);
  wxBoxSizer* enabled_sz = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* note_sz = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* wp_sz = new wxBoxSizer(wxHORIZONTAL);
  panel_sz->Add( lblName, 0, wxALL, 5 );
  panel_sz->Add( txtName, 0, wxALL, 5 );
  panel_sz->Add(lblWebPage, 0, 0, 0);
  wp_sz->Add(txtWebPage, 1, wxALL|wxEXPAND, 0);
  panel_sz->Add(wp_sz, 1, wxEXPAND, 0);
  panel_sz->Add(lblNote, 0, 0, 0);
  note_sz->Add(txtNote, 0, 0, 0);
  note_sz->Add(btnNote, 0, 0, 0);
  panel_sz->Add(note_sz, 1, wxALL|wxEXPAND, 0);
  panel_sz->Add(lblEnable, 0, 0, 0);
  enabled_sz->Add(chkEnabled, 0, 0, 0);
  panel_sz->Add(enabled_sz, 0, 0, 0);
  buttons_sz->Add(btnSave, 0, wxALL|wxEXPAND, 0);
  buttons_sz->Add(btnCancel, 0, wxALL|wxEXPAND, 0);
  panel_sz->Add(buttons_sz, 1, wxEXPAND, 5);
  panel->SetSizer(panel_sz);
  frame_sz->Add(panel, 0, 0, 0);
  SetSizer(frame_sz);
  frame_sz->Fit(this);
  Layout();
}


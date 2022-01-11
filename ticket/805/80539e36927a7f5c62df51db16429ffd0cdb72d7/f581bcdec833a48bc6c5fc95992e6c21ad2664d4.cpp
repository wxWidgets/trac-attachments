/*
msw wxStaticBox: foreground, background, and disabled colours
---------------------------------------------------------------

- During wxDialog::Create(): calls to wxStaticBox::SetForegroundColour() and
wxStaticBox::SetBackgroundColour() have the following effect on how the static
box is shown: the label text is shown as per SetForegroundColour(), and the
WHOLE background inside of the static box AND that of the label is shown as
per SetBackgroundColour(). This is not affected by any calls to disable the
static box (see next).

- After wxDialog::Create(), and after the first time that
wxStaticBox::Enable(false) is invoked (any previous calls to Enable(true) would
have been shortcircuited because the static box is already enabled), two things
happen:
   1) the static box label text is set to black, and can no longer be changed
   by calling wxStaticBox::SetForegroundColour();

   2) the background of the static box label (but not of the rest of the box)
   is shown with the colour set by the last call to SetBackgroundColour(). 

So, if during wxDialog::Create() we call
   wxStaticBox::SetForegroundColour(*wxRED)
   wxStaticBox::SetBackgroundColour(*wxYELLOW)
then the whole static box background, including its label, is yellow, and the
label is red.

Say that later on we do
   wxStaticBox::SetForegroundColour(*wxBLUE)
   wxStaticBox::SetBackgroundColour(*wxGREEN)
and then we call wxStaticBox::Enable(false) for the first time. Then we see:
1) the label foreground (the text) is now black.
2) the static box background, excluding the label background, is still yellow.
3) the label background is green.

Subsequent calls to set the fore and background colours and to enable / disable
the static box behave similarly.
*/

class TestStaticBoxDlg : public wxDialog
{
      enum
      {
         DLGID_CHECKBOX_ENABLE_STATICBOX = wxID_HIGHEST + 1
      };

      DECLARE_EVENT_TABLE()

   public:
      bool m_staticBoxEnabled;
      wxCheckBox* m_pCheckBox;
      wxStaticBox* m_pStaticBox;
      wxButton* m_pButton;

      TestStaticBoxDlg(wxWindow *pParentWnd);
      bool Create();
      void OnCheckboxEnableStaticBox(wxCommandEvent&);
};    

BEGIN_EVENT_TABLE(TestStaticBoxDlg, wxDialog)
   EVT_CHECKBOX(DLGID_CHECKBOX_ENABLE_STATICBOX, TestStaticBoxDlg::OnCheckboxEnableStaticBox)
END_EVENT_TABLE()

TestStaticBoxDlg::TestStaticBoxDlg(wxWindow *pParentWnd)
:  wxDialog(pParentWnd, wxID_ANY, "Disable wxStaticBox",
            wxDefaultPosition, wxSize(200, 150),
            wxDEFAULT_DIALOG_STYLE),
   m_staticBoxEnabled(true)
{
}

bool TestStaticBoxDlg::Create()
{
   m_pCheckBox = new wxCheckBox(this, DLGID_CHECKBOX_ENABLE_STATICBOX, "Enable the Static Box", wxPoint(8, 8));
   m_pCheckBox->SetValue(m_staticBoxEnabled);
   m_pStaticBox = new wxStaticBox(this, wxID_ANY, "This is the Static Box", wxPoint(8, 30),  wxSize(150, 75));
   m_pButton = new wxButton(m_pStaticBox, wxID_ANY, wxT("Hello!"), wxPoint(20, 25));
   // the calls to set the fore and background colours succeed here 
   m_pStaticBox->SetForegroundColour(m_staticBoxEnabled ? *wxRED : *wxBLUE);   // sets the label text colour
   m_pStaticBox->SetBackgroundColour(*wxYELLOW);   // sets the whole box background colour, including the label
   return true;
}

void TestStaticBoxDlg::OnCheckboxEnableStaticBox(wxCommandEvent& event)
{
   m_staticBoxEnabled = event.IsChecked();
   m_pStaticBox->SetForegroundColour(m_staticBoxEnabled ? *wxRED : *wxBLUE);   // will have no effect
   m_pStaticBox->SetBackgroundColour(m_staticBoxEnabled ? *wxGREEN : *wxCYAN); // sets only the label background
   m_pStaticBox->Enable(m_staticBoxEnabled); // enables / disables the static box's children
}

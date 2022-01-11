#include <wx/wx.h>

class Openfile : public wxFrame
{
public:
  Openfile(const wxString& title);

  void OnOpen(wxCommandEvent& event);

  wxTextCtrl *tc;

};

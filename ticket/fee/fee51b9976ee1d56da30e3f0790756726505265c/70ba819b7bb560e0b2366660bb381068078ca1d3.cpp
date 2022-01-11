#include "App.h"

#include <wx/aui/aui.h>
#include <wx/textctrl.h>

IMPLEMENT_APP(CM::App);

namespace CM
{

bool App::OnInit()
{
   if ( !wxApp::OnInit() )
      return false;

   // Create the main frame
   wxAuiMDIParentFrame *frame = new wxAuiMDIParentFrame(NULL, wxID_ANY, wxT("MainFrame"));
   SetTopWindow(frame);
   frame->Show();

   // Create the child frame
   wxAuiMDIChildFrame *childFrame = new wxAuiMDIChildFrame(frame, wxID_ANY, wxT("ChildFrame"));
   wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

   wxTextCtrl* textCtrl = new wxTextCtrl(childFrame, wxID_ANY, wxEmptyString,
                                         wxDefaultPosition, wxDefaultSize,
                                         wxTE_MULTILINE);
   sizer->Add(textCtrl, 1, wxEXPAND);

   childFrame->SetSizerAndFit(sizer);

   return true;
}

} // namespace

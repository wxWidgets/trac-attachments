#include "wx/wxprec.h"
#include "wx/wx.h"

#include <wx/richtext/richtextctrl.h>

class App : public wxApp
{

      bool OnInit()
      {

         while (true)
         {
            wxDialog dlg(NULL, -1, "Rich Text Bug", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);

            wxBoxSizer* bSizer1 = new wxBoxSizer( wxVERTICAL );

            wxTextCtrl* m_textCtrl1 = new wxTextCtrl( &dlg, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
            bSizer1->Add( m_textCtrl1, 0, wxALL, 5 );


            wxRichTextCtrl* ctrl = new wxRichTextCtrl(&dlg);
            bSizer1->Add( ctrl, 1, wxALL|wxEXPAND, 5 );

            dlg.SetSizer( bSizer1 );
            dlg.Layout();

            dlg.ShowModal();
         }
      }
};

IMPLEMENT_APP(App)

#include "wx/wxprec.h"
#include "wx/wx.h"

#include <wx/richtext/richtextctrl.h>

class MyFrame1: public wxFrame
{
public:
   MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title)
            : wxFrame( parent, id, title)
   {
      this->SetSizeHints( wxDefaultSize, wxDefaultSize );

      wxBoxSizer* bSizer1;
      bSizer1 = new wxBoxSizer( wxVERTICAL );

      wxRichTextCtrl* m_richText1 = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
      bSizer1->Add( m_richText1, 1, wxEXPAND | wxALL, 5 );

      wxRichTextCtrl* m_richText2 = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
      bSizer1->Add( m_richText2, 1, wxEXPAND | wxALL, 5 );


      this->SetSizer( bSizer1 );
      this->Layout();

      this->Centre( wxBOTH );
   }
};

class MyApp : public wxApp
{
   public:

      bool OnInit()
      {
         wxFrame* frame = new MyFrame1(NULL, -1, "test");
         frame->Show(true);
         return true;
      }
};

IMPLEMENT_APP(MyApp)

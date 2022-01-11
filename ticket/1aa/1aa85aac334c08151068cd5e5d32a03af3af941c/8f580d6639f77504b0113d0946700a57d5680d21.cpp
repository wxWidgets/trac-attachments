#include "wx/wxprec.h"
#include "wx/wx.h"

#include <wx/webview.h>

class MyFrame1: public wxFrame
{
   public:

      MyFrame1() : wxFrame( NULL, wxID_ANY, "Test wxWebView", wxDefaultPosition, wxSize( 500,300 ), wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL )
      {
         this->SetSizeHints( wxDefaultSize, wxDefaultSize );

         wxBoxSizer* bSizer1;
         bSizer1 = new wxBoxSizer( wxVERTICAL );

         wxPanel* m_panel1;
         m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
         wxBoxSizer* bSizer2;
         bSizer2 = new wxBoxSizer( wxVERTICAL );

         wxWebView* m_customControl1 =  wxWebView::New(m_panel1, wxID_ANY, "file:///Users/Brice/Downloads/ckeditor/samples/index.html");
         bSizer2->Add( m_customControl1, 1, wxALL|wxEXPAND, 5 );

         m_panel1->SetSizer( bSizer2 );
         m_panel1->Layout();
         bSizer2->Fit( m_panel1 );
         bSizer1->Add( m_panel1, 1, wxEXPAND | wxALL, 5 );

         this->SetSizer( bSizer1 );
         this->Layout();

         this->Centre( wxBOTH );

         this->Show(true);
      }
};

class MyApp : public wxApp
{
   public:

      bool OnInit()
      {
         new MyFrame1;
         return true;
      }
};

IMPLEMENT_APP(MyApp)
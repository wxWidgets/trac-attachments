#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "rpcrt4.lib")
#pragma warning(disable:4996)
#ifdef _DEBUG
#pragma comment(lib,"wxbase30ud")
#pragma comment(lib,"wxjpegd")
#pragma comment(lib,"wxpngd")
#pragma comment(lib,"wxtiffd")
#pragma comment(lib,"wxbase30ud_net")
#pragma comment(lib,"wxbase30ud_xml")
#pragma comment(lib,"wxmsw30ud_adv")
#pragma comment(lib,"wxmsw30ud_core")
#pragma comment(lib,"wxmsw30ud_html")
#pragma comment(lib,"wxzlibd")
#pragma comment(lib,"wxmsw30ud_aui")
#else
#pragma comment(lib,"wxbase30u")
#pragma comment(lib,"wxjpeg")
#pragma comment(lib,"wxpng")
#pragma comment(lib,"wxtiff")
#pragma comment(lib,"wxbase30u_net")
#pragma comment(lib,"wxbase30u_xml")
#pragma comment(lib,"wxmsw30u_adv")
#pragma comment(lib,"wxmsw30u_core")
#pragma comment(lib,"wxmsw30u_html")
#pragma comment(lib,"wxzlib")
#pragma comment(lib,"wxmsw30u_aui")
#endif



#include "wx/wx.h"
   

class MyFrame: public wxFrame
{
private:
   wxTextCtrl *text_status;
   int click_count;
   
public:
   MyFrame():
      wxFrame(
         0,
         wxID_ANY,
         "SetDefault",
         wxDefaultPosition,
         wxDefaultSize,
         wxDEFAULT_FRAME_STYLE | wxCLIP_CHILDREN),
      click_count(0)
   {
      wxPanel *panel(new wxPanel(this));
      wxSizer *sizer(new wxBoxSizer(wxVERTICAL));
      wxButton *button;

      text_status = new wxTextCtrl(panel, wxID_ANY);
      sizer->Add(text_status, 0, wxALL, 10);
      button = new wxButton(panel, wxID_HIGHEST + 1, "Increment");
      sizer->Add(button, 0, wxALL, 10);
      button->SetDefault();
      panel->SetSizerAndFit(sizer);
   }

   void on_increment(wxCommandEvent &event)
   {
      wxString content;
      ++click_count;
      content.Printf("%d", click_count);
      text_status->SetValue(content);
   }

   DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_BUTTON(wxID_OK, MyFrame::on_increment)
END_EVENT_TABLE()


class MyApp: public wxApp
{
   virtual bool OnInit()
   {
      MyFrame *frame(new MyFrame);
      frame->Show(true);
      SetExitOnFrameDelete(true);
      return true;
   }
};


    IMPLEMENT_APP(MyApp)

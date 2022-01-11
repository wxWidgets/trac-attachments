#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/sizer.h"
#include "wx/statline.h"
#include "wx/minifram.h"

class fooFrame: public wxFrame {
    public:
        fooFrame(wxFrame *parent, const wxPoint &position, const wxString &title, const long style): 
            wxFrame(parent, -1, title, position, wxDefaultSize, style)
        {                    
            wxFlexGridSizer *sizer = new wxFlexGridSizer(2, 0);
            sizer -> Add(new wxStaticText(this, -1, _T("wxStaticText 1")), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
            sizer -> Add(new wxTextCtrl(this, -1, _T("wxTextCtrl 1")), 0, wxALL, 5);
            sizer -> Add(new wxStaticText(this, -1, _T("wxStaticText 2")), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
            sizer -> Add(new wxTextCtrl(this, -1, _T("wxTextCtrl 2")), 0, wxALL, 5);
            sizer -> Add(new wxStaticText(this, -1, _T("wxStaticText 3")), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
            sizer -> Add(new wxTextCtrl(this, -1, _T("wxTextCtrl 3")), 0, wxALL, 5);
            SetAutoLayout(true);
            SetSizer(sizer);
            sizer -> SetSizeHints(this);
        }
};
class fooMiniFrame: public wxMiniFrame {
    public:
        fooMiniFrame(wxFrame *parent, const wxPoint &position, const wxString &title, const long style):
            wxMiniFrame(parent, -1, title, position, wxDefaultSize, style)
        {
            wxFlexGridSizer *sizer = new wxFlexGridSizer(2, 0);
            sizer -> Add(new wxStaticText(this, -1, _T("wxStaticText 1")), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
            sizer -> Add(new wxTextCtrl(this, -1, _T("wxTextCtrl 1")), 0, wxALL, 5);
            sizer -> Add(new wxStaticText(this, -1, _T("wxStaticText 2")), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
            sizer -> Add(new wxTextCtrl(this, -1, _T("wxTextCtrl 2")), 0, wxALL, 5);
            sizer -> Add(new wxStaticText(this, -1, _T("wxStaticText 3")), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
            sizer -> Add(new wxTextCtrl(this, -1, _T("wxTextCtrl 3")), 0, wxALL, 5);
            SetAutoLayout(true);
            SetSizer(sizer);
            sizer -> SetSizeHints(this);
        }
};

class fooApp: public wxApp {
    public:
        fooApp () {}
    
        bool OnInit () {
            frame1 = new fooFrame((wxFrame*)NULL, wxPoint(50, 50),
                     _T("wxFrame without wxFRAME_TOOL_WINDOW"), wxDEFAULT_FRAME_STYLE);
            frame2 = new fooFrame(frame1, wxPoint(200, 200),
                     _T("wxFrame with wxFRAME_TOOL_WINDOW"), wxDEFAULT_FRAME_STYLE | wxFRAME_TOOL_WINDOW);
            frame3 = new fooMiniFrame(frame1, wxPoint(350, 350),
                     _T("wxMiniFrame"), wxDEFAULT_FRAME_STYLE);
            frame1 -> Show(true);
            frame2 -> Show(true);
            frame3 -> Show(true);            
            SetTopWindow(frame1);
            return true;
        }
        
    private:
        fooFrame *frame1;
        fooFrame *frame2;
        fooMiniFrame *frame3;
};

IMPLEMENT_APP(fooApp)

 	  	 

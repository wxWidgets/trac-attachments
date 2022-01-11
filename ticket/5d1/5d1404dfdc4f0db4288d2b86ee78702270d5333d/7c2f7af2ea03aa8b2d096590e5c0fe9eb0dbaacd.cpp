
#include "wx/wx.h"
#ifdef __BORLANDC__
#pragma hdrstop
#endif
#include "wx/xrc/xmlres.h"
#include "wx/image.h"
#include "wx/frame.h"
#define ID_FRAME 10000
#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif

class t: public wxFrame
{    
    DECLARE_CLASS( t )
public:
    t( );
    t( wxWindow* parent, wxWindowID=wxID_ANY, const wxString& caption = _(""), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX );

    bool Create( wxWindow* parent, wxWindowID=wxID_ANY, const wxString& caption = _(""), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX);
    void CreateControls();
};
IMPLEMENT_CLASS( t, wxFrame )
t::t( ){}
t::t( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style ){    
	SetParent(parent);
	wxXmlResource::Get()->LoadFrame(this, GetParent(), wxT("ID_FRAME"));
	wxXmlResource::Get()->LoadPanel(this, wxT("ID_PANEL"));
}

class TestXRCApp: public wxApp
{    
    DECLARE_CLASS( TestXRCApp )
public:
    TestXRCApp();
    virtual bool OnInit();

    virtual int OnExit();
};
DECLARE_APP(TestXRCApp)
IMPLEMENT_APP( TestXRCApp )
IMPLEMENT_CLASS( TestXRCApp, wxApp )
TestXRCApp::TestXRCApp(){}
bool TestXRCApp::OnInit()
{    
    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->Load(_T("textXRC.xrc"));

#if wxUSE_XPM
    wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
    wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
    wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
    wxImage::AddHandler(new wxGIFHandler);
#endif
    t* mainWindow = new t( NULL, ID_FRAME );
    mainWindow->Show(true);
    return true;
}
int TestXRCApp::OnExit(){ return wxApp::OnExit();}

 	  	 

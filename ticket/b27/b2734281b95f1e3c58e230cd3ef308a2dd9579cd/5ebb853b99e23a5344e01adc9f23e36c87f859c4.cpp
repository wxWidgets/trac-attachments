// tapping button in wxRadioBox hangs if wxRadioBox is a child of a non-TLW (Windows Mobile 5.0 only)
// steps to reproduce:
// 1) run this sample under Windows Mobile 5.0 (2003SE is fine)
// 2) tap on any unselected button
// 3) the following messages are processed:
//    01:22:53: wxRadioBtnWndProc WM_SETCURSOR(hWnd=7c078150, wParam=7c078150, lParam= 2010001)
//    01:22:54: wxRadioBtnWndProc WM_GETDLGCODE(hWnd=7c078150, wParam=       0, lParam=       0)
//    01:22:54: wxRadioBtnWndProc WM_GETDLGCODE(hWnd=7c078150, wParam=       1, lParam=1c2df990)
//    01:22:54: wxRadioBtnWndProc WM_GETDLGCODE(hWnd=7c078150, wParam=       0, lParam=       0)
//    01:22:54: wxRadioBtnWndProc WM_LBUTTONDOWN(hWnd=7c078150, wParam=       1, lParam=   b0005)
//    01:22:54: Processing WM_KILLFOCUS(hWnd=7c077e90, wParam=7c078150, lParam=       0)
//    01:22:54: Forwarding WM_KILLFOCUS to DefWindowProc.
//    01:22:54: Processing WM_IME_SETCONTEXT(hWnd=7c077e90, wParam=       0, lParam=c000000f)
//    01:22:54: Forwarding WM_IME_SETCONTEXT to DefWindowProc.
//    01:22:54: wxRadioBtnWndProc WM_IME_SETCONTEXT(hWnd=7c078150, wParam=       1, lParam=c000000f)
//    01:22:54: wxRadioBtnWndProc WM_SETFOCUS(hWnd=7c078150, wParam=7c077e90, lParam=       0)
//    01:22:54: Processing WM_GETTEXTLENGTH(hWnd=7c077e90, wParam=       0, lParam=       0)
//    01:22:54: Forwarding WM_GETTEXTLENGTH to DefWindowProc.
//    01:22:54: Processing WM_GETTEXT(hWnd=7c077e90, wParam=       6, lParam=1c2ee5ac)
//    01:22:54: Forwarding WM_GETTEXT to DefWindowProc.
//    01:22:54: Processing WM_CTLCOLORSTATIC(hWnd=7c077e90, wParam=  64024f, lParam=7c078150)
//    01:22:54: Forwarding WM_CTLCOLORSTATIC to DefWindowProc.
//    01:22:54: wxRadioBtnWndProc BM_SETSTATE(hWnd=7c078150, wParam=       1, lParam=       0)
//    01:22:54: Processing WM_CTLCOLORSTATIC(hWnd=7c077e90, wParam=  6e0251, lParam=7c078150)
//    01:22:54: Forwarding WM_CTLCOLORSTATIC to DefWindowProc.
//    01:22:54: wxRadioBtnWndProc WM_GETDLGCODE(hWnd=7c078150, wParam=       0, lParam=       0)
//    01:22:54: wxRadioBtnWndProc WM_GETDLGCODE(hWnd=7c078150, wParam=       1, lParam=1c2df990)
//    01:22:55: wxRadioBtnWndProc WM_MOUSEMOVE(hWnd=7c078150, wParam=       1, lParam=   b0005)
//    01:22:55: wxRadioBtnWndProc BM_SETSTATE(hWnd=7c078150, wParam=       1, lParam=       0)
//    01:22:55: Processing WM_CTLCOLORSTATIC(hWnd=7c077e90, wParam=  7400fe, lParam=7c078150)
//    01:22:55: Forwarding WM_CTLCOLORSTATIC to DefWindowProc.
//    01:22:55: wxRadioBtnWndProc WM_GETDLGCODE(hWnd=7c078150, wParam=       0, lParam=       0)
//    01:22:55: wxRadioBtnWndProc WM_GETDLGCODE(hWnd=7c078150, wParam=       0, lParam=1c2df990)
//    01:22:55: wxRadioBtnWndProc WM_LBUTTONUP(hWnd=7c078150, wParam=       0, lParam=   b0005)
//    01:22:55: wxRadioBtnWndProc BM_SETSTATE(hWnd=7c078150, wParam=       0, lParam=       0)
//    01:22:55: Processing WM_CTLCOLORSTATIC(hWnd=7c077e90, wParam=  740259, lParam=7c078150)
//    01:22:55: Forwarding WM_CTLCOLORSTATIC to DefWindowProc.
//    01:22:55: wxRadioBtnWndProc WM_GETDLGCODE(hWnd=7c078150, wParam=       0, lParam=       0)
//    01:22:55: wxRadioBtnWndProc BM_SETCHECK(hWnd=7c078150, wParam=       1, lParam=       0)
//    01:22:55: wxRadioBtnWndProc WM_STYLECHANGED(hWnd=7c078150, wParam=fffffff0, lParam=1c2df1d4)
//    01:22:55: Processing WM_CTLCOLORSTATIC(hWnd=7c077e90, wParam=  8c0276, lParam=7c078150)
//    01:22:55: Forwarding WM_CTLCOLORSTATIC to DefWindowProc.
//    01:22:55: wxRadioBtnWndProc WM_GETDLGCODE(hWnd=7c078060, wParam=       0, lParam=       0)
//    01:22:55: wxRadioBtnWndProc BM_SETCHECK(hWnd=7c078060, wParam=       0, lParam=       0)
//    01:22:55: wxRadioBtnWndProc WM_STYLECHANGED(hWnd=7c078060, wParam=fffffff0, lParam=1c2df1d4)
//    01:22:55: Processing WM_CTLCOLORSTATIC(hWnd=7c077e90, wParam=  6a0102, lParam=7c078060)
//    01:22:55: Forwarding WM_CTLCOLORSTATIC to DefWindowProc.
// 4) symptom: button will become checked
// 5) wxRadioBtnWndProc will receive these three messages over and over again:
//    01:22:55: wxRadioBtnWndProc WM_GETDLGCODE(hWnd=7c078060, wParam=       0, lParam=       0)
//    01:22:55: wxRadioBtnWndProc BM_SETCHECK(hWnd=7c078060, wParam=       0, lParam=       0)
//    01:22:55: wxRadioBtnWndProc WM_STYLECHANGED(hWnd=7c078060, wParam=fffffff0, lParam=1c2df1d4)
// 6) symptom: app will lockup

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/image.h"

class RadioboxceApp: public wxApp
{    
    DECLARE_CLASS( RadioboxceApp )
    DECLARE_EVENT_TABLE()

public:
    RadioboxceApp();
    void Init();
    virtual bool OnInit();
    virtual int OnExit();
};

DECLARE_APP(RadioboxceApp)

#define ID_RADIOBOXCEDLG 10005
#define ID_WINDOW2 10006
#define ID_RADIOBOX2 10008
#define SYMBOL_RADIOBOXCEDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_RADIOBOXCEDLG_TITLE _("RadioboxceDlg")
#define SYMBOL_RADIOBOXCEDLG_IDNAME ID_RADIOBOXCEDLG
#define SYMBOL_RADIOBOXCEDLG_SIZE wxSize(400, 300)
#define SYMBOL_RADIOBOXCEDLG_POSITION wxDefaultPosition

class RadioboxceDlg: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( RadioboxceDlg )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    RadioboxceDlg( );
    RadioboxceDlg( wxWindow* parent, wxWindowID id = SYMBOL_RADIOBOXCEDLG_IDNAME, const wxString& caption = SYMBOL_RADIOBOXCEDLG_TITLE, const wxPoint& pos = SYMBOL_RADIOBOXCEDLG_POSITION, const wxSize& size = SYMBOL_RADIOBOXCEDLG_SIZE, long style = SYMBOL_RADIOBOXCEDLG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_RADIOBOXCEDLG_IDNAME, const wxString& caption = SYMBOL_RADIOBOXCEDLG_TITLE, const wxPoint& pos = SYMBOL_RADIOBOXCEDLG_POSITION, const wxSize& size = SYMBOL_RADIOBOXCEDLG_SIZE, long style = SYMBOL_RADIOBOXCEDLG_STYLE );

    /// Creates the controls and sizers
    void CreateControls();
};

IMPLEMENT_APP( RadioboxceApp )
IMPLEMENT_CLASS( RadioboxceApp, wxApp )
BEGIN_EVENT_TABLE( RadioboxceApp, wxApp )
END_EVENT_TABLE()

RadioboxceApp::RadioboxceApp()
{
}

bool RadioboxceApp::OnInit()
{   
    RadioboxceDlg rbd(0);

    rbd.ShowModal();

    return true;
}

int RadioboxceApp::OnExit()
{    
    return wxApp::OnExit();
}


IMPLEMENT_DYNAMIC_CLASS( RadioboxceDlg, wxDialog )
BEGIN_EVENT_TABLE( RadioboxceDlg, wxDialog )
END_EVENT_TABLE()

RadioboxceDlg::RadioboxceDlg( )
{
}

RadioboxceDlg::RadioboxceDlg( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

bool RadioboxceDlg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
    return true;
}

void RadioboxceDlg::CreateControls()
{    
    RadioboxceDlg* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxWindow* itemWindow3 = new wxWindow( itemDialog1, ID_WINDOW2, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxHSCROLL|wxVSCROLL );
    itemBoxSizer2->Add(itemWindow3, 1, wxGROW|wxALL, 5);
    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxVERTICAL);
    itemWindow3->SetSizer(itemBoxSizer4);

    wxString itemRadioBox5Strings[] = {
        _("&One"),
        _("&Two"),
        _("T&hree"),
        _("&Four"),
        _("F&ive")
    };
    wxRadioBox* itemRadioBox5 = new wxRadioBox( itemWindow3, ID_RADIOBOX2, _("Radiobox"), wxDefaultPosition, wxDefaultSize, 5, itemRadioBox5Strings, 1, wxRA_SPECIFY_ROWS );
    itemRadioBox5->SetSelection(0);
    itemBoxSizer4->Add(itemRadioBox5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    itemWindow3->FitInside();

    wxLog::SetTraceMask( wxTraceMessages );
}


 	  	 

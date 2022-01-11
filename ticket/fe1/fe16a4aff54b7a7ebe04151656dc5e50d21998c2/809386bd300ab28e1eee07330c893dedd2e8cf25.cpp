/////////////////////////////////////////////////////////////////////////////
// Name:        formtstr.cpp
// Purpose:     Format and validate number sample
// Author:      Manuel Martin
// Modified by:
// Created:     mar 2003
// RCS-ID:      
// Copyright:   
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
#ifdef __GNUG__
    #pragma implementation "formtstr.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------
// the application icon
#if defined(__WXGTK__) || defined(__WXMOTIF__)
    #include "mondrian.xpm"
#endif

//this file header
#include "formtstr.h"

//other application headers
#include "wx/statline.h"
#include "forstrnu.h"
#include "valnum.h"


// ----------------------------------------------------------------------------
// event tables and other macros for wxWindows
// ----------------------------------------------------------------------------

// the event tables connect the wxWindows events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(FSN_QUIT,  MyFrame::OnQuit)
    EVT_MENU(FSN_ABOUT, MyFrame::OnAbout)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(myPanel, wxPanel)
    EVT_BUTTON(FSVN_BUTF, myPanel::OnButtonFPressed)
    EVT_BUTTON(FSVN_BUTU, myPanel::OnButtonUPressed)
    EVT_BUTTON(FSVN_VRESET, myPanel::OnButtonVPressed)
    EVT_BUTTON(FSVN_VTOWIN, myPanel::OnButtonTTWPressed)
    EVT_BUTTON(FSVN_VFRWIN, myPanel::OnButtonTFWPressed)
END_EVENT_TABLE()

// Create a new application object: this macro will allow wxWindows to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also declares the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MyApp)

// ============================================================================
// implementation
// ============================================================================

//global variable for validator
wxString stval("");

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // create the main application window
    MyFrame *frame = new MyFrame("Format And Validate String As Number Sample",
                                 wxPoint(30, 30), wxSize(750, 440));

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(TRUE);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned FALSE here, the
    // application would exit immediately.
    return TRUE;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
#ifdef __WXMAC__
    // we need this in order to allow the about menu relocation, since ABOUT is
    // not the default id of the about menu
    wxApp::s_macAboutMenuItemId = FSN_ABOUT;
#endif

    // set the frame icon
    wxIcon frame_icon("mondrian.ico",wxBITMAP_TYPE_ICO,-1,-1);
    SetIcon(frame_icon);

    // create a menu bar
    wxMenuBar *menuBar = new wxMenuBar();

    //create the menus in the menu bar
    wxMenu *menuFile = new wxMenu("", wxMENU_TEAROFF);
    menuFile->Append(FSN_QUIT, _("E&xit\tAlt-X"), _("Quit this program"));


    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(FSN_ABOUT, _("&About...\tCtrl-A"), _("Show about dialog"));

    // now append the freshly created menu to the menu bar...
    menuBar->Append(menuFile, _("&File"));
    menuBar->Append(helpMenu, _("&Help"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);

#if wxUSE_STATUSBAR
    // create a status bar (by default with 1 pane only)
    CreateStatusBar(1);
#endif // wxUSE_STATUSBAR

    //Add a panel to place things
    int width, height;
    GetClientSize(&width, &height);
    myPanel* tpanel = new myPanel(this,
                                 wxPoint(0, 0), wxSize(width, height));

}

/////////////////////////////////////////////////////////////////////////////
MyFrame::~MyFrame()
{
}

/////////////////////////////////////////////////////////////////////////////
void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // TRUE is to force the frame to close
    Close(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( _T("Format And Validate String As Number Sample\n")
                _T("version 1.0\n")
                _T("Manuel Martin"));

    wxMessageBox(msg, _("About Format and Validate"), wxOK | wxICON_INFORMATION, this);
}

/////////////////////////////////////////////////////////////////////////////
myPanel::myPanel(wxWindow* parent, const wxPoint& pos, const wxSize& size)
             : wxPanel(parent, -1, pos, size, wxTAB_TRAVERSAL)
{
    SetBackgroundColour(wxColour(122,166,208));

    int xs=10, ys=10, dx=180, dy=20;
    wxStaticText* wordss = new wxStaticText(this, -1,
          _T("with this style"), wxPoint(xs,ys));
    wxStaticText* wordsn = new wxStaticText(this, -1,
          _T("this number"), wxPoint(xs+dx,ys));
    wxStaticText* wordsf = new wxStaticText(this, -1,
          _T("gets formatted into"), wxPoint(xs+2*dx,ys));
    wxStaticText* wordsu = new wxStaticText(this, -1,
          _T("unformatted is"), wxPoint(xs+3*dx,ys));
    wxStaticLine* seline = new wxStaticLine(this, -1,
            wxPoint(xs,ys+0.7*dy), wxSize(xs+4*dx,-1));

    //lets make some samples
    wxString stastyle, stanum;
    wxString strFormatted, strUnFormatted;
    wxFormatStringAsNumber fsnsample(wxT("[,###].'.'#"));

    stastyle = wxT("[,###].'.'#");
    stanum = wxT("1234567890.4321");
    fsnsample.FormatStr(stanum, strFormatted);
    fsnsample.UnFormatStr(strFormatted, strUnFormatted, wxUF_BESTRICT);
    wxStaticText* smp1s = new wxStaticText(this, -1, stastyle, wxPoint(xs, ys+dy));
    wxStaticText* smp1n = new wxStaticText(this, -1, stanum, wxPoint(xs+dx, ys+dy));
    wxStaticText* smp1f = new wxStaticText(this, -1, strFormatted, wxPoint(xs+2*dx, ys+dy));
    wxStaticText* smp1u = new wxStaticText(this, -1, strUnFormatted, wxPoint(xs+3*dx, ys+dy));

    stastyle = wxT("[mM000].'d'#");
    stanum = wxT("12345678.4321");
    fsnsample.SetStyle(stastyle);
    fsnsample.FormatStr(stanum, strFormatted);
    fsnsample.UnFormatStr(strFormatted, strUnFormatted, wxUF_BESTRICT);
    wxStaticText* smp2s = new wxStaticText(this, -1, stastyle, wxPoint(xs, ys+2*dy));
    wxStaticText* smp2n = new wxStaticText(this, -1, stanum, wxPoint(xs+dx, ys+2*dy));
    wxStaticText* smp2f = new wxStaticText(this, -1, strFormatted, wxPoint(xs+2*dx, ys+2*dy));
    wxStaticText* smp2u = new wxStaticText(this, -1, strUnFormatted, wxPoint(xs+3*dx, ys+2*dy));

    stastyle = wxT("-#0.','#E-###");
    stanum = wxT("-1234.56e98");
    fsnsample.SetStyle(stastyle);
    fsnsample.FormatStr(stanum, strFormatted);
    fsnsample.UnFormatStr(strFormatted, strUnFormatted, wxUF_BESTRICT);
    wxStaticText* smp3s = new wxStaticText(this, -1, stastyle, wxPoint(xs, ys+3*dy));
    wxStaticText* smp3n = new wxStaticText(this, -1, stanum, wxPoint(xs+dx, ys+3*dy));
    wxStaticText* smp3f = new wxStaticText(this, -1, strFormatted, wxPoint(xs+2*dx, ys+3*dy));
    wxStaticText* smp3u = new wxStaticText(this, -1, strUnFormatted, wxPoint(xs+3*dx, ys+3*dy));

    stastyle = wxT("num is= [#].' and '00+");
    double d = -1234.5698;
    stanum.Printf("%f",d);
    fsnsample.SetStyle(stastyle);
    fsnsample.FormatStr(stanum, strFormatted);
    fsnsample.UnFormatStr(strFormatted, strUnFormatted, wxUF_BESTRICT);
    wxStaticText* smp4s = new wxStaticText(this, -1, stastyle, wxPoint(xs, ys+4*dy));
    wxStaticText* smp4n = new wxStaticText(this, -1, stanum, wxPoint(xs+dx, ys+4*dy));
    wxStaticText* smp4f = new wxStaticText(this, -1, strFormatted, wxPoint(xs+2*dx, ys+4*dy));
    wxStaticText* smp4u = new wxStaticText(this, -1, strUnFormatted, wxPoint(xs+3*dx, ys+4*dy));

    stastyle = wxT("@#[b 0 ]@-000e+bxbxbx0+@#");
    stanum = wxT("12345678E+98");
    fsnsample.SetStyle(stastyle);
    fsnsample.FormatStr(stanum, strFormatted);
    fsnsample.UnFormatStr(strFormatted, strUnFormatted, wxUF_BESTRICT);
    wxStaticText* smp5s = new wxStaticText(this, -1, stastyle, wxPoint(xs, ys+5*dy));
    wxStaticText* smp5n = new wxStaticText(this, -1, stanum, wxPoint(xs+dx, ys+5*dy));
    wxStaticText* smp5f = new wxStaticText(this, -1, strFormatted, wxPoint(xs+2*dx, ys+5*dy));
    wxStaticText* smp5u = new wxStaticText(this, -1, strUnFormatted, wxPoint(xs+3*dx, ys+5*dy));

    stastyle = wxT("+[#].'.'#;(000.','00)");
    stanum = wxT("12.3");
    fsnsample.SetStyle(stastyle);
    fsnsample.FormatStr(stanum, strFormatted);
    fsnsample.UnFormatStr(strFormatted, strUnFormatted, wxUF_BESTRICT);
    wxStaticText* smp6s = new wxStaticText(this, -1, stastyle, wxPoint(xs, ys+6*dy));
    wxStaticText* smp6n = new wxStaticText(this, -1, stanum, wxPoint(xs+dx, ys+6*dy));
    wxStaticText* smp6f = new wxStaticText(this, -1, strFormatted, wxPoint(xs+2*dx, ys+6*dy));
    wxStaticText* smp6u = new wxStaticText(this, -1, strUnFormatted, wxPoint(xs+3*dx, ys+6*dy));

    stanum = wxT("-12.3");
    fsnsample.SetStyle(stastyle);
    fsnsample.FormatStr(stanum, strFormatted);
    fsnsample.UnFormatStr(strFormatted, strUnFormatted, wxUF_BESTRICT);
    wxStaticText* smp7s = new wxStaticText(this, -1, stastyle, wxPoint(xs, ys+7*dy));
    wxStaticText* smp7n = new wxStaticText(this, -1, stanum, wxPoint(xs+dx, ys+7*dy));
    wxStaticText* smp7f = new wxStaticText(this, -1, strFormatted, wxPoint(xs+2*dx, ys+7*dy));
    wxStaticText* smp7u = new wxStaticText(this, -1, strUnFormatted, wxPoint(xs+3*dx, ys+7*dy));

    //try your own style, number, result and unformatted
    wxButton* butTestF = new wxButton(this, FSVN_BUTF,
             _("Press here to test your own format"), wxPoint(xs, ys+9*dy));
    wxButton* butTestU = new wxButton(this, FSVN_BUTU,
             _("Press here to test your own unformat"), wxPoint(xs+dx, ys+9*dy));
    beStrict = new wxCheckBox(this, FSVN_BSTRC, _("Strict Mode"),
             wxPoint(xs+2.5*dx, ys+9*dy), wxSize(-1,-1), 0);
    leftrim0 = new wxCheckBox(this, FSVN_LTRM0, _("Trim zeros at left"),
             wxPoint(xs+3.1*dx, ys+9*dy), wxSize(-1,-1), 0);
    rigtrim0 = new wxCheckBox(this, FSVN_RTRM0, _("Trim zeros at right"),
             wxPoint(xs+3.1*dx, ys+10*dy), wxSize(-1,-1), 0);

    yourstyle = new wxTextCtrl(this, -1,"",wxPoint(xs, ys+11*dy), wxSize(dx-5,dy+5));
    yournumb  = new wxTextCtrl(this, -1,"",wxPoint(xs+dx, ys+11*dy), wxSize(dx-5,dy+5));
    yourresul = new wxTextCtrl(this, -1,"",wxPoint(xs+2*dx, ys+11*dy), wxSize(dx-5,dy+5));
    yourunfor = new wxTextCtrl(this, -1,"",wxPoint(xs+3*dx, ys+11*dy), wxSize(dx-5,dy+5));

    //Validate test
    wxStaticText* valst = new wxStaticText(this, -1, wxT("VALIDATE"), wxPoint(xs, ys+13*dy));
    wxStaticText* valdt = new wxStaticText(this, -1, wxT("String in var"), wxPoint(xs+dx, ys+13*dy));
    wxStaticText* valvl = new wxStaticText(this, -1, wxT("Validator window"), wxPoint(xs+dx, ys+15.3*dy));
    wxButton* butValRst = new wxButton(this, FSVN_VRESET,
             _("Use style and checked flags "), wxPoint(xs, ys+14*dy));
    wxButton* butToWin = new wxButton(this, FSVN_VTOWIN,
             _("Transfer to window"), wxPoint(xs+2.2*dx, ys+16*dy));
    wxButton* butFrWin = new wxButton(this, FSVN_VFRWIN,
             _("Transfer from window"), wxPoint(xs+3.2*dx, ys+16*dy));

    vOnChar  = new wxCheckBox(this, FSVN_VONCH, _("Validate On Char"),
             wxPoint(xs+2.2*dx, ys+13*dy), wxSize(-1,-1), 0);
    vOnChar->SetValue(TRUE);
    vOnEnTab = new wxCheckBox(this, FSVN_VONET, _("Validate On Enter/Tab"),
             wxPoint(xs+3.1*dx, ys+13*dy), wxSize(-1,-1), 0);
    vOnEnTab->SetValue(TRUE);
    vOnKillF = new wxCheckBox(this, FSVN_VONKF, _("Validate On Kill Focus"),
             wxPoint(xs+2.2*dx, ys+14*dy), wxSize(-1,-1), 0);
    vOnKillF->SetValue(TRUE);
    vTransUn = new wxCheckBox(this, FSVN_VTRUN, _("Transfer Unformatted"),
             wxPoint(xs+3.1*dx, ys+14*dy), wxSize(-1,-1), 0);
    stastyle = wxT("-[,###].'w'#e-##");
    yourvalsty = new wxTextCtrl(this, -1, stastyle,
                      wxPoint(xs, ys+16*dy), wxSize(dx-5,dy+5));
    yourvaldat = new wxTextCtrl(this, -1, stval,
                      wxPoint(xs+dx, ys+13.9*dy), wxSize(dx-5,dy+5));
    yourtest   = new wxTextCtrl(this, -1, "",
                      wxPoint(xs+dx, ys+16*dy), wxSize(dx-5,dy+5),0,
                      wxNumberValidator(stastyle,
                          wxVAL_ON_KILL_FOCUS | wxVAL_ON_EDIT, &stval));
}

/////////////////////////////////////////////////////////////////////////////
myPanel::~myPanel()
{
}

/////////////////////////////////////////////////////////////////////////////
void myPanel::OnButtonFPressed(wxCommandEvent& WXUNUSED(event))
{
    int res;
    wxString testFormatted;
    wxFormatStringAsNumber usrtest;

    res = usrtest.SetStyle(yourstyle->GetValue());
    if (res != -1)
    {   wxMessageBox(usrtest.GetLastError(), _("Error in style"));
        yourstyle->SetInsertionPoint((long)res);
        yourstyle->SetFocus();
        return;
    }
    res = usrtest.FormatStr(yournumb->GetValue(), testFormatted);
    if (res != -1)
    {   wxMessageBox(usrtest.GetLastError(), _("Error in number"));
        yournumb->SetInsertionPoint((long)res);
        yournumb->SetFocus();
        return;
    }
    yourresul->SetValue(testFormatted);

}

/////////////////////////////////////////////////////////////////////////////
void myPanel::OnButtonUPressed(wxCommandEvent& WXUNUSED(event))
{
    int res, bstric=wxUF_NOSTRICT, tz=0;
    wxString testUnFormatted;
    wxFormatStringAsNumber usrtest;

    res = usrtest.SetStyle(yourstyle->GetValue());
    if (res != -1)
    {   wxMessageBox(usrtest.GetLastError(), _("Error in style"));
        yourstyle->SetInsertionPoint((long)res);
        yourstyle->SetFocus();
        return;
    }
    if (beStrict->GetValue())
        bstric = wxUF_BESTRICT;
    res = usrtest.UnFormatStr(yourresul->GetValue(), testUnFormatted, bstric);
    if (res != -1)
    {   wxMessageBox(usrtest.GetLastError(), _("Error in formatted number"));
        yourresul->SetInsertionPoint((long)res);
        yourresul->SetFocus();
        return;
    }
    //trim zeros
    if (leftrim0->GetValue())
        tz = tz | wxTZ_LEFT;
    if (rigtrim0->GetValue())
        tz = tz | wxTZ_RIGHT;
    usrtest.TrimZeros(testUnFormatted, tz);

    yourunfor->SetValue(testUnFormatted);
}

/////////////////////////////////////////////////////////////////////////////
void myPanel::OnButtonVPressed(wxCommandEvent& WXUNUSED(event))
{
    int res, vflags=0;
    wxNumberValidator *nva = (wxNumberValidator*) yourtest->GetValidator() ;
    res = nva->SetStyle(yourvalsty->GetValue());
    if (res != -1)
    {   wxMessageBox(nva->GetLastError(), _("Error in validate style"));
        yourvalsty->SetInsertionPoint((long)res);
        yourvalsty->SetFocus();
        return;
    }
    if (beStrict->GetValue())
        vflags |= wxUF_BESTRICT;
    else
        vflags |= wxUF_NOSTRICT;
    if (leftrim0->GetValue())
        vflags |= wxTZ_LEFT;
    if (rigtrim0->GetValue())
        vflags |= wxTZ_RIGHT;
    if (vOnChar->GetValue())
        vflags |= wxVAL_ON_CHAR;
    if (vOnEnTab->GetValue())
        vflags |= wxVAL_ON_ENTER_TAB;
    if (vOnKillF->GetValue())
        vflags |= wxVAL_ON_KILL_FOCUS;
    if (vTransUn->GetValue())
        vflags |= wxTRANSFER_UNFORMATTED;

    nva->SetBehavior(vflags);
    return;
}


/////////////////////////////////////////////////////////////////////////////
void myPanel::OnButtonTTWPressed(wxCommandEvent& WXUNUSED(event))
{
    wxNumberValidator *nva = (wxNumberValidator*) yourtest->GetValidator() ;
    stval = yourvaldat->GetValue();
    nva->TransferToWindow();
    return;
}

/////////////////////////////////////////////////////////////////////////////
void myPanel::OnButtonTFWPressed(wxCommandEvent& WXUNUSED(event))
{
    wxNumberValidator *nva = (wxNumberValidator*) yourtest->GetValidator() ;
    nva->TransferFromWindow();
    yourvaldat->SetValue(stval);
    return;
}


 	  	 

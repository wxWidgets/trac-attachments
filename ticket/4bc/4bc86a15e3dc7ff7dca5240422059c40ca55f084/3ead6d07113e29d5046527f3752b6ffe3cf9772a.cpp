/////////////////////////////////////////////////////////////////////////////
// Name:        minimal.cpp
// Purpose:     Minimal wxWindows sample
// Author:      Julian Smart
// Modified by: Christian Sturmlechner 2004/02/07 to demonstrate a bugfix (search for ***)
// Created:     04/01/98
// RCS-ID:      $Id: minimal.cpp,v 1.64 2003/12/28 17:34:18 JS Exp $
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

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

// the application icon (under Windows and OS/2 it is in resources)
#if defined(__WXGTK__) || defined(__WXMOTIF__) || defined(__WXMAC__) || defined(__WXMGL__) || defined(__WXX11__)
    #include "mondrian.xpm"
// *** new start
static char *playgreen_xpm[] = {
/* width height ncolors chars_per_pixel */
"16 16 3 1",
/* colors */
"  c #000000",
". c #00FF00",
"X c #008000",
/* pixels */
"                ",
"                ",
"   XXX          ",
"   X.XXX        ",
"   X...XXX      ",
"   X.....XXX    ",
"   X.......XXX  ",
"   X.........X  ",
"   X.......XXX  ",
"   X.....XXX    ",
"   X...XXX      ",
"   X.XXX        ",
"   XXX          ",
"                ",
"                ",
"                "
};

static char *redcenter_xpm[] = {
/* width height ncolors chars_per_pixel */
"16 16 3 1",
/* colors */
"  c #000000",
". c #C0C0C0",
"X c #FF0000",
/* pixels */
"................",
".....      .....",
"....        ....",
"...          ...",
"..    XXXX    ..",
".    XXXXXX    .",
".   XXXXXXXX   .",
".   XXXXXXXX   .",
".   XXXXXXXX   .",
".   XXXXXXXX   .",
".    XXXXXX    .",
"..    XXXX    ..",
"...          ...",
"....        ....",
".....      .....",
"................"
};
// *** new end
#endif

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnCalc(wxCommandEvent& event); // *** new

private:
    // any class wishing to process wxWindows events must use this macro
    DECLARE_EVENT_TABLE()
};




// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    Minimal_Calc = 0, // *** new
    ID_STOPCALC,      // *** new
    ID_CLOSECALC,     // *** new

    // menu items
    Minimal_Quit = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWindows
// ----------------------------------------------------------------------------

// the event tables connect the wxWindows events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Calc,  MyFrame::OnCalc) // *** new
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
END_EVENT_TABLE()

// Create a new application object: this macro will allow wxWindows to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MyApp)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // create the main application window
    MyFrame *frame = new MyFrame(_T("Minimal wxWindows App"));

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
    // set the frame icon
    SetIcon(wxICON(mondrian));

#if wxUSE_MENUS
    // create a menu bar
    wxMenu *menuFile = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, _T("&About...\tF1"), _T("Show about dialog"));

    menuFile->Append(Minimal_Calc, _T("&Calc...\tCtrl+C"), _T("Calculate something important")); // *** new
    menuFile->Append(Minimal_Quit, _T("E&xit\tAlt+X"), _T("Quit this program"));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, _T("&File"));
    menuBar->Append(helpMenu, _T("&Help"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(_T("Welcome to wxWindows!"));
#endif // wxUSE_STATUSBAR

    // *** new start
    wxToolBar* pToolBar = CreateToolBar( wxNO_BORDER | wxTB_HORIZONTAL );
#if defined(__WXGTK__) || defined(__WXMOTIF__) || defined(__WXMAC__) || defined(__WXMGL__) || defined(__WXX11__)
    pToolBar->AddTool( Minimal_Calc, wxBitmap(wxBITMAP(playgreen)) );
#else
    // use a standard bitmap
    pToolBar->AddTool( Minimal_Calc, wxBitmap(wxBITMAP(csquery)) );
#endif    
    pToolBar->Realize();
    // *** new end
}


// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( _T("This is the About dialog of the minimal sample.\n")
                _T("Welcome to %s"), wxVERSION_STRING);

    wxMessageBox(msg, _T("About Minimal"), wxOK | wxICON_INFORMATION, this);
}


// *** new from now on
// CalcFrame --------------------------------------------------------------------------------------------

class CalcFrame: public wxFrame
{
    public:
        CalcFrame( wxWindow* parent, wxWindowID id,
                   const wxString& title, const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize );

        void calculate( void );

    private:
        void onfullstop( wxCommandEvent& event );
        void onclose( wxCommandEvent& event );
        void onclosewindow( wxCloseEvent& event );
    
        wxStaticText* display;
        int iFullStop;

      DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(CalcFrame, wxFrame)
    EVT_MENU( ID_STOPCALC, CalcFrame::onfullstop )
    EVT_MENU( ID_CLOSECALC, CalcFrame::onclose )
    EVT_CLOSE( CalcFrame::onclosewindow )
END_EVENT_TABLE()

void MyFrame::OnCalc(wxCommandEvent& WXUNUSED(event))
{
    CalcFrame* pCalcFrame = new CalcFrame( this, -1, wxT("Calculate"), wxPoint(0, 0), wxSize(200,100) );
    pCalcFrame->Show(TRUE);
    pCalcFrame->calculate();
}

CalcFrame::CalcFrame( wxWindow* parent, wxWindowID id,
                      const wxString& title, const wxPoint& pos, const wxSize& size ) :
wxFrame( parent, id, title, pos, size )
{
    iFullStop = 0;

#if wxUSE_MENUS
    wxMenu *menuCalc = new wxMenu;

    menuCalc->Append(ID_STOPCALC, _T("&Stop\tAlt+S"), _T("Stop the calculation"));
    menuCalc->Append(ID_CLOSECALC, _T("&Close\tCtrl+C"), _T("Close this frame"));

    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuCalc, _T("&Stop"));

    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

    wxToolBar* pToolBar = CreateToolBar( wxNO_BORDER | wxTB_HORIZONTAL );
#if defined(__WXGTK__) || defined(__WXMOTIF__) || defined(__WXMAC__) || defined(__WXMGL__) || defined(__WXX11__)
    pToolBar->AddTool( ID_STOPCALC, wxBitmap(wxBITMAP(redcenter)) );
#else
    pToolBar->AddTool( ID_STOPCALC, wxBitmap(wxBITMAP(wxDISABLE_BUTTON_BITMAP)) );
#endif
    pToolBar->Realize();
  
    display = new wxStaticText( this, -1, wxT("0"), wxPoint( 10,70), wxSize( 155,30 ) );
}


void CalcFrame::calculate( void )
{
    wxString str;
 
    wxWindowDisabler wd( this );

    for ( int i = 0; i < 10000; i++ )
    {
        wxGetApp().Yield();
        if ( iFullStop )
        {
            return;
        }
        str.Printf( wxT("%d"), i);
        display->SetLabel(str);
    }
}


void CalcFrame::onfullstop( wxCommandEvent& WXUNUSED(event) )
{
    if ( iFullStop )
    {
        wxBell();
    }
    iFullStop = 1;
}

void CalcFrame::onclose( wxCommandEvent& WXUNUSED(event) )
{
    iFullStop = 1;
    Close();
}

void CalcFrame::onclosewindow( wxCloseEvent& event )
{
    if ( iFullStop )
    {
        event.Skip();
    }
    else
    {
        /*
            if ( wxMessageBox( wxT("Do you really want to stop the calculation?"), wxT(""),
                                     wxICON_QUESTION|wxYES_NO ) == wxYES
            )
        {
            iFullStop = 1;
        }
        if ( event.CanVeto() )
        {
            event.Veto();
        }
        */
        iFullStop = 1;
    }
}

 	  	 

/////////////////////////////////////////////////////////////////////////////
// Name:        minimal.cpp
// Purpose:     Minimal wxWindows sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id: minimal.cpp,v 1.57 2002/04/07 21:12:45 JS Exp $
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
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size,
            long style = wxDEFAULT_FRAME_STYLE);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

protected :
    void OnButtonSelect (wxCommandEvent &event);
    
private:
    
    wxTextCtrl *display ;
    bool        finished ;
    
    void SetDisplay (wxString &label) ;
    // any class wishing to process wxWindows events must use this macro
    DECLARE_EVENT_TABLE()
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = 1,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT, 
    BUTTON_SELECT = 1000
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWindows
// ----------------------------------------------------------------------------

// the event tables connect the wxWindows events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
    EVT_BUTTON ( BUTTON_SELECT, MyFrame::OnButtonSelect)
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

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // create the main application window
    MyFrame *frame = new MyFrame(_T("Simple Calculator"),
                                 wxPoint(50, 50), wxSize(450, 340));

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
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size, long style)
       : wxFrame(NULL, -1, title, pos, size, style)
{
    
    finished = true ;
    
    // set the frame icon
    SetIcon(wxICON(mondrian));
    
    // Constants
    const int lineOffset = 25 ;
    const int smallColumnOffset = 25 ; 
    const int largeColumnOffset = 50 ;
    const wxSize longButtonSize = wxSize (largeColumnOffset-1, lineOffset-1) ;
    const wxSize smallButtonSize = wxSize (smallColumnOffset-1, lineOffset-1) ;
    const wxSize squareButtonSize = wxSize (2*smallColumnOffset-1, 2*lineOffset-1) ;
    const wxSize highButtonSize = wxSize (smallColumnOffset-1, 2*lineOffset-1) ;
    wxColour wc ;
    wxButton *b, *b1 ;


    // Create the display
    display = new wxTextCtrl (this, -1, wxEmptyString, wxPoint (1, 4), wxSize (200, lineOffset), wxTE_RIGHT) ;
    
    // All buttons of the calculator
    wc = wxColour (200,200, 150) ;
    int line = 10 + lineOffset ;
    b= new wxButton (this, BUTTON_SELECT, "sin", wxPoint (largeColumnOffset*0+1 ,line), longButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b1 = new wxButton (this, BUTTON_SELECT, "cos", wxPoint (largeColumnOffset*1+1 ,line), longButtonSize) ;
    // b1->SetForegroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, "tan", wxPoint (largeColumnOffset*2+1 ,line), longButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, "1/x", wxPoint (largeColumnOffset*3+1 ,line), longButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    
    line += lineOffset ;
    b = new wxButton (this, BUTTON_SELECT, "log", wxPoint (largeColumnOffset*0+1 ,line), longButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, "ln", wxPoint (largeColumnOffset*1+1 ,line), longButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, "(", wxPoint (largeColumnOffset*2+1 ,line), longButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, ")", wxPoint (largeColumnOffset*3+1 ,line), longButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    
    line +=10 ;
    line += lineOffset ;
    wc = wxColour (150,150,200) ;
    b = new wxButton (this, BUTTON_SELECT, "MC", wxPoint (largeColumnOffset*0+1 ,line), longButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, "MR", wxPoint (largeColumnOffset*1+1 ,line), longButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, "M+", wxPoint (largeColumnOffset*2+1 ,line), longButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, "<--", wxPoint (largeColumnOffset*3+1 ,line), longButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    
    line += 5 ;
    line += lineOffset ;
    wc = wxColour (150,100,100) ;
    b = new wxButton (this, BUTTON_SELECT, "7", wxPoint (largeColumnOffset*0+1 ,line), squareButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, "8", wxPoint (largeColumnOffset*1+1 ,line), squareButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, "9", wxPoint (largeColumnOffset*2+1 ,line), squareButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    wc = wxColour(50,150,150) ;
    b = new wxButton (this, BUTTON_SELECT, "*", wxPoint (largeColumnOffset*3+1 ,line), longButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, "/", wxPoint (largeColumnOffset*3+1 ,line+lineOffset), longButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    
    line += 2*lineOffset ;
    wc = wxColour (150,100,100) ;
    b = new wxButton (this, BUTTON_SELECT, "4", wxPoint (largeColumnOffset*0+1 ,line), squareButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, "5", wxPoint (largeColumnOffset*1+1 ,line), squareButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, "6", wxPoint (largeColumnOffset*2+1 ,line), squareButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    wc = wxColour(50,150,150) ;
    b = new wxButton (this, BUTTON_SELECT, "+", wxPoint (largeColumnOffset*3+1 ,line), longButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, "-", wxPoint (largeColumnOffset*3+1 ,line+lineOffset), longButtonSize) ;
    
    line += 2*lineOffset ;
    wc = wxColour (150,100,100) ;
    b = new wxButton (this, BUTTON_SELECT, "1", wxPoint (largeColumnOffset*0+1 ,line), squareButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, "2", wxPoint (largeColumnOffset*1+1 ,line), squareButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, "3", wxPoint (largeColumnOffset*2+1 ,line), squareButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    wc = wxColour(50,150,150) ;
    b = new wxButton (this, BUTTON_SELECT, "%", wxPoint (largeColumnOffset*3+1 ,line), longButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, "^", wxPoint (largeColumnOffset*3+1 ,line+lineOffset), longButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    
    line += 2*lineOffset ;
    wc = wxColour (150,100,100) ;
    b = new wxButton (this, BUTTON_SELECT, "(-)",wxPoint(largeColumnOffset*0+1 ,line), squareButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, "0", wxPoint (largeColumnOffset*1+1 ,line), squareButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    wc = wxColour(50,150,150) ;
    b = new wxButton (this, BUTTON_SELECT, ".", wxPoint (largeColumnOffset*2+1 ,line), squareButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    b = new wxButton (this, BUTTON_SELECT, "=", wxPoint (largeColumnOffset*3+1 ,line), squareButtonSize) ;
    // b->SetBackgroundColour (wc) ;
    
    this->SetSize (largeColumnOffset*4+8, line+3*lineOffset+10) ;
    
/*
#if wxUSE_MENUS
    // create a menu bar
    wxMenu *menuFile = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, _T("&About...\tF1"), _T("Show about dialog"));

    menuFile->Append(Minimal_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));

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

*/
}


// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // TRUE is to force the frame to close
    Close(TRUE);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( _T("This is the About dialog of the minimal sample.\n")
                _T("Welcome to %s"), wxVERSION_STRING);

    wxMessageBox(msg, _T("About Minimal"), wxOK | wxICON_INFORMATION, this);
}


void MyFrame::OnButtonSelect (wxCommandEvent &event)
{
   // wxMessageBox ("Button clicked")  ;
   wxButton * wx = (wxButton *) event.GetEventObject () ;
   wxString s = display->GetLabel () ;
   wxString bs = wx->GetLabel() ;
   
    if (!bs.Cmp("="))
    {
        double result ;
        int  errorposition ;
        char buffer[256] ;
        int i ;
        for (i=0; 
             i<(int)s.length()&& i<255; 
             i++) 
            buffer[i] = 
                (char) s.GetChar(i) ; 
        buffer[i]='\0' ;
        // int err = EvaluateD (buffer, &result, &errorposition) ;
        
        //if (err != E_OK)
       // {
       //    // throw exception
       //     wxMessageBox ("Sorry, I don't understand the expression ") ;
       //}
        
        sprintf (buffer, "%f", result) ;
        
        display->SetLabel (buffer) ;
        finished = true ;
    }
    else if (!bs.Cmp("<--"))
    {
        if (s.Length()>0) s.Truncate(s.Length()-1) ;
        display->SetLabel(s) ;
    }
    else 
    {
        if (finished) s.Clear ();
        s.Append (wx->GetLabel()) ;
        finished = false ;
        display->SetLabel (s) ;
    }
}


 	  	 

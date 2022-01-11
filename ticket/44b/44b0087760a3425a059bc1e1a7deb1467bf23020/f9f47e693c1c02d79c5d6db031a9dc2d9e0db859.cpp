/////////////////////////////////////////////////////////////////////////////
// Name:        testCSConv.cpp
// Purpose:     wxCSConv testing
// Author:      Manuel Martin
// Modified by:
// Created:     12/20/06
// Copyright:   (c) Manuel Martin
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/fontenc.h"
#include "wx/fontmap.h"

// Define our new application type
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};


///////////////////////////////////////////////////////////////////////////////
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    wxTextCtrl* tTC;
    void test_wxCSConv();

private:
    DECLARE_EVENT_TABLE()
};

// IDs for the controls and the menu commands
enum
{
    // menu items
    tst_Quit = wxID_EXIT,
    tst_About = wxID_ABOUT,

};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(tst_Quit,  MyFrame::OnQuit)
    EVT_MENU(tst_About, MyFrame::OnAbout)
END_EVENT_TABLE()


IMPLEMENT_APP(MyApp)

// ============================================================================
// implementation
// ============================================================================


// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    // create the main application window
    MyFrame *frame = new MyFrame(wxT("wxCSConv test"));

    frame->Show(true);
    frame->test_wxCSConv();

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
    SetIcon(wxICON(sample));

#if wxUSE_MENUS
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(tst_About, wxT("&About...\tF1"), wxT("Show about dialog"));

    fileMenu->Append(tst_Quit, wxT("E&xit\tAlt-X"), wxT("Quit this program"));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(helpMenu, wxT("&Help"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR

    CreateStatusBar(1);

#endif // wxUSE_STATUSBAR

    tTC = new wxTextCtrl(this, -1, wxT("TESTING...\n\n"), wxDefaultPosition,
                         wxSize(600,450), wxTE_MULTILINE);

    Fit();
}

// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg =  wxT("wxCSConv test\n")
                    wxT("\n")
                    wxT("version 1.0\n")
                    wxT("By Manuel Martin\n");

    wxMessageBox(msg, wxT("About this app"), wxOK | wxICON_INFORMATION, this);
}

///////////////////////////////////////////////////////////////////////////////

// ============================================================================
// The function for doing testing
// ============================================================================

void MyFrame::test_wxCSConv()
{
    //Test all encodings enumerated in fontenc.h
    //and try to get each name using wxFontMapper

    tTC->AppendText(wxT("Testing wx encodings:\n"));
    tTC->AppendText(wxT("=====================\n"));

#if wxUSE_FONTMAP
    wxFontMapper* fomap = wxFontMapper::Get();
    if (!fomap)
    {   tTC->AppendText(wxT("Error: No wxFontMapper instance\n"));
        return;
    }
#else
    tTC->AppendText(wxT("Warning: wxUSE_FONTMAP is not defined"));
#endif

    wxFontEncoding encoding = wxFONTENCODING_SYSTEM;
    int i = (int) encoding;
    wxString str;
    wxCSConv* conv;
    bool res;

    for ( ; encoding <= wxFONTENCODING_MAX; encoding = (wxFontEncoding)++i)
    {
        str.Printf( wxT("Creating wxCSConv with  %d  "), encoding);
#if wxUSE_FONTMAP
        str.Append(wxT("("));
        str.Append( fomap->GetEncodingName(encoding) );
        str.Append(wxT(")"));
#endif
        tTC->AppendText(str);
        conv = new wxCSConv(encoding);
        res = conv->IsOk();
        str = wxT("   wxCSConv::IsOk() returned  ");
        str.Append( res ? wxT("TRUE") : wxT("FALSE") );
        tTC->AppendText(str);

        wxDELETE(conv);
        tTC->AppendText(wxT("\n"));
    }
    tTC->AppendText(wxT("\n"));

    tTC->AppendText(wxT("Testing special and wrong encodings:\n"));
    tTC->AppendText(wxT("====================================\n"));

    str = wxT("Creating wxCSConv with  wxFONTENCODING_SYSTEM");
    tTC->AppendText(str);
    conv = new wxCSConv(wxFONTENCODING_SYSTEM);
    res = conv->IsOk();
    str = wxT("  wxCSConv::IsOk() returned  ");
    str.Append( res ? wxT("TRUE") : wxT("FALSE") );
    tTC->AppendText(str);
    wxDELETE(conv);
    tTC->AppendText(wxT("\n"));

    str = wxT("Creating wxCSConv with  wxFONTENCODING_MAX");
    tTC->AppendText(str);
    conv = new wxCSConv(wxFONTENCODING_MAX);
    res = conv->IsOk();
    str = wxT("  wxCSConv::IsOk() returned  ");
    str.Append( res ? wxT("TRUE") : wxT("FALSE") );
    tTC->AppendText(str);
    wxDELETE(conv);
    tTC->AppendText(wxT("\n"));

    str = wxT("Creating wxCSConv with  encoding = wxFONTENCODING_MAX + 10 ");
    tTC->AppendText(str);
    encoding = (wxFontEncoding)(wxFONTENCODING_MAX + 10);
    conv = new wxCSConv(encoding);
    res = conv->IsOk();
    str = wxT("  wxCSConv::IsOk() returned  ");
    str.Append( res ? wxT("TRUE") : wxT("FALSE") );
    tTC->AppendText(str);
    wxDELETE(conv);
    tTC->AppendText(wxT("\n"));

    str = wxT("Creating wxCSConv with  -5");
    tTC->AppendText(str);
    conv = new wxCSConv((wxFontEncoding)-5);
    res = conv->IsOk();
    str = wxT("  wxCSConv::IsOk() returned  ");
    str.Append( res ? wxT("TRUE") : wxT("FALSE") );
    tTC->AppendText(str);
    wxDELETE(conv);
    tTC->AppendText(wxT("\n"));
    tTC->AppendText(wxT("\n"));

    //-----------------------------------------------------------------------
    //Now try using charsets
    tTC->AppendText(wxT("Testing with charsets:\n"));
    tTC->AppendText(wxT("======================\n"));

    str = wxT("Creating wxCSConv with  'ISO-8859-1'");
    tTC->AppendText(str);
    conv = new wxCSConv(wxT("ISO-8859-1"));
    res = conv->IsOk();
    str = wxT("  wxCSConv::IsOk() returned  ");
    str.Append( res ? wxT("TRUE") : wxT("FALSE") );
    tTC->AppendText(str);
    wxDELETE(conv);
    tTC->AppendText(wxT("\n"));

    str = wxT("Creating wxCSConv with  'WINDOWS-437'");
    tTC->AppendText(str);
    conv = new wxCSConv(wxT("WINDOWS-437"));
    res = conv->IsOk();
    str = wxT("  wxCSConv::IsOk() returned  ");
    str.Append( res ? wxT("TRUE") : wxT("FALSE") );
    tTC->AppendText(str);
    wxDELETE(conv);
    tTC->AppendText(wxT("\n"));

    str = wxT("Creating wxCSConv with  'utf8'");
    tTC->AppendText(str);
    conv = new wxCSConv(wxT("utf8"));
    res = conv->IsOk();
    str = wxT("  wxCSConv::IsOk() returned  ");
    str.Append( res ? wxT("TRUE") : wxT("FALSE") );
    tTC->AppendText(str);
    wxDELETE(conv);
    tTC->AppendText(wxT("\n"));

    str = wxT("Creating wxCSConv with  'xKxK'");
    tTC->AppendText(str);
    conv = new wxCSConv(wxT("xKxK"));
    res = conv->IsOk();
    str = wxT("  wxCSConv::IsOk() returned  ");
    str.Append( res ? wxT("TRUE") : wxT("FALSE") );
    tTC->AppendText(str);
    wxDELETE(conv);
    tTC->AppendText(wxT("\n"));

    str = wxT("Creating wxCSConv with  ''");
    tTC->AppendText(str);
    conv = new wxCSConv(wxEmptyString);
    res = conv->IsOk();
    str = wxT("  wxCSConv::IsOk() returned  ");
    str.Append( res ? wxT("TRUE") : wxT("FALSE") );
    tTC->AppendText(str);
    wxDELETE(conv);
    tTC->AppendText(wxT("\n"));

    tTC->AppendText(wxT("\nEND TEST\n"));
}


 	  	 

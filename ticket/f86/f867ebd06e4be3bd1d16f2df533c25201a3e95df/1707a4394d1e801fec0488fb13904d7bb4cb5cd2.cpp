/////////////////////////////////////////////////////////////////////////////
// Name:        toolbar.cpp
// Purpose:     wxToolBar sample
// Author:      Julian Smart
// Modified by: Aidan Dunne ( DGI ) for testcase ( nov 2016 )
// Created:     04/01/98
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////


// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/toolbar.h"
#include "wx/log.h"
#include "wx/image.h"


// Define a new application
class MyApp : public wxApp
{
public:
    bool OnInit();
};

// Define a new frame
class MyFrame: public wxFrame
{
public:
    MyFrame(wxFrame *parent,wxWindowID id = wxID_ANY,
	const wxString& title = wxT("crash"),
	const wxPoint& pos = wxDefaultPosition,
	const wxSize& size = wxDefaultSize,
	long style = 
	    wxDEFAULT_FRAME_STYLE|wxCLIP_CHILDREN|wxNO_FULL_REPAINT_ON_RESIZE);
    
    virtual ~MyFrame() {}
    void Crash(wxCommandEvent &/*event*/);
    wxBitmap GenerateBitmap();
private:
    wxToolBar	    *_toolBar ;
    wxDECLARE_EVENT_TABLE();
};

const int ID_TOOLBAR = 500;
const int ID_CRASH_TOOL= 510;

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
   EVT_MENU(ID_CRASH_TOOL,MyFrame::Crash)
wxEND_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    MyFrame* frame = new MyFrame((wxFrame *) NULL, wxID_ANY,
                                 wxT("wxToolBar Sample"),
                                  wxPoint(100, 100), wxSize(650, 300));

    frame->Show(true);
    //wxInitAllImageHandlers();
    return true;
}

//MyFrame
MyFrame::MyFrame(wxFrame* parent,wxWindowID id,
		 const wxString& title,const wxPoint& pos,
		 const wxSize& size,long style)
       : wxFrame(parent, id, title, pos, size, style)
{
    _toolBar = NULL;
    SetIcon(wxICON(sample));
    // Create & realize the toolbar, with a single button
    _toolBar = new wxToolBar(this,-1,wxDefaultPosition,wxDefaultSize,wxTB_HORIZONTAL,wxT(""));
    wxBitmap toolBarBitmap = GenerateBitmap();
    _toolBar->AddTool(ID_CRASH_TOOL, wxT("crash"), toolBarBitmap, wxT(""));
    _toolBar->Realize();
}

// the tool item handler:
void MyFrame::Crash(wxCommandEvent &/*event*/)
{
    // here's the crash; handler for tool event destroys the
    // containing toolbar. This works fine under wx 3.0.1

    _toolBar->Destroy();
}


// some bitmap generation code for the tool icon 
// fastest way (for me) to embed an arbitrary bitmap within the testcase
wxBitmap MyFrame::GenerateBitmap()
{
    static const char *xpm_data[] = {
        /* columns rows colors chars-per-pixel */
        "32 32 2 1",
        "a c Red",
        "b c #FFFFFF",
        /* pixels */
        "bbbaaaaaaaaaaaaaaaaaaaaaaaaaabbb",
        "bbbbaaaaaaaaaaaaaaaaaaaaaaaabbbb",
        "bbbbbaaaaaaaaaaaaaaaaaaaaaabbbbb",
        "abbbbbaaaaaaaaaaaaaaaaaaaabbbbba",
        "aabbbbbaaaaaaaaaaaaaaaaaabbbbbaa",
        "aaabbbbbaaaaaaaaaaaaaaaabbbbbaaa",
        "aaaabbbbbaaaaaaaaaaaaaabbbbbaaaa",
        "aaaaabbbbbaaaaaaaaaaaabbbbbaaaaa",
        "aaaaaabbbbbaaaaaaaaaabbbbbaaaaaa",
        "aaaaaaabbbbbaaaaaaaabbbbbaaaaaaa",
        "aaaaaaaabbbbbaaaaaabbbbbaaaaaaaa",
        "aaaaaaaaabbbbbaaaabbbbbaaaaaaaaa",
        "aaaaaaaaaabbbbbaabbbbbaaaaaaaaaa",
        "aaaaaaaaaaabbbbbbbbbbaaaaaaaaaaa",
        "aaaaaaaaaaaabbbbbbbbaaaaaaaaaaaa",
        "aaaaaaaaaaaaabbbbbbaaaaaaaaaaaaa",
        "aaaaaaaaaaaaabbbbbbaaaaaaaaaaaaa",
        "aaaaaaaaaaaabbbbbbbbaaaaaaaaaaaa",
        "aaaaaaaaaaabbbbbbbbbbaaaaaaaaaaa",
        "aaaaaaaaaabbbbbaabbbbbaaaaaaaaaa",
        "aaaaaaaaabbbbbaaaabbbbbaaaaaaaaa",
        "aaaaaaaabbbbbaaaaaabbbbbaaaaaaaa",
        "aaaaaaabbbbbaaaaaaaabbbbbaaaaaaa",
        "aaaaaabbbbbaaaaaaaaaabbbbbaaaaaa",
        "aaaaabbbbbaaaaaaaaaaaabbbbbaaaaa",
        "aaaabbbbbaaaaaaaaaaaaaabbbbbaaaa",
        "aaabbbbbaaaaaaaaaaaaaaaabbbbbaaa",
        "aabbbbbaaaaaaaaaaaaaaaaaabbbbbaa",
        "abbbbbaaaaaaaaaaaaaaaaaaaabbbbba",
        "bbbbbaaaaaaaaaaaaaaaaaaaaaabbbbb",
        "bbbbaaaaaaaaaaaaaaaaaaaaaaaabbbb",
        "bbbaaaaaaaaaaaaaaaaaaaaaaaaaabbb"
        };
        return wxBitmap ( xpm_data );
}
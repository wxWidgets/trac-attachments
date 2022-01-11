// wxSplitterWindow / multiline wxTextCtrl with border test.
//
// Attempting to drag the split line sometimes fails when a cursor indicating
// that the mouse pointer is over the split line is shown.
//
// To see this problem, start with the mouse cursor in the text area below the
// split line and move it up until it changes to the "drag" cursor (but be
// careful not to move it beyond the point where it first changes). Now attempt
// to drag the split line. Dragging the split line doesn't work for me when
// using wxWindows 2.4.2 with GTK2 2.2.4 on Linux.
//


#define BREAK_IT


// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/app.h"
    #include "wx/frame.h"

    #include "wx/scrolwin.h"
    #include "wx/textdlg.h"
#endif

#include "wx/splitter.h"



struct MyFrame: public wxFrame
{
    MyFrame()
      : wxFrame( NULL, -1, _T("wxSplitterWindow Test") )
    {
        wxSplitterWindow *splitter = new wxSplitterWindow( this, -1 );

        wxWindow *bottom = new wxTextCtrl( splitter, -1, _T("abc\n123"),
                                           wxDefaultPosition, wxDefaultSize,
										   wxTE_MULTILINE
#ifndef BREAK_IT
										   | wxNO_BORDER
#endif
										   );

        splitter->SplitHorizontally( new wxPanel( splitter ), bottom, 100 );
    }
};


struct MyApp: public wxApp
{
    MyApp() { }

    virtual bool OnInit()
    {
        (new MyFrame)->Show(TRUE);

        return TRUE;
    }
};

IMPLEMENT_APP( MyApp )

 	  	 

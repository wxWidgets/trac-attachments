// This program demonstrates a bug that can occur when using a pop-up menu with
// a wxGrid (on Win XP).
//
// Right click to display the pop-up menu. Now (while the pop-up menu is
// visible) left click on a column label. All subsequent mouse events go to a
// column label. E.g. clicking on the window close button appears to be
// processed as a click on a column label!  Moving the window by dragging the
// title bar will not be possible.
//

#ifdef __GNUG__
    #pragma implementation
    #pragma interface
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/grid.h"


struct GridFrame : public wxFrame
{
    GridFrame::GridFrame()
      : wxFrame( (wxFrame *)NULL, -1, "" )
    {
        wxGrid *grid = new wxGrid( this, -1 );
        grid->CreateGrid( 100, 100 );
    }

    void GridFrame::OnCellRightClick( wxGridEvent& ev )
    {
        wxMenu menu;
        menu.Append( 9666, _T("Junk") );
        PopupMenu( &menu, ev.GetPosition() );
    }

    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE( GridFrame, wxFrame )
    EVT_GRID_CELL_RIGHT_CLICK( GridFrame::OnCellRightClick )
END_EVENT_TABLE()



struct GridApp : public wxApp
{
    bool GridApp::OnInit()
    {
	(new GridFrame)->Show( TRUE );
        return TRUE;
    }
};

IMPLEMENT_APP( GridApp )

 	  	 

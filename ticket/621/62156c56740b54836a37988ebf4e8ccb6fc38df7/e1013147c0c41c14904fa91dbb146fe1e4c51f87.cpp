#include <wx/wx.h>
#include <wx/gbsizer.h>

class Bugdemo: public wxApp
{
public:

    virtual bool    OnInit();
};

bool    Bugdemo::OnInit()
{
wxFrame         *frame;
wxGridBagSizer  *sizer;
int             i;

    // Create a frame and a grid bag sizer for its content

    frame = new wxFrame( NULL, wxID_ANY, "Bug demo" );
    sizer = new wxGridBagSizer();
    frame->SetSizer( sizer );

    // We want the sizer to have 3x2 cells. On the left we have a
    // text entry control, spanning 3 rows. In order to demonstrate
    // the bug we make it tall.

    sizer->Add( new wxTextCtrl( frame, wxID_ANY, wxEmptyString,
                                wxDefaultPosition, wxSize( 100, 500 ),
                                wxTE_MULTILINE ),
                wxGBPosition( 0, 0 ),
                wxGBSpan( 3, 1 ),
                wxALIGN_LEFT );

    // Now we create 3 buttons, one for each row.

    for ( i = 0 ; i < 3 ; i++ ) {

        sizer->Add( new wxButton( frame, wxID_ANY, "text" ),
                    wxGBPosition( i, 1 ),
                    wxGBSpan( 1, 1 ),
                    wxALIGN_CENTRE );
    }

    // Tell the sizer that all 3 rows are growable and that they have
    // an equal (and non-zero) weight when distributing the extra space

    for ( i = 0 ; i < 3 ; i++ ) {

        sizer->AddGrowableRow( i, 1 );
    }

    // Display the result. We expect the buttons on the right equally
    // spaced vertically - but they aren't. All the extra space forced
    // on the sizer by the tall TextCtrl is assigned to row 2, while
    // row 0 and 1 are only as tall as needed by the button.
    //
    // If you now make the frame taller by resizing it with the mouse,
    // you will see that the extra space you give *by the mouse* will be
    // equally distrubuted between rows. But the extra space that was
    // already there *at creation time* is not.

    sizer->Fit( frame );
    sizer->SetSizeHints( frame );
    frame->Show( true );
    return true;
}

wxIMPLEMENT_APP( Bugdemo );


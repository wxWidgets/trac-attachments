#include "wx/wx.h"
#include "wx/propgrid/propgrid.h"
#include "wx/propgrid/advprops.h"


class MyFrame : public wxFrame 
{ 
public: 
    MyFrame ( wxWindow* parent ); 
private:
    wxPropertyGrid *mPg;
};

MyFrame::MyFrame ( wxWindow *parent ) : wxFrame ( parent, wxID_ANY, wxT("PropertyGrid Test") )
{
    wxPropertyGrid *pg = new wxPropertyGrid( this, -1, wxDefaultPosition, wxSize ( 400, 400 ),
                        wxPG_SPLITTER_AUTO_CENTER | wxPG_BOLD_MODIFIED );
    mPg = pg;

    wxPGChoices eech;
	for ( wxUint32 i = 0; i < 49; ++i ) { eech.Add ( wxString() << i ); }

    pg->Append ( new wxEditEnumProperty ( "EditEnumProperty", wxPG_LABEL, eech ) );

    SetSize ( 400, 600 );
}

class MyApplication : public wxApp
{
public:
	virtual bool OnInit();
private:
    MyFrame *mpFrame;
};

IMPLEMENT_APP( MyApplication)

bool MyApplication::OnInit()
{
    mpFrame = new MyFrame ( NULL );
    mpFrame->Show ( true );

	return true;
}
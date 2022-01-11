#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#	include "wx/wx.h"
#endif

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyCombo : public wxComboBox
{
public:
    MyCombo( wxWindow *pParent ) : wxComboBox( pParent, -1 )
    {
	Append( "Item #1" );
	Append( "Item #2" );
	Append( "Item #3" );
	Append( "Item #4" );
	Append( "Item #5" );
    }
    void OnSelection(wxCommandEvent& event)
    {
	wxMessageDialog MsgDlg( 0, "Hello" );
	MsgDlg.ShowModal();
    }
private:
    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyCombo, wxComboBox)
    EVT_COMBOBOX(-1,MyCombo::OnSelection)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxFrame *frame = new wxFrame(0, -1, "Minimal wxWindows App", wxPoint(50, 50), wxSize(450, 340));
    new MyCombo( frame );
    frame->Show(TRUE);
    return TRUE;
}

 	  	 

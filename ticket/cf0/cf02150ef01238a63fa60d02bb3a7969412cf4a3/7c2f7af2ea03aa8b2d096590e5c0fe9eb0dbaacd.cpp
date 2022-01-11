/*
** A simple app to demonstrate that using the wxSTAY_ON_TOP style with a
** wxMessageDialog causes a "HELP" button to be displayed (on Linux with
** GTK1.2).
*/

#include "wx/wx.h"

struct TestApp : wxApp
{
	virtual bool OnInit()
	{
		wxMessageDialog dlg( NULL, wxT( "Dialog Text" ), wxT( "Dialog Header" ),
							 wxICON_INFORMATION | wxOK | wxSTAY_ON_TOP |
							 wxCENTRE );
		dlg.ShowModal();

		return false;
	}
};

IMPLEMENT_APP(TestApp)

 	  	 

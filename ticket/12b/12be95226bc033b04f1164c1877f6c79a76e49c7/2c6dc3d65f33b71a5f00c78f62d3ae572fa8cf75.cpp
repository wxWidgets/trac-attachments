#include <wx/wx.h>
#include <wx/stc/stc.h>


class MyEditor : public wxStyledTextCtrl
{
public:
	MyEditor( wxWindow *parent, int id )
		: wxStyledTextCtrl( parent, id, wxDefaultPosition, wxDefaultSize )
	{
	}

	void OnCharAdded( wxStyledTextEvent &evt )
	{

		wxUniChar ch = evt.GetKey();
		if ( ch == '(' )
		{
			if (CallTipActive()) Cancel();

			CallTipShow( GetCurrentPos(), wxString("Very Simple CallTip!") );
		}
		else if ( ch == ')' )
		{
			if (CallTipActive()) Cancel();
		}

		evt.Skip();
	} 

	DECLARE_EVENT_TABLE();
};

BEGIN_EVENT_TABLE( MyEditor, wxStyledTextCtrl )
	EVT_STC_CHARADDED( wxID_ANY, MyEditor::OnCharAdded )
END_EVENT_TABLE()



class MyApp : public wxApp
{
public:
	bool OnInit()
	{
		wxFrame *frame = new wxFrame( 0, wxID_ANY, "STC Test", wxDefaultPosition, wxSize(600,400) );
		new MyEditor( frame, wxID_ANY );
		frame->Show();
		return true;
	}
};

IMPLEMENT_APP( MyApp );

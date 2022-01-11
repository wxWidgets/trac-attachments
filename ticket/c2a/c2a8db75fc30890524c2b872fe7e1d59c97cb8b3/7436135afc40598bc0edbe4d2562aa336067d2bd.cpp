#include <wx/wx.h>
#ifdef __WXMAC__
#include <ApplicationServices/ApplicationServices.h>
#endif

class toolwnd : public wxFrame
{
public:
	toolwnd( void ) : wxFrame( 0, -1, wxT( "Test" ), wxDefaultPosition, wxDefaultSize, wxFRAME_TOOL_WINDOW | wxCAPTION ) {  }
};

class app : public wxApp
{
	virtual bool OnInit( void )
	{
#ifdef __WXMAC__
		ProcessSerialNumber PSN;
		GetCurrentProcess( &PSN );
		TransformProcessType( &PSN, kProcessTransformToForegroundApplication );
#endif

		toolwnd *tw = new toolwnd;
		tw->Show();
		return TRUE;
	}
};

IMPLEMENT_APP( app )


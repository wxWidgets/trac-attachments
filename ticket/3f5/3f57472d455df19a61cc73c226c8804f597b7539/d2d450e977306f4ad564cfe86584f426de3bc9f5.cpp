#pragma warning ( push, 0 )
#include <wx/wxprec.h>
#include <boost/scoped_ptr.hpp>
#include <boost/timer.hpp>
#pragma warning ( pop )


// ----------------------------------------------------------------------------


class CMainFrame : public wxFrame
{
public:
	CMainFrame();

private:
	void OnPaint( wxPaintEvent & event );

	DECLARE_EVENT_TABLE()
	DECLARE_NO_COPY_CLASS( CMainFrame );
};


BEGIN_EVENT_TABLE( CMainFrame, wxFrame )
	EVT_PAINT( CMainFrame::OnPaint ) 
END_EVENT_TABLE()


CMainFrame::CMainFrame()
	: wxFrame( 0, wxID_ANY, _( "wxTestApp" ))
{
}


void
CMainFrame::OnPaint( wxPaintEvent & )
{
	wxPaintDC dc( this );
	boost::scoped_ptr< wxGraphicsContext > context( wxGraphicsRenderer::GetDefaultRenderer()->CreateContext(( wxPaintDC & )( dc )));

	// this demonstrates the off by one in rectangle size 
	// ( the red rectangle should be completely invisible, i.e. overdrawn by the green one -> it isn't )
	context->SetBrush( wxColour( 0xFF, 0, 0, 0xFF ));
	context->SetPen( wxColour( 0xFF, 0, 0, 0xFF ));
	context->DrawRectangle( 10, 10, 100, 100 );

	dc.SetBrush( wxColour( 0, 0xFF, 0, 0xFF ));
	dc.SetPen( wxColour( 0, 0xFF, 0, 0xFF ));
	dc.DrawRectangle( 10, 10, 100, 100 );

	// this demonstrates the abysmal performance of wxGraphicsContext (GDI+) compared to regular GDI
	// I understand there may be a performance difference if gradient brushes and transparency is used
	// but in a comparison like this there shouldn't be a factor ~30 difference in speed!
	{
	wxGraphicsContext & inner( *context ); 
	boost::timer timer;
	for ( size_t i = 0; i < 10000; ++i )
		inner.DrawRectangle( 10, 10, 100, 100 );
	const double elapsedContext = timer.elapsed();
	timer.restart();
	for ( size_t i = 0; i < 10000; ++i )
		dc.DrawRectangle( 10, 10, 100, 100 );
	const double elapsedGdi = timer.elapsed();
	wxString text;
	text << _( "context: " ) << elapsedContext << _( " seconds, gdi: " ) << elapsedGdi << _( " seconds" );
	dc.DrawText( text, 10, 240 );
	}

	// this demonstrates mistakes in the use of alpha transparency
	// 1) the brush color influences the pen color, which is wrong
	// 2) the four corners are drawn multiple times in pen color, thus get the wrong color again
	context->SetBrush( wxColour( 0x66, 0, 0, 0xFF ));
	context->SetPen( wxColour( 0, 0, 0x66, 0x66 ));
	context->DrawRectangle( 10, 120, 100, 100 );
}


// ----------------------------------------------------------------------------


class wxTestApp : public wxApp
{
public:
	wxTestApp() {}

private:
	virtual bool	OnInit();

	CMainFrame *	m_MainFrame;

	DECLARE_NO_COPY_CLASS( wxTestApp );
};


DECLARE_APP( wxTestApp );
IMPLEMENT_APP( wxTestApp )


bool	
wxTestApp::OnInit()
{
	m_MainFrame = new CMainFrame();
	m_MainFrame->Show();
	SetTopWindow( m_MainFrame );
	return true;
}


// ----------------------------------------------------------------------------

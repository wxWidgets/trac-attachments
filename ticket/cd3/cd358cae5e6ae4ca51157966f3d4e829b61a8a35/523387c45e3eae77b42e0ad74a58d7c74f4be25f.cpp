#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/dcgraph.h>
#include <wx/rawbmp.h>

void bitmapSetAlpha(wxBitmap *bmp, unsigned char alpha = wxALPHA_OPAQUE )
{
  wxAlphaPixelData bmdata(*bmp);
  if(bmdata==NULL) {
    wxLogDebug(wxT("bitmapSetAlpha() failed"));
    return;
  }

  wxAlphaPixelData::Iterator dst(bmdata);

  for(int y=0; y<bmp->GetHeight(); y++) {
    dst.MoveTo(bmdata, 0, y);
    for(int x=0; x<bmp->GetWidth(); x++) {
      dst.Alpha() = alpha;
      dst++;
    }
  }
}

class DrawTest : public wxWindow
{
public:
	DrawTest( wxWindow *parent )
		: wxWindow( parent, wxID_ANY )
	{
		SetBackgroundStyle( wxBG_STYLE_CUSTOM );
	}

	// small helper class to delete 
	class gcdc_ref 
	{
	public:
		gcdc_ref() { m_ptr = 0; }
		~gcdc_ref() { if (m_ptr != 0) delete m_ptr; }
		wxGCDC *m_ptr;
	};
	
	void Render( wxDC &dc, const wxRect &rect )
	{
		// if it is possible to create an antialiased DC from
		// the one passed in do it.  the gcdc_ref class keeps track
		// of the pointer and deletes it if a GCDC was created. (like a 'smart' pointer)
		gcdc_ref gdc;		
		if ( wxMemoryDC *memdc = dynamic_cast<wxMemoryDC*>( &dc ) )
			gdc.m_ptr = new wxGCDC( *memdc );
		else if ( wxWindowDC *windc = dynamic_cast<wxWindowDC*>( &dc ) )
			gdc.m_ptr = new wxGCDC( *windc );
	
		// reference to an 'anti-aliased' DC (if it was possible to create one)
		wxDC &aadc = gdc.m_ptr != 0 ? *gdc.m_ptr : dc; 

		// draw some stuff using the normal DC (faster, at least on win32)
		dc.SetBrush( *wxBLACK_BRUSH );
		dc.DrawRectangle( rect.x + 10, rect.y + 10, rect.width - 20, rect.height - 20 );

		dc.SetPen( wxPen( *wxBLUE, 2 ) );
		for ( int i=0;i<10;i++ )
		{
			int xpos = rect.x+rect.width-100+i*10;
			dc.DrawLine( xpos, rect.y, xpos-50, rect.y+rect.height );
		}

		// draw some stuff using the anti-aliased DC (looks better, but takes longer)
		aadc.SetPen( wxPen( *wxWHITE, 3 ) );
		aadc.SetBrush( *wxRED_BRUSH );
		aadc.DrawRoundedRectangle( rect.x + 20, rect.y+rect.height/2-20, rect.width-40, 40, 10 );
		aadc.DrawCircle( rect.x + rect.width/2, rect.y + rect.height/2, 50 );		

		// a little bit of text
		dc.SetTextForeground( *wxWHITE );
		dc.DrawText( "Text output", 15, 15 );
	}

	void OnPaint( wxPaintEvent & )
	{
		wxAutoBufferedPaintDC dc( this );
		
		// set up the font and backround for the screen
		dc.SetFont( GetFont() );
		dc.SetBackground( wxBrush( GetBackgroundColour() ) );
		dc.Clear();
		
		int width, height;
		GetClientSize( &width, &height );
		wxRect rect( 0, 0, width, height );
		Render( dc, rect );
	}

	void OnSize( wxSizeEvent & )
	{
		Refresh();
	}

	void Export( )
	{
		int width, height;
		GetClientSize( &width, &height );
		wxRect rect( 0, 0, width, height );

		wxBitmap bitmap( width, height, 32 );
		// attempt to initialize the alpha channel
		// per http://trac.wxwidgets.org/ticket/14922
		bitmapSetAlpha( &bitmap );

		wxMemoryDC memdc( bitmap );

		// setup the font and background
		wxFont font( *wxSWISS_FONT );
		font.SetPointSize( 20 );
		memdc.SetFont( font );
		memdc.SetBackground( *wxGREY_BRUSH );
		memdc.Clear();

		Render( memdc, rect );

		memdc.SelectObject( wxNullBitmap );
		
		bitmap.SaveFile( "draw.bmp", wxBITMAP_TYPE_BMP );
		bitmap.SaveFile( "draw.jpg", wxBITMAP_TYPE_JPEG );
		bitmap.SaveFile( "draw.png", wxBITMAP_TYPE_PNG );
	}

private:
	DECLARE_EVENT_TABLE();
};

BEGIN_EVENT_TABLE( DrawTest, wxWindow )
	EVT_PAINT( DrawTest::OnPaint )
	EVT_SIZE( DrawTest::OnSize )
END_EVENT_TABLE()


class MyApp : public wxApp
{
public:
	bool OnInit()
	{
		wxInitAllImageHandlers();

		wxFrame *frame1 = new wxFrame( 0, wxID_ANY, "Draw Test", 
			wxDefaultPosition, wxSize(400,300) );
		DrawTest *draw = new DrawTest( frame1 );

		frame1->Show();
		
		// export in 4 different formats for testing
		draw->Export();

		return true;
	}
};

IMPLEMENT_APP( MyApp );

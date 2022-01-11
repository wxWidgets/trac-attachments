#include <wx/wx.h>
#include <wx/image.h>
#include <wx/frame.h>

class MyApp : public wxApp
{
public:
	bool OnInit() 
	{
		::wxInitAllImageHandlers(); 

		class MyFrame : public wxFrame
		{
		public:
			MyFrame() : wxFrame( 0, -1, wxT( "test" ), wxDefaultPosition, wxSize( 100, 100 ) )
			{
				Connect( wxID_ANY, wxEVT_PAINT, wxPaintEventHandler( MyFrame::OnPaint ) );
				SetBackgroundColour( *wxWHITE );
				bitmap1_ = LoadPng( wxT("fully_transparent.png") );
				bitmap2_ = LoadPng( wxT("almost_transparent.png") );
			}

			void OnPaint( wxPaintEvent& e )
			{
				wxPaintDC dc( this );
				dc.DrawBitmap( bitmap1_, 4, 4 );
				dc.DrawBitmap( bitmap2_, 4 + bitmap1_.GetWidth() + 4, 4 );
			}
		private:
			wxBitmap LoadPng( wxString const& name )
			{
				wxBitmap bitmap;
				bitmap.LoadFile( name, wxBITMAP_TYPE_PNG );
				return bitmap;
			}

			wxBitmap bitmap1_, bitmap2_;	
		};
		(new MyFrame())->Show(true);
		return true;
	}
};
IMPLEMENT_APP(MyApp)

 	  	 

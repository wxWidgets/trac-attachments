#include "wx/image.h"
#include "Scale.h"
int main( int argc, char* argv[] )
{
  wxInitAllImageHandlers(); // void return
  wxImage image( "rgb_mark.xpm" );
  assert( image.SaveFile( "image.png", wxBITMAP_TYPE_PNG ) );

  const wxImageResizeQuality quality =
    // wxIMAGE_QUALITY_NEAREST
    //    wxIMAGE_QUALITY_BILINEAR
    //wxIMAGE_QUALITY_BICUBIC
     wxIMAGE_QUALITY_BOX_AVERAGE
    ;
#if 0
  wxImage image2( image.Scale( 256, 256, quality ) );
#else
  wxImage image2( Scale( image, 256, 256, quality ) );
#endif
  assert( image2.SaveFile( "image2.png", wxBITMAP_TYPE_PNG ) );
  return 0;
}// main

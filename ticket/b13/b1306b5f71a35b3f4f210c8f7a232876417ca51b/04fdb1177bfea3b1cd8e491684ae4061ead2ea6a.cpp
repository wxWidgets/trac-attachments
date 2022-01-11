#include "Scale.h"
#include "opencv2/imgproc.hpp"
#include <memory>
#include <iostream>

wxImage Scale( const wxImage& image,
	       int width,
	       int height,
	       wxImageResizeQuality quality )
{
  using namespace std;

  // The x and y dense tables
  cv::Mat map1( height, width, CV_32FC1 );
  cv::Mat map2( height, width, CV_32FC1 );

  // Create the two 1D output locations
  unique_ptr<float[]> rowLocs( new float[ height ] );
  for( int index = 0; index < height; ++index )
  {
    rowLocs[ index ] = index * ( image.GetHeight() - 1 ) / double( height - 1 );
  }
  unique_ptr<float[]> colLocs( new float[ width ] );
  for( int index = 0; index < width; ++index )
  {
    colLocs[ index ] = index * ( image.GetWidth() - 1 ) / double( width - 1 );
  }

  // Loop over every location in the destimation image
  for( int dstRow = 0; dstRow < height; ++dstRow )
  {
    for( int dstCol = 0; dstCol < width; ++dstCol )
    {
      map1.at<float>( dstRow, dstCol ) = colLocs[ dstCol ];
      map2.at<float>( dstRow, dstCol ) = rowLocs[ dstRow ];
    }
  }

  cv::Mat inMat( image.GetHeight(),
		 image.GetWidth(),
		 CV_8UC3,
		 image.GetData() ); // Not copied or owned

  // Ownership will be passed to the output wxImage
  unsigned char* data = (unsigned char*) malloc( height * width * 3 );

  cv::Mat outMat( height,
		  width,
		  CV_8UC3,
		  data );  // Not copied or owned

  int interpolation = 0;

  switch( quality )
  {
    //case wxIMAGE_QUALITY_NEAREST: // Same value as NORMAL
    case wxIMAGE_QUALITY_NORMAL:
    {
      interpolation = cv::INTER_NEAREST;
      break;
    }

    case wxIMAGE_QUALITY_BILINEAR:
    {
      interpolation = cv::INTER_LINEAR;
      break;
    }

    case wxIMAGE_QUALITY_BICUBIC:
    {
      interpolation = cv::INTER_CUBIC;
      break;
    }

    case wxIMAGE_QUALITY_BOX_AVERAGE:
    case wxIMAGE_QUALITY_HIGH:
    {
      cout << "*** BOX_AVERAGE and HIGH are only similar to cv:AREA" << endl;
      interpolation = cv::INTER_AREA;
      break;
    }
  }

  cv::remap( inMat,
	     outMat,
	     map1,
	     map2,
	     interpolation,
	     cv::BORDER_REPLICATE ); // Extrapolate source with border values

  wxImage outImage( width,
		    height,
		    data,
		    nullptr,   // No alpha
		    false );   // Free the data

  return outImage;
}// Scale

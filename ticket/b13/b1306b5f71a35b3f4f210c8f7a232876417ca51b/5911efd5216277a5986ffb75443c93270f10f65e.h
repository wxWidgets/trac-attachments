#ifndef SCALE_HH
#define SCALE_HH

#include "wx/image.h"

/*
wxIMAGE_QUALITY_NEAREST
wxIMAGE_QUALITY_BILINEAR
wxIMAGE_QUALITY_BICUBIC 
	
wxIMAGE_QUALITY_BOX_AVERAGE 	
Use surrounding pixels to calculate an average that will be used for new pixels.
This method is typically used when reducing the size of an image.

wxIMAGE_QUALITY_NORMAL 	
Default image resizing algorithm used by wxImage::Scale().
Currently the same as wxIMAGE_QUALITY_NEAREST.

wxIMAGE_QUALITY_HIGH 
Since version 2.9.2 this results in wxIMAGE_QUALITY_BOX_AVERAGE being used when 
reducing the size of the image (meaning that both the new width and height will 
be smaller than the original size). Otherwise wxIMAGE_QUALITY_BICUBIC is used. 
 */

wxImage Scale( const wxImage& image,
	       int width,
	       int height,
	       wxImageResizeQuality quality );

#endif

/////////////////////////////////////////////////////////////////////////////
// Name:        imagjbig.cpp
// Purpose:     wxImage JBIG1 handlers
// Author:      Bruno Schwander bruno at tinkerbox dot org
// Copyright:   (c) Bruno Schwander
// Licence:     GPL  
//              
// heavily based on Markus Kunh's pbmtojbg and jbgtopbm
//              -- http://www.cl.cam.ac.uk/~mgk25/jbigkit/
//
/////////////////////////////////////////////////////////////////////////////
#include "wx/defs.h"

#include "wx/bitmap.h"
#include "wx/debug.h"
#include "wx/log.h"
#include "wx/app.h"

extern "C"
{
    #include <jbig.h>
}

#include "wx/filefn.h"
#include "wx/wfstream.h"
#include "wx/intl.h"
#include "wx/module.h"

#include "imagjbig.h"


// For memcpy
#include <string.h>
#include <stdlib.h>

// Does not support multiple images
// Support only 1 or 8 planes (converted to RGB=> 8 planes max)

//-----------------------------------------------------------------------------
// wxJBIGHandler
//-----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC_CLASS(wxJBIGHandler,wxImageHandler)

//------------- JBIG Data Source Manager


/*
 * Call-back routine for merged image output,
 * writes an 8bit per pixel decoded image
 * to an RGB buffer
 */

extern "C"
{

  struct encbuf {
    unsigned char *start;
    unsigned char *next;
    size_t size;
    size_t bufSize;
  };

  void LINKAGEMODE eightBitToRGB(unsigned char *data, 
				 size_t len, 
				 void **destination)
  {
    /* fwrite(data, len, 1, (FILE *) destination);
 return;
    */
    unsigned char* d = *(unsigned char**)destination;
    unsigned char* src;

    src = data;

    size_t i = 0;
    for(i = 0; i < len; i++){
      *d = *src;
      d++;
      *d = *src;
      d++;
      *d = *src;
      d++;
      src++;
    }
    *(unsigned char**)destination += (3*len);
  }

  void LINKAGEMODE writeStream(unsigned char *start, size_t len, void *encBuf)
  {

    struct encbuf *sencBuf = (struct encbuf *)encBuf;

    size_t offset = sencBuf->next - sencBuf->start;
    size_t space_left = sencBuf->bufSize - offset;

    //  printf("writeStream : encBuf bufSize: %d\n", sencBuf->bufSize);

    
    if( space_left <= len ){
      sencBuf->bufSize = sencBuf->bufSize + len + 4096;
      sencBuf->start = (unsigned char *)malloc(sencBuf->bufSize);
      sencBuf->next = sencBuf->start + offset;
    }

    memcpy(sencBuf->next, start, len);
    sencBuf->next += len;
    sencBuf->size += len;

  }

}

void onebitByteToRGB(unsigned char *dest, unsigned char src,
		     int bits)
{
  int i=0;
  unsigned char val = 0;
  unsigned char s = src;
  for(i = 0; i<bits; i++){
    val = (s & 0x80)? 0x0:0xFF;
    *dest = val;
    dest++;
    *dest = val;
    dest++;
    *dest = val;
    dest++;
    s<<=1;
  }
}

void oneBitImgToRGB(unsigned char *dest, unsigned char *src,
		    int width, int height)
{
  
  int line, row;

  unsigned char *d, *s;
  d = dest; s = src;

  int bitsInLastByte = width % 8;
  int fullBytesPer1BitRow = (width / 8);
     
  for (line = 0; line < height; line++){
    for (row = 0; row < fullBytesPer1BitRow; row++){
      onebitByteToRGB(d, *s, 8);
      d+=24; // RGB, 8 pixel
      s++;
    }
    if(bitsInLastByte > 0){
      onebitByteToRGB(d, *s, bitsInLastByte);
      s++;
      d+= (3*bitsInLastByte);
    }
    
  }

}

// really just take the R channel...
void RGBtoGray(unsigned char *dest, unsigned char *src,
	       size_t destSize)
{
  size_t i = 0;
  unsigned char *d, *s;
  d = dest; s = src;
  for(i=0; i< destSize; i++){
    *d = ~(*src);
    src+=3;
    d++;
  }
}

bool read_file(unsigned char** buf, size_t *buflen, 
	       size_t *len, wxInputStream& stream)
{
  

  if (*buflen == 0) {
    *buflen = 4096;
    *len = 0;
    *buf = (unsigned char*)malloc(*buflen);
    if (!*buf) {
      wxLogError("wxJBIGHandler::read_file: Sorry, not enough memory available!\n");
      return FALSE;
    }
  }
  do {
    
    *len += stream.Read(*buf + *len, *buflen - *len).LastRead();
    if (*len == *buflen) {
      *buflen *= 2;
      *buf = (unsigned char*)realloc(*buf, *buflen);
      if (!*buf) {
        wxLogError("wxJBIGHandler::read_file: Sorry, not enough memory available!\n");
        return FALSE;
      }
    }
    wxStreamError err = stream.LastError();
    if ((err == wxSTREAM_WRITE_ERROR) 
	|| (err == wxSTREAM_READ_ERROR)) {
      wxLogError("wxJBIGHandler::read_file: Problem while reading input file");
      return FALSE;
    }
  } while (!stream.Eof());
  *buflen = *len;
  *buf = (unsigned char*)realloc(*buf, *buflen);
  if (!*buf) {
    wxLogError("wxJBIGHandler::read_file: Oops, realloc failed when shrinking buffer!\n");
    return FALSE;
  }
  
  return TRUE;

}


bool wxJBIGHandler::LoadFile( wxImage *image, wxInputStream& stream, 
			      bool verbose, int WXUNUSED(index) )
{
  //  printf("wxJBIGHandler::LoadFile\n");

  struct jbg_dec_state s;
  size_t buflen, len, cnt;
  int result;
  bool use_graycode = TRUE;

  unsigned char *p;
  unsigned char *buffer = (unsigned char *)malloc(4096);

  if(!buffer){
    wxLogError( "wxJBIGHandler::LoadFile: could not allocate memory!\n");
    return FALSE;
  }

  buflen = 4096;

  jbg_dec_init(&s);

  if (image->HasOption(wxT("maxWidth")) 
      && image->HasOption(wxT("maxHeight")))
    jbg_dec_maxsize(&s, image->GetOptionInt(wxT("maxWidth")), 
		    image->GetOptionInt(wxT("maxHeight")));

  if (image->HasOption(wxT("useGrayCode"))){ 
    use_graycode = image->GetOptionInt(wxT("useGrayCode"));
  }


  len = stream.Read(buffer, 20).LastRead();
  if(len < 20){
    wxLogError("wxJBIGHandler: Input stream must be at least 20 bytes long !\n");
    return FALSE;
  };
  
  if (buffer[19] & JBG_VLENGTH) {
    /* VLENGTH = 1 => we might encounter a NEWLEN, therefore read entire
     * input file into memory and run two passes over it */
    read_file(&buffer, &buflen, &len, stream);
    /* scan for NEWLEN marker segments and update BIE header accordingly */
    result = jbg_newlen(buffer, len);
    /* feed data to decoder */
    if (result == JBG_EOK) {
      p = (unsigned char *) buffer;
      result = JBG_EAGAIN;
      while (len > 0 &&
             (result == JBG_EAGAIN || (result == JBG_EOK && 0))) {
        result = jbg_dec_in(&s, p, len, &cnt);
        p += cnt;
        len -= cnt;
      }
    }
  } else {
    /* VLENGTH = 0 => we can simply pass the input file directly to decoder */
    result = JBG_EAGAIN;
    do {
      cnt = 0;
      p = (unsigned char *) buffer;
      while (len > 0 &&
             (result == JBG_EAGAIN || (result == JBG_EOK && 0))) {
        result = jbg_dec_in(&s, p, len, &cnt);
        p += cnt;
        len -= cnt;
      }
      if (!(result == JBG_EAGAIN || (result == JBG_EOK && 0)))
        break;
      len = stream.Read(buffer, buflen).LastRead();
    } while (len > 0);
    wxStreamError err = stream.LastError();
    if ((err == wxSTREAM_WRITE_ERROR) 
	|| (err == wxSTREAM_READ_ERROR)) {
      wxLogError("Problem while reading input file");
      return FALSE;
    }
  }
  if (result != JBG_EOK && result != JBG_EOK_INTR) {
    wxLogError("Problem with input file: %s\n",
	    jbg_strerror(result, JBG_EN));
    return FALSE;
  }

  if (jbg_dec_getplanes(&s) == 1) {

    
    image->Create(jbg_dec_getwidth(&s),
		  jbg_dec_getheight(&s));
    image->SetOption(wxT("encodeBitPlanesNum"), 1);
    image->SetOption(wxT("planes"), 1);

    unsigned char *dat = image->GetData();
    
    oneBitImgToRGB(dat, 
		   jbg_dec_getimage(&s, 0),
		   jbg_dec_getwidth(&s),
		   jbg_dec_getheight(&s));
    
  } else {
    /* write PGM output file */
    size_t numPlanes = (size_t) jbg_dec_getplanes(&s);
    if ( numPlanes > 8) {
      wxLogError("Image has too many planes!\n");
      return FALSE;
    }

    image->Create(jbg_dec_getwidth(&s),
		  jbg_dec_getheight(&s));

    image->SetOption(wxT("encodeBitPlanesNum"), numPlanes);
    image->SetOption(wxT("planes"), numPlanes);

    unsigned char *dat = image->GetData();

    jbg_dec_merge_planes(&s, use_graycode, eightBitToRGB, &dat);

  }

  free(buffer);

  jbg_dec_free(&s);

  return TRUE;
}


bool wxJBIGHandler::SaveFile( wxImage *image, wxOutputStream& stream, bool verbose )
{
  //  printf("wxJBIGHandler::SaveFile\n");

  struct jbg_enc_state s;
  bool use_graycode = TRUE;
  int bpp, planes = 8, encode_planes = 1;
  unsigned long x = 640, y = 480;
  int dl = -1, dh = -1, d = -1, l0 = -1, mx = -1;
  int bpl;
  size_t bitmap_size;
  unsigned char **bitmap;
  int options = JBG_TPDON | JBG_TPBON | JBG_DPON;
  int order = JBG_ILEAVE | JBG_SMID;

  if (image->HasOption(wxT("useGrayCode"))){ 
    use_graycode = image->GetOptionInt(wxT("useGrayCode"));
  }

  if (image->HasOption(wxT("planes"))){ 
    planes = image->GetOptionInt(wxT("planes"));
  }

  if (image->HasOption(wxT("maxWidthLow"))){ 
    x = image->GetOptionInt(wxT("maxWidthLow"));
  }

  if (image->HasOption(wxT("maxHeightLow"))){ 
    y = image->GetOptionInt(wxT("maxHeightLow"));
  }
 
  if (image->HasOption(wxT("extraLayers"))){ 
    d = image->GetOptionInt(wxT("extraLayers"));
  }
 
  if (image->HasOption(wxT("linesPerStripesinLayer0"))){ 
    l0 = image->GetOptionInt(wxT("linesPerStripesinLayer0"));
  }
 
  if (image->HasOption(wxT("maxHOffsetAdaptativeTemplate"))){ 
    mx = image->GetOptionInt(wxT("maxHOffsetAdaptativeTemplate"));
  }

  // can be used to reduce bit depth...
  if (image->HasOption(wxT("encodeBitPlanesNum"))){ 
    encode_planes = image->GetOptionInt(wxT("encodeBitPlanesNum"));
  }

  bpl = (image->GetWidth() + 7)/8;
  bitmap_size = bpl * (size_t)image->GetHeight();
  
  bitmap = (unsigned char **) malloc(sizeof(unsigned char*) * encode_planes);
  if(!bitmap){
    wxLogError("wxJBIGHandler::SaveFile: could not alloc memory !\n");
    return FALSE;
  }

  int i = 0;
  for(i = 0; i < encode_planes; i++){
    bitmap[i] = (unsigned char *) malloc(bitmap_size);
    if(!bitmap[i]){
      wxLogError("wxJBIGHandler::SaveFile: could not alloc memory !\n");
      return FALSE;
    }
  }

  unsigned char *dat = (unsigned char *)image->GetData();
  unsigned char *imageBuf = (unsigned char *)malloc(image->GetWidth() 
						    * image->GetHeight() 
						    * sizeof(unsigned char));
  if(!imageBuf){
    wxLogError("wxJBIGHandler::SaveFile: could not alloc memory !\n");
    return FALSE;
  }

  RGBtoGray(imageBuf, dat, image->GetWidth() 
	    * image->GetHeight() * sizeof(unsigned char));
  

  jbg_split_planes(image->GetWidth(), image->GetHeight(), 
		   planes, encode_planes, imageBuf, bitmap,
		   use_graycode);


  struct encbuf encBuf;
  unsigned char *tmp = (unsigned char *)malloc(4096);
  encBuf.start = tmp;
  encBuf.next = tmp;
  encBuf.size = 0;
  encBuf.bufSize = 4096;

  jbg_enc_init(&s, image->GetWidth(), image->GetHeight(), 
	       encode_planes, bitmap, writeStream, &encBuf);

  /* Select number of resolution layers either directly or based
   * on a given maximum size for the lowest resolution layer */
  if (d >= 0){
    jbg_enc_layers(&s, d);
  }else{
    unsigned long mwidth = x;
    unsigned long mheight = y;
    jbg_enc_lrlmax(&s, mwidth, mheight);
  }

  jbg_enc_lrange(&s, dl, dh);
  jbg_enc_options(&s, order, options, l0, mx, -1);

  /* now encode everything and send it to data_out() */
  jbg_enc_out(&s);

  /* give encoder a chance to free its temporary data structures */
  jbg_enc_free(&s);

  if(stream.Write(encBuf.start, encBuf.size).LastWrite() 
     != encBuf.size){
    wxLogError("wxJBIGHandler::SaveFile: could not write file fully !\n");
    return FALSE;
  }

  free(encBuf.start);
  free(imageBuf);
  for(i = 0; i < encode_planes; i++){
    free(bitmap[i]);
  }
  free(bitmap);

  //  printf("wxJBIGHandler::SaveFile: saved !\n");

  return TRUE;
}

bool wxJBIGHandler::DoCanRead( wxInputStream& stream )
{
  //  printf("wxJBIGHandler::DoCanRead\n");
  
  // raw jbig lacks any magic number, etc. so just try 
  // to decompress a very small layer and see if it works...
  // (if the image has only one layer, it will decode the
  // whole image unfortunately...)
  wxImage img;
  img.SetOption("maxWidth", 10);
  img.SetOption("maxHeight", 10);

  return LoadFile(&img, stream, FALSE, 0);

}








 	  	 

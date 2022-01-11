// this is how we use the bitmap/dc/postscript changes
// hope someone can get use of it




//simplification of the tiffobject
class TiffWrapper : public PenObj
{
	public:
		//ctor, dtor
		TiffWrapper();
		~TiffWrapper();

	public:
		//methods
		int TiffRead();
		int TiffInit(bool fromPLX);

	public:
		//inherited methods
		virtual bool GetFromPLX(XpltDocument &doc);
		virtual void Show(wxDC &dc); //Anzeigen des Objekts
		virtual void Highlight(wxDC &dc, int i){}///TODO:noch implementieren

	private:
		char* mv_pImageDescriptor;
		long mv_pWidth;
		long mv_pHeight;
		wxMemoryDC *mv_pMaskDC;   //DrawingAccel for 1 bit tiff
		char *mv_pcFileName;
};



// display our tiffobject at the given dc
void TiffWrapper::Show(wxDC &dc)

{
	dc.SetPen( *GetPen() );
	dc.SetBackgroundMode(wxTRANSPARENT);
	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	DrawBoundingBox( dc );

	// size from bounding box (in _world_ coordinates)
	long w = abs( mp_pBBox->GetMaxX() - mp_pBBox->GetMinX() );
	long h = abs( mp_pBBox->GetMaxY() - mp_pBBox->GetMinY() );

	mv_pMaskDC->SetMapMode(dc.GetMapMode());
	mv_pMaskDC->SetUserScale((float)mv_pWidth/(float)w,(float)mv_pHeight/(float)h);
	dc.SetTextForeground(*wxRED);

	mv_pMaskDC->SetPen( *GetPen() );

	dc.SetTextForeground(GetPen()->GetColour());
	dc.SetTextBackground(GetPen()->GetColour());
	dc.SetBackgroundMode(wxTRANSPARENT);

#ifdef __WXGTK__

	dc.Blit(mp_pBBox->GetMinX(), mp_pBBox->GetMaxY(), w, h, mv_pMaskDC, 0, 0,wxCOPY,true);

#else // (MSW)
	if(mv_pMaskDC->GetSelectedBitmap().GetDepth()==1)
		dc.Blit(mp_pBBox->GetMinX(), mp_pBBox->GetMaxY(), w-5, -h+5, mv_pMaskDC, 0, 0,wxCOPY,true,0,0);
	else
		dc.Blit(mp_pBBox->GetMinX(), mp_pBBox->GetMaxY(), w-5, -h+5, mv_pMaskDC, 0, 0,wxCOPY,false,0,0);
#endif  	

	return;
}



//reading tiff images
int TiffWrapper::TiffRead()
{
    uint32 iw, ih,row,column;
    uint32 npixels;
    uint32 bytewidth;
    wxString filename(mv_pcFileName);
    wxBitmap * bmp = new wxBitmap();
    uint16 bitspersample;
    uint16 photometric = 0;
    uint8 bitmask=128;

    TIFF *tif = TIFFOpen(filename ,"r" );

    if (!tif)
    {
        if (true)
            wxLogError( _("TIFF: Error loading image.") );

        return FALSE;
    }

    TIFFGetField( tif, TIFFTAG_IMAGEWIDTH, &iw );
    TIFFGetField( tif, TIFFTAG_IMAGELENGTH, &ih );
    TIFFGetField(tif,TIFFTAG_BITSPERSAMPLE,&bitspersample);

    npixels = iw * ih;

    mv_pWidth=iw;
    mv_pHeight=ih;


    if (bitspersample==1)
    {
        bytewidth = iw/8;
        if (iw%8!=0)
            bytewidth+=1;
    }
    else
    {
        bytewidth=iw+3;
    }

    if (bitspersample==1)//loading b/w-tiff//
    {
        char * data = (char*)calloc((bytewidth)*(ih),sizeof(char));
        char * mask = (char*)calloc((bytewidth)*(ih),sizeof(char));

        for (row = 0; row < ih ; row++)
        {
            TIFFReadScanline(tif, (void*)(data+row*bytewidth), row, 0);
            if (photometric)
            {
                for (column=0;column<bytewidth ;column++)
                {
                    data[row*bytewidth+column]=~data[row*bytewidth+column];
                }
            }

            for (column=0;column<bytewidth ;column++)
            {
                uint8 reverse=0;
                bitmask=128;
                for (int bp=0;bp<8 ;bp++)
                {
                    if (data[row*bytewidth+column]&bitmask)
                        reverse = reverse | 1<<bp;
                    bitmask >>= 1;
                }
                #ifdef __WXGTK__
                data[row*bytewidth+column]=~reverse;

                #else //(MSW)

                data[row*bytewidth+column]=~reverse;
                mask[row*bytewidth+column]=reverse;
                #endif
            }

        }
        bmp = new wxBitmap((const char *)data,abs(iw),abs(ih),1);
        wxBitmap *maskbmp = new wxBitmap((const char *)mask,abs(iw),abs(ih),1);
        wxMask* bmask= new wxMask(*maskbmp);
        bmp->SetMask(bmask);
    }
    else//load colored image//
    {
        bmp->LoadFile( filename,wxBITMAP_TYPE_ANY );
        mv_pWidth = bmp->GetWidth();
        mv_pHeight = bmp->GetHeight();

    }

    // Create a memory DC
    mv_pMaskDC = new wxMemoryDC();
    mv_pMaskDC->SelectObject(*bmp);
    mv_pMaskDC->SetAxisOrientation(true,true);
    mv_pMaskDC->SetMapMode(MM_TEXT);


    return true;

}


 	  	 

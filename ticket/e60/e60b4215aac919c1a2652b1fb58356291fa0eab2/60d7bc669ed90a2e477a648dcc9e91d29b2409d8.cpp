
void wxGnomePrintDC::DoGetTextExtent(const wxString& string, wxCoord *width, wxCoord *height,
                     wxCoord *descent,
                     wxCoord *externalLeading,
                     wxFont *theFont ) const
{
    if ( width )
        *width = 0;
    if ( height )
        *height = 0;
    if ( descent )
        *descent = 0;
    if ( externalLeading )
        *externalLeading = 0;

    if (string.empty())
    {
        return;
    }

    // Set layout's text
#if wxUSE_UNICODE
    const wxCharBuffer data = wxConvUTF8.cWC2MB( string );
    const char *dataUTF8 = (const char *)data;
#else
    const wxWCharBuffer wdata = wxConvLocal.cMB2WC( string );
    if ( !wdata )
    {
        if (width) (*width) = 0;
        if (height) (*height) = 0;
        return;
    }
    const wxCharBuffer data = wxConvUTF8.cWC2MB( wdata );
    const char *dataUTF8 = (const char *)data;
#endif

    if ( !dataUTF8 )
    {
        // hardly ideal, but what else can we do if conversion failed?
        return;
    }

    PangoFontDescription *desc = (theFont) ? theFont->GetNativeFontInfo()->description : m_fontdesc;

    gint oldSize = pango_font_description_get_size( desc );
    double size = oldSize;
    size = size * m_scaleY;
    pango_font_description_set_size( desc, (gint)size );

    // apply scaled font
    pango_layout_set_font_description( m_layout, desc );

    pango_layout_set_text( m_layout, dataUTF8, strlen(dataUTF8) );

    int w, h;
    pango_layout_get_pixel_size( m_layout, &w, &h );


    if (width)
        *width = (wxCoord)(w / m_scaleX);
    if (height)
        *height = (wxCoord)(h / m_scaleY);

    if (descent)
    {
        PangoLayoutIter *iter = pango_layout_get_iter(m_layout);
        int baseline = pango_layout_iter_get_baseline(iter);
        pango_layout_iter_free(iter);
        *descent = h - PANGO_PIXELS(baseline);
    }

    // reset unscaled size
    pango_font_description_set_size( desc, oldSize );

    // reset unscaled font
    pango_layout_set_font_description( m_layout, m_fontdesc );
}

//-------------------------------------
// TEST CODE
//-------------------------------------

bool MyPrintout::OnPrintPage(int _page)
{
	MapScreenSizeToPage();

	wxDC* dc = GetDC();
	int w, h;

	// Test GetTextExtent()
	wxFont font1( 25, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false );
	dc->SetFont( font1 );

	wxString text = wxT("This is a test 1 of GetTextExtent()");
	dc->GetTextExtent(text, &w, &h);

	dc->DrawRectangle( 10, 10, w, h );
	dc->DrawText(text, 10, 10);

	wxFont font2( 15, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false );	

	text = wxT("This is a test 2 of GetTextExtent()");
	dc->GetTextExtent(text, &w, &h, NULL, NULL, &font2 );
	dc->SetFont( font2 );

	dc->DrawRectangle( 10, 80, w, h );
	dc->DrawText(text, 10, 80);

	return true;
}


 	  	 


include/wx/dc.h:
-----------------

class wxDCBase : public wxObject
{
public:

    ...

    void SetClippingRegion(const wxPoint* points, int n)
        { DoSetClippingRegion(points, n); }

    ...

protected:

    ...

    virtual void DoSetClippingRegion(const wxPoint* points, int n)
    {
        wxPoint *clipPoints = new wxPoint[n];

        // The clipping region must be in device units
        for (int i=0; i<n; i++)
        {
            clipPoints[i].x = LogicalToDeviceX( points[i].x );
            clipPoints[i].y = LogicalToDeviceY( points[i].y );
        }
        wxRegion clipRegion(n, clipPoints);

        // Implemented already in wxMemoryDC, wxPrinterDC, wxWindowDC...
        DoSetClippingRegionAsRegion(clipRegion);

        delete[] clipPoints;
    }

    ...

};

include/wx/gtk/gnome.h:
-----------------------

class wxGnomePrintDC : public wxDC
{
protected:

    ...

    // Special implemetation for wxGnomePrintDC
    void DoSetClippingRegion(const wxPoint* points, int n);

    ...
};

src/gtk/gnome/gprint.cpp:
-------------------------

void wxGnomePrintDC::DoSetClippingRegion(const wxPoint* points, int n)
{
    wxASSERT(n > 0);

    gs_lgp->gnome_print_gsave( m_gpc );

    gs_lgp->gnome_print_newpath( m_gpc );
    gs_lgp->gnome_print_moveto( m_gpc, XLOG2DEV( points[0].x ), YLOG2DEV( points[0].y ) );

    for (int i=1; i<n; i++)
    {
        gs_lgp->gnome_print_lineto( m_gpc, XLOG2DEV( points[i].x ), YLOG2DEV( points[i].y ) );
    }

    gs_lgp->gnome_print_closepath( m_gpc );
    gs_lgp->gnome_print_clip( m_gpc );

    // Calculate bounding rect
    int x, y, width, height;
    wxRegion clipRegion(n, points);
    clipRegion.GetBox(x, y, width, height);

    wxDC::DoSetClippingRegion( x, y, width, height );
}

include/wx/generic/dcpsg.h:
---------------------------

class wxPostScriptDC : public wxDC
{
protected:

    ...

    // Special implemetation for wxPostScriptDC
    void DoSetClippingRegion(const wxPoint* points, int n);

    ...
};

src/generic/dcpsg.cpp:
----------------------

void wxPostScriptDC::DoSetClippingRegion(const wxPoint* points, int n)
{
    wxASSERT(n > 0);

    PsPrintf( wxT("gsave\n newpath\n")
              wxT("%d %d moveto\n"), 
            LogicalToDeviceX( points[0].x ), LogicalToDeviceY( points[0].y ) );

    for (int i=1; i<n; i++)
    {
        PsPrintf( wxT("%d %d lineto\n"), 
            LogicalToDeviceX( points[i].x ), LogicalToDeviceY( points[i].y ) );
    }

    PsPrintf( wxT("closepath clip newpath\n") );

    m_clipping = true;

    // Calculate bounding rect
    int x, y, width, height;
    wxRegion clipRegion(n, points);
    clipRegion.GetBox(x, y, width, height);

    wxDC::DoSetClippingRegion( x, y, width, height );
}

//----------------------------------------
// TEST CODE
//----------------------------------------

bool MyPrintout::OnPrintPage(int _page)
{
	MapScreenSizeToPage();

	wxDC* dc = GetDC();

	// Clipping points
   wxPoint points[] = 
	{
		wxPoint(  10,  10 ),
		wxPoint( 210, 105 ),
		wxPoint(  10, 210 ),
		wxPoint(  10,  10 )
	};

	int n = sizeof(points) / sizeof(points[0]);

   // Set new clipping region
	dc->DestroyClippingRegion();
	dc->SetClippingRegion(points, n);

   // Uncomment these to see a difference 
   // (no clipping when printing on Linux, wrong clipping region on preview)
	//dc->DestroyClippingRegion();
	//dc->SetClippingRegion( wxRegion(n, points) );

	dc->SetBrush( *wxBLUE_BRUSH );
	dc->DrawRectangle( 10, 10, 200, 200 );

	dc->DestroyClippingRegion();

	wxPen pen(*wxRED_PEN);
	pen.SetWidth(2);
	dc->SetPen(pen);

	// Draw clipping outline
	dc->DrawLines(n, points);

	return true;
}


 	  	 

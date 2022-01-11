// imagxbm.h

#ifndef _WX_IMAGXBM_H_
#define _WX_IMAGXBM_H_

//-----------------------------------------------------------------------------
// wxXBMHandler
//-----------------------------------------------------------------------------

class wxXBMHandler: public wxImageHandler
{
public:
    inline wxXBMHandler()
    {
        m_name = wxT("XBM file");
        m_extension = wxT("xbm");
        m_type = wxBITMAP_TYPE_XBM;
        m_mime = wxT("image/xbm");
    }

#if wxUSE_STREAMS
    virtual bool LoadFile( wxImage *image, wxInputStream& stream, bool verbose=true, int index=-1 );
    virtual bool SaveFile( wxImage *image, wxOutputStream& stream, bool verbose=true );
    virtual bool DoCanRead( wxInputStream& stream );
#endif

private:
    DECLARE_DYNAMIC_CLASS(wxXBMHandler)
};

#endif
  // _WX_IMAGXBM_H_


 	  	 

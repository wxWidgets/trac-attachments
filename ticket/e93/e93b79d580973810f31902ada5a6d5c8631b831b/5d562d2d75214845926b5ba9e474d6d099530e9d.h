/////////////////////////////////////////////////////////////////////////////
// Name:        imagjbig.h
// Purpose:     wxImage JBIG1 handlers
// Author:      Bruno Schwander bruno at tinkerbox dot org
// Copyright:   (c) Bruno Schwander
// Licence:     GPL  
//              
// heavily based on Markus Kunh's pbmtojbg and jbgtopbm
//              -- http://www.cl.cam.ac.uk/~mgk25/jbigkit/
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_IMAGJBIG_H_
#define _WX_IMAGJBIG_H_

#include <wx/image.h>

//-----------------------------------------------------------------------------
// wxJBIGHandler
//-----------------------------------------------------------------------------

class wxJBIGHandler: public wxImageHandler
{
public:
    inline wxJBIGHandler()
    {
        m_name = wxT("JBIG file");
        m_extension = wxT("jbg");
        m_type = wxBITMAP_TYPE_ANY + 1;
        m_mime = wxT("image/jbig");
    };

    virtual bool LoadFile( wxImage *image, 
			   wxInputStream& stream, 
			   bool verbose=TRUE, int index=-1 );
    virtual bool SaveFile( wxImage *image, 
			   wxOutputStream& stream, bool verbose=TRUE );
    virtual bool DoCanRead( wxInputStream& stream );

private:
    DECLARE_DYNAMIC_CLASS(wxJBIGHandler)
};


#endif  // _WX_IMAGJBIG_H_


 	  	 

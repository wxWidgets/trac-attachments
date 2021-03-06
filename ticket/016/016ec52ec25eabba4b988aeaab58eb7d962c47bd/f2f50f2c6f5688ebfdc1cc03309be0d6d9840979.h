/////////////////////////////////////////////////////////////////////////////
// Name:        xh_grd.h
// Purpose:     XML resource handler for the grid control
// Author:      Agron Selimaj
// Created:     2005/08/11
// RCS-ID:      $Id: xh_grd.h,v 0.1 2005/08/11 09:17:06 VS Exp $
// Copyright:   (c) 2005 Agron Selimaj, Freepour Controls Inc.
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_GRD_H_
#define _WX_XH_GRD_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "xh_grd.h"
#endif

#include "wx/xrc/xmlres.h"

#if wxUSE_XRC


class WXDLLIMPEXP_XRC wxGridXmlHandler : public wxXmlResourceHandler  
{
DECLARE_DYNAMIC_CLASS(wxGridXmlHandler)
public:
	wxGridXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);
};

#endif // wxUSE_XRC


#endif // _WX_XH_GRD_H_

 	  	 

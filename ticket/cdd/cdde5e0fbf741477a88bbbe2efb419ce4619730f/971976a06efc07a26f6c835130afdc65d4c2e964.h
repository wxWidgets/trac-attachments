///////////////////////////////////////////////////////////////////////////////
// Name:        wx/LocalMenu.h
// Purpose:     LocalMenu allows retrieving the ID of the selected item directly
// Author:      Arne Steinarson
// Modified by:
// Created:     31.05.03
// RCS-ID:      
// Copyright:   (c) 2007 Arne Steinarson 
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////


#ifndef LOCALMENU_H
#define LOCALMENU_H

#include "wx/menu.h"

class wxMenuLocal : public wxMenu {
public:
	wxMenuLocal( const wxChar *title=_T(""), int style=0 ) : wxMenu(title,style), m_id(wxID_NONE) { }
	
	// Returns the ID of the selected item or wxID_NONE if error/no selection
	int PopupMenu( wxWindow *wnd, wxPoint pt=wxDefaultPosition );
	
protected:
	void OnCommand( wxCommandEvent& evt );
	int m_id;
	
	DECLARE_EVENT_TABLE();
};

#endif // LOCALMENU_H

 	  	 

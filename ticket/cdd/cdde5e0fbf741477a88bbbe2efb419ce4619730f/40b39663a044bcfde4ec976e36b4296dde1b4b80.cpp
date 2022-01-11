///////////////////////////////////////////////////////////////////////////////
// Name:        wx/MenuLocal.cpp
// Purpose:     LocalMenu allows retrieving the ID of the selected item directly
// Author:      Arne Steinarson
// Modified by:
// Created:     31.05.03
// RCS-ID:      
// Copyright:   (c) 2007 Arne Steinarson 
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#include "wx/MenuLocal.h"

BEGIN_EVENT_TABLE(wxMenuLocal, wxMenu)
    EVT_MENU(wxID_ANY, wxMenuLocal::OnCommand)
END_EVENT_TABLE()

int wxMenuLocal::PopupMenu( wxWindow *wnd, wxPoint pt ){_CFE_;
	if( !wnd ) return wxID_NONE;
	if( !wnd->PopupMenu(this,pt) ) return wxID_NONE;
	// Event handler will catch ID for us to return
	return m_id;
}

void wxMenuLocal::OnCommand(wxCommandEvent &evt){_CFE_;
	m_id = evt.GetId();
}


 	  	 

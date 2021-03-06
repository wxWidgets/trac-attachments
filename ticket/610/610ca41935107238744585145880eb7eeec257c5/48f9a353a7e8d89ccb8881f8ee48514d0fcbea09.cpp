// -*- C++ -*- generated by wxGlade 0.5 on Fri Aug 14 23:54:20 2009

/***************************************************************************
 *   Copyright (C) 2005 by Igor Korot                                      *
 *   igor@IgorsGentoo                                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

class CSelectTable : public wxDialog
{
	CSelecttable(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style);
};

CSelectTable::CSelectTable(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE)
{
	style = style;
	// begin wxGlade: CSelectTable::CSelectTable
	panel_1 = new wxPanel( this, wxID_ANY );
	m_tablesList = new wxListBox( panel_1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_MULTIPLE | wxLB_SORT );
	m_systemTables = new wxCheckBox( panel_1, wxID_SYSTEMTABLESHOWN, _T( "&Show system tables" ) );
	button_1 = new wxButton( panel_1, wxID_OK, _T( "&Open" ) );
	button_2 = new wxButton( panel_1, wxID_ANY, _T("&New..." ) );
	button_3 = new wxButton( panel_1, wxID_CANCEL, _T("&Cancel" ) );
	button_4 = new wxButton( panel_1, wxID_ANY, _T( "&Help" ) );
	SetTitle(wxT("Select Table"));
	button_1->SetDefault();
	button_1->Enable( false );
	for( int i = 0; i < 10; i++ )
	{
		wxString test;
		test.Printf( "Test string %d", i );
		m_tablesList->Append( test );
	}
	wxBoxSizer* sizer_1 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizer_3 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* sizer_4 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizer_6 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* sizer_5 = new wxBoxSizer(wxVERTICAL);
	sizer_2->Add(5, 20, 0, wxEXPAND, 0);
	sizer_3->Add(20, 5, 0, wxEXPAND, 0);
	sizer_5->Add(m_tablesList, 0, wxEXPAND, 0);
	sizer_5->Add(20, 5, 0, wxEXPAND, 0);
	sizer_5->Add(m_systemTables, 0, wxALIGN_BOTTOM, 0);
	sizer_4->Add(sizer_5, 0, wxEXPAND, 0);
	sizer_4->Add(5, 20, 0, wxEXPAND | wxALIGN_BOTTOM | wxFIXED_MINSIZE, 0);
	sizer_6->Add(button_1, 0, 0, 0);
	sizer_6->Add(20, 5, 0, wxEXPAND, 0);
	sizer_6->Add(button_2, 0, 0, 0);
	sizer_6->Add(20, 5, 0, wxEXPAND, 0);
	sizer_6->Add(button_3, 0, 0, 0);
	sizer_6->Add(20, 5, 0, wxEXPAND, 0);
	sizer_6->Add(button_4, 0, 0, 0);
	sizer_4->Add(sizer_6, 0, wxEXPAND, 0);
	sizer_3->Add(sizer_4, 0, wxEXPAND, 0);
	sizer_3->Add(20, 5, 0, wxEXPAND, 0);
	sizer_2->Add(sizer_3, 0, wxEXPAND, 0);
	sizer_2->Add(5, 20, 0, wxEXPAND, 0);
	panel_1->SetSizer(sizer_2);
	sizer_1->Add(panel_1, 1, wxEXPAND, 0);
	SetSizer(sizer_1);
	sizer_1->Fit(this);
	Layout();
	Centre();
	// end wxGlade
}


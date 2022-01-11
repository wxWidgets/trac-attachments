/////////////////////////////////////////////////////////////////////////////
// Name:        m_subscript.cpp
// Purpose:     wxHtml module for basic subscript and supscript handling
// Author:      Carsten Niehaus <cniehaus AT kde DOT org>
// Copyright:   (c) 2004 Carsten Niehaus
// Licence:     wxWindows Licence
/////////////////////////////////////////////////////////////////////////////


#ifdef __GNUG__
#pragma implementation
#endif

#include "wx/wxprec.h"

#include "wx/defs.h"
#if wxUSE_HTML && wxUSE_STREAMS

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WXPRECOMP
#endif

#include "wx/html/forcelnk.h"
#include "wx/html/m_templ.h"
#include "wx/html/htmlcell.h"

#include "wx/font.h"

FORCE_LINK_ME(m_subscript)

class wxSubscriptCell : public wxHtmlWordCell
{
	public:
		wxSubscriptCell( const wxString& word, wxDC& dc );
		virtual void Draw( wxDC& dc, int x, int y, int view_y1, int view_y2 );

};

wxSubscriptCell::wxSubscriptCell( const wxString& word, wxDC& dc ) : wxHtmlWordCell(word, dc)
{
}

void wxSubscriptCell::Draw( wxDC& dc, int x, int y, int WXUNUSED( view_y1 ), int WXUNUSED( view_y2 ) )
{
	wxFont font = dc.GetFont();
	int size = font.GetPointSize();
	font.SetPointSize( size-5 );
	dc.SetFont( font );

	dc.DrawText( m_Word, x + m_PosX, y + m_PosY+m_Height/2 );
	
	font.SetPointSize( size );
	dc.SetFont( font );
}


TAG_HANDLER_BEGIN(SUB, "SUB")

    TAG_HANDLER_PROC(tag)
	{
		ParseInner(tag);

		const wxString& src = *m_WParser->GetSource();
		wxString mark = src.Mid(tag.GetBeginPos(), tag.GetEndPos1()-tag.GetBeginPos());

		int oldsize = m_WParser->GetFontSize();
		m_WParser->GetContainer()->InsertCell(new wxSubscriptCell( mark, *( m_WParser->GetDC() ) ) );
	}

TAG_HANDLER_END(SUB)

//Now the code for superscript
class wxSupscriptCell : public wxHtmlWordCell
{
	public:
		wxSupscriptCell( const wxString& word, wxDC& dc );
		virtual void Draw( wxDC& dc, int x, int y, int view_y1, int view_y2 );

};

wxSupscriptCell::wxSupscriptCell( const wxString& word, wxDC& dc ) : wxHtmlWordCell(word, dc)
{
}


void wxSupscriptCell::Draw( wxDC& dc, int x, int y, int WXUNUSED( view_y1 ), int WXUNUSED( view_y2 ) )
{
	wxFont font = dc.GetFont();
	int size = font.GetPointSize();
	font.SetPointSize( size-5 );
	dc.SetFont( font );
	
	dc.DrawText( m_Word, x + m_PosX, y + m_PosY-m_Height/5 );
	
	font.SetPointSize( size );
	dc.SetFont( font );
}

TAG_HANDLER_BEGIN(SUP, "SUP")

    TAG_HANDLER_PROC(tag)
	{
		ParseInner(tag);

		const wxString& src = *m_WParser->GetSource();
		wxString mark = src.Mid(tag.GetBeginPos(), tag.GetEndPos1()-tag.GetBeginPos());

		m_WParser->GetContainer()->InsertCell(new wxSupscriptCell( mark, *( m_WParser->GetDC() ) ) );
	}

TAG_HANDLER_END(SUP)


TAGS_MODULE_BEGIN(sub)

    TAGS_MODULE_ADD(SUB)
    TAGS_MODULE_ADD(SUP)

TAGS_MODULE_END(sub)

#endif // wxUSE_HTML

 	  	 

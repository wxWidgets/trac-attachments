/////////////////////////////////////////////////////////////////////////////
// Name:        src/gtk/statusbar.cpp
// Purpose:
// Author:      Igor Korot
// Id:          
// Copyright:   (c) 1998 Robert Roebling, Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#if wxUSE_STATUSBAR

#ifndef WX_PRECOMP
    #include "wx/statusbr.h"
#endif

#include "wx/gtk/private.h"

wxStatusBar::wxStatusBar()
{
    m_statusbar = NULL;
    m_count = 0;
}

wxStatusBar::wxStatusBar(wxWindow *parent, wxWindowID id, long style, const wxString &name)
{
    Create(parent, id, style, name);
}

wxStatusBar::~wxStatusBar()
{
}

bool wxStatusBar::Create(wxWindow *parent, wxWindowID id, long style, const wxString &WXUNUSED(name))
{
    if (!PreCreation( parent, wxDefaultPosition, wxDefaultSize ) ||
        !CreateBase( parent, id, wxDefaultPosition, wxDefaultSize, style ))
    {
        wxFAIL_MSG( wxT("wxStatusBar creation failed") );
        return false;
    }

    m_statusbar = GTK_STATUSBAR(gtk_statusbar_new());
    m_uid.insert( 0, gtk_statusbar_get_context_id( m_statusbar, "context0" ) );

    if( style & wxSTB_SIZEGRIP )
         gtk_statusbar_set_has_resize_grip( m_statusbar, TRUE );
    else
         gtk_statusbar_set_has_resize_grip( m_statusbar, FALSE );

    m_widget = gtk_event_box_new();
    g_object_ref(m_widget);
    gtk_container_add(GTK_CONTAINER(m_widget),GTK_WIDGET(m_statusbar));
    gtk_widget_show(GTK_WIDGET(m_statusbar));
    m_parent->DoAddChild(this);
    SetFieldsCount(1);
    PostCreation();
    return true;
}

int wxStatusBar::GetFieldsCount() const
{
    return m_count;
}
/*
const wxStatusBarPane& wxStatusBar::GetField(int n) const
{
}

wxSize wxStatusBar::GetBorders() const
{
    return wxDefaultSize;
}

const wxArrayString& wxStatusBar::GetStatusStack(int n) const
{
}

int wxStatusBar::GetStatusWidth(int n) const
{
    return 0;
}

int wxStatusBar::GetStatusStyle(int n) const
{
    return 0;
}
*/
void wxStatusBar::PopStatusText(int field)
{
    if( field < 0 || (size_t) field > m_panes.GetCount() )
    {
         wxLogError( "Incorrect number of fields passed to PopStatusText" );
         return;
    }
    gtk_statusbar_pop( m_statusbar, m_uid[field] );
}

void wxStatusBar::PushStatusText(const wxString& string, int field)
{
    if( field < 0 || (size_t) field > m_panes.GetCount() )
    {
         wxLogError( "Incorrect number of fields passed to PopStatusText" );
         return;
    }
    gtk_statusbar_push( m_statusbar, m_uid[field], string );
}
/*
wxString wxStatusBar::GetStatusText(int i) const
{
    return "";
}
*/
void wxStatusBar::SetFieldsCount(int number, const int* widths)
{
    int i;
    wxASSERT_MSG( (number > 0) && (number < 255), "too many fields" );
    wxStatusBarBase::SetFieldsCount(number, widths);
    SetFieldsWidth();
    // all panes should have the same width
    if( widths == NULL )
    {
         gtk_box_set_homogeneous( GTK_BOX( m_statusbar ), TRUE );
    }
    // panes should have different sizes
    else
    {
         gtk_box_set_homogeneous( GTK_BOX( m_statusbar ), FALSE );
    }
    for( i = 0; i < number; i++ )
         gtk_box_pack_start( GTK_BOX( m_statusbar ), gtk_entry_new(), FALSE, FALSE, 0 );
    m_count = number;
}
/*
void wxStatusBar::SetStatusStyles(int n, const int* styles)
{
}

void wxStatusBar::SetStatusText(const wxString& text, int i)
{
}
*/
void wxStatusBar::SetStatusWidths(int n, const int* widths_field)
{
    GtkWidget *hbox;
    wxSize size = GetSize();
    if( m_panes.GetCount() != (size_t)n )
    {
         wxLogMessage( "Incorrect number of panes passed" );
         return;
    }
    for( int i = 0; i < n; i++ )
    {
    }
}

bool wxStatusBar::GetFieldRect(int i, wxRect& rect) const{    wxCHECK_MSG( (i >= 0) && ((size_t)i < m_panes.GetCount()), false,
                 "invalid statusbar field index" );

    wxRect r;
    return true;}
void wxStatusBar::SetMinHeight(int height)
{
}

int wxStatusBar::GetBorderX() const
{
    return 0;
}

int wxStatusBar::GetBorderY() const
{
    return 0;
}

void wxStatusBar::SetFieldsWidth()
{
    if( m_panes.IsEmpty() )
         return;
    wxArrayInt widthAbs = CalculateAbsWidths(GetClientSize().x);
}

#endif // wxUSE_STATBAR

/////////////////////////////////////////////////////////////////////////////
// Name:        wxDataViewDoubleSpinRenderer.cpp
// Purpose:     A double precision floating point version of 
//              wxDataViewSpinRenderer. Based on the original 
//              wxDataViewSpinRenderer by Robert Roebling.
// Author:      Hans de Ruiter
// Created:     2010.04.16
// RCS-ID:      $$
// Copyright:   (c) Hans de Ruiter
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "wxDataViewDoubleSpinRenderer.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/spinctrl.h"

// -------------------------------------
// wxDataViewDoubleSpinRenderer
// -------------------------------------

#define DEFAULT_INCREMENT 0.1

wxDataViewDoubleSpinRenderer::wxDataViewDoubleSpinRenderer( double min, double max, double increment, wxDataViewCellMode mode, int alignment) :
   wxDataViewCustomRenderer(wxT("double"), mode, alignment )
{
    m_min = min;
    m_max = max;
	this->increment = increment;
}

wxControl* wxDataViewDoubleSpinRenderer::CreateEditorCtrl( wxWindow *parent, wxRect labelRect, const wxVariant &value )
{
    double d = value;
    wxSize size = labelRect.GetSize();
#ifdef __WXMAC__
    size = wxSize( wxMax(70,labelRect.width ), -1 );
#endif
    wxString str;
    str.Printf( wxT("%lg"), (double) d );
    wxSpinCtrlDouble *sc = new wxSpinCtrlDouble( parent, wxID_ANY, str,
               labelRect.GetTopLeft(), size, wxSP_ARROW_KEYS|wxTE_PROCESS_ENTER, m_min, m_max, d, DEFAULT_INCREMENT );
#ifdef __WXMAC__
    size = sc->GetSize();
    wxPoint pt = sc->GetPosition();
    sc->SetSize( pt.x - 4, pt.y - 4, size.x, size.y );
#endif

    return sc;
}

bool wxDataViewDoubleSpinRenderer::GetValueFromEditorCtrl( wxControl* editor, wxVariant &value )
{
    wxSpinCtrlDouble *sc = (wxSpinCtrlDouble*) editor;
    double d = sc->GetValue();
    value = d;
    return true;
}

bool wxDataViewDoubleSpinRenderer::Render( wxRect rect, wxDC *dc, int state )
{
    wxString str;
    str.Printf(wxT("%lg"), (double) m_data );
    RenderText( str, 0, rect, dc, state );
    return true;
}

wxSize wxDataViewDoubleSpinRenderer::GetSize() const
{
    return wxSize(80,16);
}

bool wxDataViewDoubleSpinRenderer::SetValue( const wxVariant &value )
{
    m_data = value.GetDouble();
    return true;
}

bool wxDataViewDoubleSpinRenderer::GetValue( wxVariant &value ) const
{
    value = m_data;
    return true;
}

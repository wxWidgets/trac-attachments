/////////////////////////////////////////////////////////////////////////////
// JFZ 1/31/03	Attempt to fix bias that first item in the box sizer gets
//		due to integer rounding.  This gets magnified as the 
//		item's stretch factor increases.
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation "sizer.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "wx/sizer.h"
#include "sizer.hpp"
#include "wx/log.h"

//---------------------------------------------------------------------------

IMPLEMENT_ABSTRACT_CLASS(wxFairBoxSizer, wxBoxSizer);


//---------------------------------------------------------------------------
// wxBoxSizer
//---------------------------------------------------------------------------

wxFairBoxSizer::wxFairBoxSizer( int orient )
	: wxBoxSizer(orient)
{
	wxLogDebug("Creating fair box sizer");
}

void wxFairBoxSizer::RecalcSizes()
{
//    wxLogDebug("wxFairBoxSizer::RecalcSizes()");

    if (m_children.GetCount() == 0)
        return;

    double delta = 0;
    double extra = 0;
    double extraDelta = 0;
    if (m_stretchable)
    {
        if (m_orient == wxHORIZONTAL)
        {
            delta = (m_size.x - m_fixedWidth) / (double)m_stretchable;
            extra = delta - (int)delta;
        }
        else
        {
//	    wxLogDebug("y = %d, h = %d, stretch = %d",
//            		m_size.y,m_fixedHeight,m_stretchable);
            delta = (m_size.y - m_fixedHeight) / (double)m_stretchable;
            extra = delta - (int)delta;
        }
//	wxLogDebug("delta = %f, extra = %f",delta,extra);
    }

    wxPoint pt( m_position );

    wxNode *node = m_children.GetFirst();
    while (node)
    {
        wxSizerItem *item = (wxSizerItem*) node->Data();

        int weight = 1;
        if (item->GetOption())
            weight = item->GetOption();

        wxSize size( item->CalcMin() );

        if (m_orient == wxVERTICAL)
        {
            wxCoord height = size.y;
            if (item->GetOption())
            {
                height = (int)((delta * weight) + extra);
                extra = 0; // only the first item will get the remainder as extra size
            }

            wxPoint child_pos( pt );
            wxSize  child_size( wxSize( size.x, height) );

            if (item->GetFlag() & (wxEXPAND | wxSHAPED))
                child_size.x = m_size.x;
            else if (item->GetFlag() & wxALIGN_RIGHT)
                child_pos.x += m_size.x - size.x;
            else if (item->GetFlag() & (wxCENTER | wxALIGN_CENTER_HORIZONTAL))
            // XXX wxCENTER is added for backward compatibility;
            //     wxALIGN_CENTER should be used in new code
                child_pos.x += (m_size.x - size.x) / 2;

            item->SetDimension( child_pos, child_size );

            pt.y += height;
        }
        else
        {
            wxCoord width = size.x;
            if (item->GetOption())
            {
                width = (int)((delta * weight) + extra);
                extra = 0; // only the first item will get the remainder as extra size
            }

            wxPoint child_pos( pt );
            wxSize  child_size( wxSize(width, size.y) );

            if (item->GetFlag() & (wxEXPAND | wxSHAPED))
                child_size.y = m_size.y;
            else if (item->GetFlag() & wxALIGN_BOTTOM)
                child_pos.y += m_size.y - size.y;
            else if (item->GetFlag() & (wxCENTER | wxALIGN_CENTER_VERTICAL))
            // XXX wxCENTER is added for backward compatibility;
            //     wxALIGN_CENTER should be used in new code
                child_pos.y += (m_size.y - size.y) / 2;

            item->SetDimension( child_pos, child_size );

            pt.x += width;
        }

        node = node->Next();
    }
}



 	  	 

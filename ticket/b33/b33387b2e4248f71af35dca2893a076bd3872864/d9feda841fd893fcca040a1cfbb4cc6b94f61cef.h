/////////////////////////////////////////////////////////////////////////////
// Name:        wx/wrapsizer.h
// Purpose:     provide wrapping sizer for layout (wxWrapSizer)
// Author:      Arne Steinarson
// Modified by: 
// Created:
// RCS-ID:      $Id$
// Copyright:   (c) Arne Steinarson
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef __WXWRAPSIZER_H__
#define __WXWRAPSIZER_H__


#include "wx/sizer.h" 

//---------------------------------------------------------------------------
// wxWrapSizer - A box sizer that can wrap items on several lines when 
// sum of widths exceed available line width.
//---------------------------------------------------------------------------

enum {
    wxEXPAND_LAST_ON_LINE    = 1,    // Causes last item on a line to expand
    wxREMOVE_LEADING_SPACES  = 2     // Will remove space items when first on a line
};

class WXDLLEXPORT wxWrapSizer : public wxBoxSizer
{
public:
    wxWrapSizer( int orient = wxHORIZONTAL, 
                 int flags  = wxEXPAND_LAST_ON_LINE|wxREMOVE_LEADING_SPACES );
    virtual ~wxWrapSizer();

    virtual void RecalcSizes();
    virtual wxSize CalcMin();
    
protected:
    // Called by parent sizer once the first size component has been determined
    virtual bool InformFirstDirection( int direction, int size, int availableOtherDir );
    
    // Helper to determine if an item to be treated as space (may be discared when 
    // first or last on a line) or as solid (never discarded). By default spacer 
    // items are treated as space. A derived class may override for a different 
    // behaviour.
    virtual bool IsSpaceItem( wxSizerItem *psi );
    
    // Various ways of calculating min size for a wrap sizer - 
    // NOTE: When containing 2+ items, a unique min size is _not_ possible 
    // to determine. It will depend on the number of rows / columns in its 
    // current wrap layout.
    void CalcMinFromMinor( int totMinor );
    void CalcMinFromMajor( int totMajor );
    void CalcMinUsingCurrentLayout( );
    
    // Helper for extending the last item to fill a line
    void AdjustPropLastItem(wxSizer *psz, wxSizerItem *itemLast);    
    
protected:    
    int   m_dirInform;         // Direction for size information 
    int   m_availableOtherDir; // How much more available in opposite direction
    int   m_firstSizeInform;   // Size in primary direction last time
    bool  m_lastInformUsed;    // Indicates whether value from InformFirst... has been used yet
    
    int   m_nrLines;           // Number of lines
    int   m_minSumMinor;       // Min size in minor direction 
    int   m_maxSizeMajor;      // Min size in major direction
    int   m_minItemMajor;      // Smallest item in major dir 
    
    int        m_flags;        // Internal flags for sizer
    wxBoxSizer m_rows;         // Rows/columns of items
    
private:
    DECLARE_DYNAMIC_CLASS(wxWrapSizer);
    DECLARE_NO_COPY_CLASS(wxWrapSizer);
};

#endif // __WXWRAPSIZER_H__

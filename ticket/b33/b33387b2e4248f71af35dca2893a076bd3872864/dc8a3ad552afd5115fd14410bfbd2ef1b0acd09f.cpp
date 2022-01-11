/////////////////////////////////////////////////////////////////////////////
// Name:        src/common/wrapsizer.cpp
// Purpose:     provides wxWrapSizer class for layout
// Author:      Arne Steinarson
// Modified by: 
// Created:
// RCS-ID:      $Id$
// Copyright:   (c) Arne Steinarson
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "wx/wrapsizer.h"
#include "wx/vector.h"

//---------------------------------------------------------------------------

IMPLEMENT_DYNAMIC_CLASS(wxWrapSizer, wxBoxSizer);

//---------------------------------------------------------------------------
// wxWrapSizer
//---------------------------------------------------------------------------

#define wxDEFAULT_PROPORTION_LAST    1000000

// User data to hold old proportion for last item on line (which might be extended)
struct wxPropHolder : public wxObject
{
    wxPropHolder( ) : m_item(NULL), m_propOld(0)  
    { 
    }
    
    void Init( wxSizerItem *item, int propOld ) 
    { 
        m_item=item; 
        m_propOld=propOld; 
    }
    
    wxSizerItem *m_item;
    int          m_propOld;
};


wxWrapSizer::wxWrapSizer( int orient, int flags )
    : wxBoxSizer(orient),
      m_dirInform(0), 
      m_availableOtherDir(0), 
      m_firstSizeInform(-1), 
      m_lastInformUsed(true),
      m_nrLines(0),
      m_minSumMinor(0), 
      m_maxSizeMajor(0),
      m_minItemMajor(INT_MAX),
      m_flags(flags),
      m_rows(orient^wxBOTH)
{
}

wxWrapSizer::~wxWrapSizer()
{
    // Have to clear grand child items so that they're not deleted twice
    for( int ix=m_rows.GetChildren().GetCount()-1; ix>=0; ix-- )
    {
        wxSizer *psz = m_rows.GetItem((size_t)ix)->GetSizer();
        wxSizerItemList &sl = psz->GetChildren();
        while( sl.GetLast() )
            sl.Erase( sl.GetLast() );
    }
}


bool wxWrapSizer::InformFirstDirection( int direction, int size, int availableOtherDir )
{
    if ( !direction )
        return false;
    
    // Store the values for later use
    
    // First determined size component
    m_firstSizeInform = size;
    
    // Available space in the opposite direction
    m_availableOtherDir = availableOtherDir + 
                         (direction==wxHORIZONTAL ? m_minSize.y : m_minSize.x);
    
    // Set flags for new information and store direction
    m_dirInform = direction;
    m_lastInformUsed = false;
    
    return true;
}


// This will cause an item to use all remaining space on a line by setting 
// a very high proportion value for it. 
void wxWrapSizer::AdjustPropLastItem( wxSizer *psz, wxSizerItem *itemLast )
{
    if ( !itemLast ) return;
    
    wxSizerItem *psi = m_rows.GetItem(psz);
    wxASSERT(psi);
    
    wxPropHolder *pph = (wxPropHolder*)psi->GetUserData();
    if ( !pph )
    {
        pph=new wxPropHolder;
        psi->SetUserData( pph );
    }
        
    pph->Init( itemLast, itemLast->GetProportion() );
    itemLast->SetProportion( wxDEFAULT_PROPORTION_LAST );
}


// A test to decide if an item represents empty space or not. We do this to avoid having 
// space-only items first or last on a wrapped line (left alignment).
bool wxWrapSizer::IsSpaceItem( wxSizerItem *psi )
{
    // A derived wxWrapSizer class can do this differently 
    return psi->IsSpacer();
}

void wxWrapSizer::RecalcSizes()
{
    wxASSERT( m_orient&wxBOTH );
    if (m_children.GetCount() == 0)
        return;

    // What we do here is to put our items into child box sizers,
    // as many of them as we have lines.

    // Empty all items in all rows in child sizers. 
    // We have to access the underlying list directly, since we must not
    // destroy the contained wxSizerItems.
    //
    // This trick is safe (but does depend on the list implementation of
    // wxSizer), because:
    //
    // 1 - The child sizer is not exposed outside of this file
    // 2 - We only keep items in child sizers for the purpose of doing
    //     the layout (recalcSizes). Each child sizer is cleared on 
    //     on each new call here.
    // 3 - In ~wxWrapSizer the child wxSizer lists must be emptied
    //     before calling ~wxSizer.
    // 
    for (int ix=m_rows.GetChildren().GetCount()-1; ix>=0; ix--)
    {
        wxSizerItem *psi = m_rows.GetItem( (size_t)ix );

        // Restore proportion for last item on line (if item has not been deleted)
        // NOTE: This is safe, even if wxPropHolder points to a deleted item. 
        // We only compare pointer values.
        wxPropHolder *pph = (wxPropHolder*)psi->GetUserData();
        if ( pph && GetChildren().Find( pph->m_item ) )
            pph->m_item->SetProportion( pph->m_propOld );

        // And empty child sizers, accessing the list (to avoid deleting 
        // wxSizerItems)
        wxSizer *psz = psi->GetSizer();
        wxASSERT( psz );
        wxSizerItemList &sl = psz->GetChildren();
        while (sl.GetLast())
            sl.Erase( sl.GetLast() );
    }

    // Setup for layout on multiple lines / columns
    int lineSumMajor = 0;
    int lineMaxMinor = 0;
    int majorSize = SizeInMajorDir(m_size);
    m_minSumMinor = 0;
    m_minItemMajor = INT_MAX;
    m_maxSizeMajor = 0;

    // Make sure we have at least one child sizer
    if (!m_rows.GetChildren().GetCount())
        m_rows.Add( new wxBoxSizer(GetOrientation()), 1, wxEXPAND );
    m_nrLines = 1;

    // The sizer where to insert items in
    wxSizer *psz = m_rows.GetItem( (size_t)0 )->GetSizer();
    wxASSERT( psz );


    // Now put our child items into child sizers instead. 
    // See the note above. 
    wxSizerItem *item = NULL, 
                *itemLast=NULL,    // Usually don't want space items first or last at a line
                *itemSpace = NULL;
                
    for( wxSizerItemList::iterator node = m_children.begin();
         node!=m_children.end();
         node++ )
    {
        item = *node;
        if ( item->IsShown() )
        {
            wxSize minSz = item->GetMinSize();
            int minSzMajor = SizeInMajorDir(minSz);
            int minSzMinor = SizeInMinorDir(minSz);
            if ( minSzMajor>0 && minSzMajor<m_minItemMajor )
                m_minItemMajor = minSzMajor;

            // More space on this line?
            if ( !itemLast || lineSumMajor+minSzMajor<=majorSize )    
            {
                // If so, extend line 
                lineSumMajor += minSzMajor;
                if ( lineMaxMinor<minSzMinor )
                    lineMaxMinor = minSzMinor;
            }
            else
            {
                // No more space on this line, make a new line
                if ( m_maxSizeMajor<lineSumMajor )
                    m_maxSizeMajor = lineSumMajor;
                lineSumMajor = minSzMajor;
                m_minSumMinor += lineMaxMinor;
                lineMaxMinor = minSzMinor;
                
                // Get a new empty sizer to insert into
                if ( (int)m_rows.GetChildren().GetCount()<=m_nrLines )
                    m_rows.Add( new wxBoxSizer(GetOrientation()), 1, wxEXPAND );

                // If we have wxEXPAND_LAST_ON_LINE mode, then do so now.
                // NOTE: We must store old proportion value to be able to restore it later.
                if ( m_flags&wxEXPAND_LAST_ON_LINE )
                    AdjustPropLastItem( psz, itemLast );
                itemLast = itemSpace = NULL;

                // The sizer where to insert items in
                psz = m_rows.GetItem( m_nrLines++ )->GetSizer();
            }
            
            // Only remove first/last spaces if that flag is set
            bool isSpace = m_flags&wxREMOVE_LEADING_SPACES ? 
                           IsSpaceItem(item) : false;
                           
            // When ading space items, that decision is postponed one iteration
            // so that we know if it's really not last on a line. The variables:
            // 'itemLast' and 'itemSpace' helps with keeping track of this.
            if ( !isSpace )
            {
                if ( itemLast && itemSpace )
                    psz->Add( itemSpace );    // Add previous space
                itemLast = item;
                psz->Add( item );
                itemSpace = NULL;
            }
            else 
            {
                // Remember space only if we have a first item
                if ( itemLast )
                    itemSpace = item;
            }
            
            // If item is a window, it now has a pointer to the child sizer,
            // which is wrong. Set it to point to us.
            if ( item->GetWindow() )
                item->GetWindow()->SetContainingSizer( this );
        }
    }

    // Total min size in minor direction. 
    m_minSumMinor += lineMaxMinor;
    if ( m_maxSizeMajor<lineSumMajor )
        m_maxSizeMajor = lineSumMajor;
    
    // If we have extend-last-on-each-line mode, then do so now
    if ( m_flags&wxEXPAND_LAST_ON_LINE )
        AdjustPropLastItem( psz, itemLast );

    // If we have more sizers than lines, remove them now
    while ( (int)m_rows.GetChildren().GetCount()>m_nrLines )
        m_rows.Remove( m_nrLines );

    // Now do layout on row sizer
    m_rows.SetDimension( m_position.x, m_position.y, m_size.x, m_size.y );
}


wxSize wxWrapSizer::CalcMin()
{
    // No items?
    if (m_children.GetCount() == 0)
        return wxSize();

    // We come here to calc min size in two different situations:
    //
    // 1 - Immediately after InformFirstDirection, then we find a min size that 
    //     uses one dimension maximally and the other direction minimally.
    //
    // 2 - Ordinary case, get a sensible min size value using the current line layout,
    //     trying to maintain the possibility to re-arrange lines by sizing.
    //
    // 3 - Before the very first layout has been done. We simply return the 
    //     size of single the largest item, to avoid making any assumption 
    //     on what layout will be used. 
    
    // NOTE: In 2 it is important that: When the current size reaches the minsize 
    // (in primary direction), that we can present a smaller minsize (in primary 
    // direction), since otherwise we would not be able to resize the contents by 
    // adding more wrap lines). 

    // Keep track of boundary so we don't overflow
    wxSize szBoundary;    
    if ( m_firstSizeInform>0 )
    {
        if ( m_dirInform==m_orient )
            szBoundary =  SizeFromMajorMinor( m_firstSizeInform, m_availableOtherDir );
        else 
            szBoundary =  SizeFromMajorMinor( m_availableOtherDir, m_firstSizeInform );
    }
                            
    // Case 1 above
    if ( m_lastInformUsed==false && m_firstSizeInform>0 )
    {
        // There are two different algorithms for finding a useful min size for 
        // a wrap sizer, depending on whether the first reported size component 
        // is the opposite as our own orientation (the simpler case) or the same
        // (more complex algo). 
        wxSize szMinPrev = m_minSize;
        if ( m_dirInform==m_orient )
            CalcMinFromMajor( m_firstSizeInform );
        else
            CalcMinFromMinor( m_firstSizeInform );

        // If overflowing given boundary, go back to previous min size
        if ( m_minSize.x>szBoundary.x || m_minSize.y>szBoundary.y )
            m_minSize = szMinPrev;
    }
    else 
    {
        // Case 2 above
        if ( m_minSumMinor>0 )
        {
            // Min size based on current line layout. It is important to provide a 
            // smaller size when possible to allow for resizing with the help of 
            // re-arranging the lines.
            wxSize sizeMin = SizeFromMajorMinor( m_maxSizeMajor, m_minSumMinor );
            if ( m_minSumMinor<SizeInMinorDir(m_size) && 
                 m_maxSizeMajor<SizeInMajorDir(m_size) )
            {
                // Current minsize allows for resizing
                m_minSize = sizeMin; 
            }
            else 
            {
                // Current minsize does _not_ allow for resizing in primary direction
                bool done = false;
                if ( m_minItemMajor!=INT_MAX && m_maxSizeMajor>0 )
                {
                    // We try to present a lower min value by removing an item 
                    // in the major direction (and preserving current minor min size). 
                    CalcMinFromMajor( m_maxSizeMajor-m_minItemMajor );
                    if ( m_minSize.x<=szBoundary.x && m_minSize.y<=szBoundary.y ) 
                    {
                        // It went fine
                        SizeInMinorDir(m_minSize) = SizeInMinorDir(sizeMin);
                        done = true;
                    }
                }
                if ( !done )
                {
                    // If failed finding a little smaller area, go back to what we had
                    m_minSize = sizeMin; 
                }
            }
        }
        else 
        {
            // Find max item size in each direction
            wxSize sz;
            int maxMinor = 0;    // Line height 
            int maxMajor = 0;    // Widest item 
            for ( wxSizerItemList::iterator node = m_children.begin();
                  node != m_children.end(); 
                  node++ )
            {
                wxSizerItem *item = *node;
                if ( item->IsShown() )
                {
                    sz = item->CalcMin();
                    if ( SizeInMinorDir(sz)>maxMinor )
                        maxMinor = SizeInMinorDir(sz);
                    if ( SizeInMajorDir(sz)>maxMinor )
                        maxMajor = SizeInMajorDir(sz);
                }
            }
            m_minSize = SizeFromMajorMinor( maxMajor, maxMinor );
        }
    }
    
    // We have used information from InformFirst...
    m_lastInformUsed = true;
    return m_minSize;  
}


void wxWrapSizer::CalcMinFromMajor( int totMajor )
{
    // Algorithm for calculating min size: (assuming horizontal orientation)
    // This is the simpler case (known major size)
    // X: Given, totMajor
    // Y: Based on X, calculate how many lines needed
    
    // NOTE: We use 'width' and 'height' in the comments below. That assumes 
    // wxHORIZONTAL orientation, and would be the opposite for a wrap sizer with 
    // wxVERTICAL orientation. 

    int maxSumMajor = 0;
    int minorSum = 0;
    int lineMaxMinor = 0;
    int lineSumMajor = 0;
    m_nrLines = 0;

    // precalc item minsizes and fit on lines (preliminary)
    for ( wxSizerItemList::iterator node = m_children.begin();
          node != m_children.end(); 
          node++ )
    {
        wxSizerItem *item = *node;
        if ( item->IsShown() )
        {
            wxSize minSz = item->CalcMin();
            int szMajor = SizeInMajorDir(minSz);
            int szMinor = SizeInMinorDir(minSz);
            
            // More space on this line?
            if ( totMajor<0 || !lineSumMajor || 
                 lineSumMajor+szMajor<=totMajor )    
            {
                lineSumMajor += szMajor;
                if ( szMinor>lineMaxMinor )
                     lineMaxMinor = szMinor;
            }
            else
            {
                // Add height of highest item on last line
                minorSum += lineMaxMinor;    
                m_nrLines++;
                
                // Keep track of the widest line
                if ( lineSumMajor>maxSumMajor )
                     maxSumMajor = lineSumMajor;
                     
                lineMaxMinor = szMinor;
                lineSumMajor = szMajor;
            }
        }
    }
    
    // Add height of highest item on last line
    minorSum += lineMaxMinor;            
    if ( lineSumMajor>maxSumMajor )
        maxSumMajor = lineSumMajor;

    // Have valid min size
    m_minSize = SizeFromMajorMinor( maxSumMajor, minorSum ); 
}


// Helper struct during min size calculation below
struct wxWrapLine 
{
    wxWrapLine() : m_first(NULL), m_width(0) { }
    wxSizerItem *m_first;        // First item on this line
    int          m_width;        // Width of line
};

void wxWrapSizer::CalcMinFromMinor( int totMinor )
{
    // Algorithm for calculating min size.
    // This is the more complex case (known minor size)
    
    // First step, find total sum of all items in primary direction 
    // and max item size in secondary direction, that gives initial 
    // estimate of the minimum number of lines.
    
    int totMajor = 0;    // Sum of widths 
    int maxMinor = 0;    // Line height 
    int maxMajor = 0;    // Widest item 
    int itemCount = 0;
    wxSize sz;
    for ( wxSizerItemList::iterator node = m_children.begin();
          node != m_children.end(); 
          node++ )
    {
        wxSizerItem *item = *node;
        if ( item->IsShown() )
        {
            sz = item->CalcMin();
            totMajor += SizeInMajorDir(sz);
            if ( SizeInMinorDir(sz)>maxMinor )
                maxMinor = SizeInMinorDir(sz);
            if ( SizeInMajorDir(sz)>maxMinor )
                maxMajor = SizeInMajorDir(sz);
            itemCount++;
        }
    }
    
    // The trivial case 
    if ( !itemCount || totMajor==0 || maxMinor==0 )
    {
        m_minSize = wxSize(0,0);
        return;
    }
        
    // First attempt, use lines of average size.
    int nrLines = totMinor / maxMinor; // Rounding down is right here 
    if ( nrLines<=1 )
    {
        // Another simple case, everything fits on one line 
        m_minSize = SizeFromMajorMinor( totMajor, maxMinor );
        return;
    }

    // First estimate of line width.
    int lineSize = totMajor / nrLines;
    if ( lineSize<maxMajor )     
        // Must be at least as wide as the widest element 
        lineSize = maxMajor;

    // The algorithm is as follows (horz case):
    // 1  - Vertical (minor) size is known.
    // 2  - We have a reasonable estimated width from above
    // 3  - Loop:
    // 3a   - Do layout with suggested width
    // 3b   - See how much we spill over in minor dir (the 'tail')
    // 3c   - If no spill (tail), we're done
    // 3d   - Otherwise increase width by known smallest item 
    //        and redo loop
        
    // First algo step: put items on lines of known max width 
    wxVector<wxWrapLine*> lines;
    
    int sumMinor;       // Sum of all minor sizes (height of all lines)
    
    // While we still have items 'spilling over' extend the tested line width
    while ( true )
    {
        wxWrapLine *line = new wxWrapLine;
        lines.push_back( line );
        
        int tailSize = 0;   // Width of what exceeds nrLines
        maxMinor = 0;
        sumMinor = 0;
        
        for( wxSizerItemList::iterator node = m_children.begin();
             node!=m_children.end();
             node++ )
        {
            wxSizerItem *item = *node;
            if ( item->IsShown() )
            {
                sz = item->GetMinSize();
                
                // Goto new line?
                if ( line->m_width+SizeInMajorDir(sz)>lineSize )
                {
                    line = new wxWrapLine;
                    lines.push_back(line);
                    sumMinor += maxMinor;
                    maxMinor = 0;
                }
                
                // Add width of item
                line->m_width += SizeInMajorDir(sz);
                if ( line->m_width && !line->m_first ) 
                    line->m_first = item;
                    
                // Keep track of height
                if ( SizeInMinorDir(sz)>maxMinor )
                    maxMinor = SizeInMinorDir(sz);
                
                // Are we on the 'tail' part?
                if ( sumMinor+maxMinor>totMinor )
                {
                    // Keep track of widest tail item 
                    // It's the one that needs to be fitted on previous lines.
                    if ( SizeInMajorDir(sz)>tailSize )
                        tailSize = SizeInMajorDir(sz);
                }
            }
        }
        
        // If we have tail size 
        if ( tailSize )
        {
            // Now look how much we need to extend our size in major direction.
            // We know we must have at least one more line than current 'nrLines'
            // (otherwise no tail size). 
            
            int bestExtSize = 0; // Minimum extension width for current tailSize 
            for( int ix=0; ix<nrLines; ix++ )
            {
                // Take what is not used on this line, see how much extension we get 
                // by adding first item on next line.

                // Left over at end of this line                 
                int leftOverSize = lineSize - lines[ix]->m_width;   
                // How much line would be extended by pulling in first item on next line
                int extSize = GetSizeInMajorDir( lines[ix+1]->m_first->GetMinSize() ) 
                              - leftOverSize;
                              
                // Use this extension width?
                if ( (extSize>=tailSize && 
                      (extSize<bestExtSize || bestExtSize<tailSize)) || 
                     (extSize>bestExtSize && bestExtSize<tailSize) )
                    // Yes.
                    bestExtSize = extSize;
            }
            
            // Have an extension size, ready to redo line layout 
            lineSize += bestExtSize;
        }
        
        // Clear helper items
        for ( wxVector<wxWrapLine*>::iterator it=lines.begin(); 
              it<lines.end(); 
              ++it )
        {
            delete *it;
        }
        lines.clear();
        
        // No spill over? Then we're done.
        if ( !tailSize ) 
            break;
    }
    
    // Now have min size in the opposite direction 
    m_minSize = SizeFromMajorMinor(lineSize,sumMinor);
}

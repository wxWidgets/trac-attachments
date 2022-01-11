/////////////////////////////////////////////////////////////////////////////
// Name:        wxDataViewDoubleSpinRenderer.h
// Purpose:     A double precision floating point version of 
//              wxDataViewSpinRenderer. Based on the original 
//              wxDataViewSpinRenderer by Robert Roebling.
// Author:      Hans de Ruiter
// Created:     2010.04.16
// RCS-ID:      $$
// Copyright:   (c) Hans de Ruiter
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef __WXDATAVIEWDOUBLESPINRENDERER_H__
#define __WXDATAVIEWDOUBLESPINRENDERER_H__

#include "wx/dataview.h"

// -------------------------------------
// wxDataViewSpinDoubleRenderer
// -------------------------------------

class WXDLLIMPEXP_ADV wxDataViewDoubleSpinRenderer: public wxDataViewCustomRenderer
{
public:
	/** Creates a new wxDataViewDoubleSpinRenderer.
	 *
	 * @param min the minimum value that the spin control can take
	 * @param mac the maximum value that the spin control can take
	 * @param increment the increment step for each click of the
	 * @param mode the data view mode (see wxDataViewCustomRenderer class for details
	 * @param alignment the alignment of the data
	 */
    wxDataViewDoubleSpinRenderer( double min, double max, double increment = 0.1,
                            wxDataViewCellMode mode = wxDATAVIEW_CELL_EDITABLE,
                            int alignment = wxDVR_DEFAULT_ALIGNMENT );

    virtual bool HasEditorCtrl() const { return true; }
    virtual wxControl* CreateEditorCtrl( wxWindow *parent, wxRect labelRect, const wxVariant &value );
    virtual bool GetValueFromEditorCtrl( wxControl* editor, wxVariant &value );
    virtual bool Render( wxRect rect, wxDC *dc, int state );
    virtual wxSize GetSize() const;
    virtual bool SetValue( const wxVariant &value );
    virtual bool GetValue( wxVariant &value ) const;

private:
    double    m_data;
    double    m_min,m_max;
	double    increment;
};

#endif

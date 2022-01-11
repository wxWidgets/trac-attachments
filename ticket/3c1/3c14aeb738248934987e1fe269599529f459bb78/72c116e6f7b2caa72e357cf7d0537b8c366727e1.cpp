/////////////////////////////////////////////////////////////////////////////
// Name:        wrapsizer.cpp
// Purpose:     wxWidgets sample demonstrating wxWrapSizer use (and wxSHAPED+wxEXPAND)
// Author:      Arne Steinarson
// Modified by: 
// Created:     21.01.2008
// RCS-ID:      
// Copyright:   (c) Arne Steinarson
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/wxprec.h>
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


#include "wx/log.h"
#include "wx/artprov.h"

#include "wx/wrapsizer.h"

class WrapDialog: public wxDialog 
{
public:

    wxToolBar *MakeToolBar( )
    {
        wxBitmap bm1, bm2, bm3, bm4;
        bm1 = wxArtProvider::GetBitmap( wxART_PRINT, wxART_TOOLBAR, wxSize(16,16) );
        bm2 = wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_TOOLBAR, wxSize(16,16));
        bm3 = wxArtProvider::GetBitmap( wxART_GO_DIR_UP, wxART_TOOLBAR, wxSize(16,16) );
        bm4 = wxArtProvider::GetBitmap( wxART_EXECUTABLE_FILE, wxART_TOOLBAR, wxSize(16,16) );
        bool have_bms = bm1.IsOk() && bm2.IsOk() && bm3.IsOk() && bm4.IsOk();

        wxToolBar *ptb = new wxToolBar( this, -1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxTB_FLAT|wxTB_NODIVIDER | (have_bms?0:wxTB_TEXT|wxTB_NOICONS) );
        ptb->AddTool( 1000, _T("Tool1"), bm1, wxNullBitmap, wxITEM_NORMAL, _T("Tip 1") );
        ptb->AddSeparator( );
        ptb->AddTool( 1001, _T("Tool2"), bm2, wxNullBitmap, wxITEM_NORMAL, _T("Another tip") );
        ptb->AddSeparator( );
        ptb->AddTool( 1002, _T("Tool3"), bm3, wxNullBitmap, wxITEM_NORMAL, _T("Not implemented") );
        ptb->AddTool( 1003, _T("Tool4"), bm4, wxNullBitmap, wxITEM_NORMAL, _T("Neither this one...") );
        
        ptb->Realize( );
        return ptb;
    }

    WrapDialog( wxWindow *prnt, int id, const wxChar *title, wxPoint pos, wxSize size ) :
        wxDialog(prnt,id,title,pos,size,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER) 
    { 
        // Root sizer, vertical
        m_psz_root = new wxBoxSizer(wxVERTICAL);
        
        // Some toolbars in a wrap sizer
        wxSizer *ps_top = new wxWrapSizer( wxHORIZONTAL );
        ps_top->Add( MakeToolBar() );
        ps_top->Add( 20,1 );
        ps_top->Add( MakeToolBar() );
        ps_top->Add( 20,1 );
        ps_top->Add( MakeToolBar() );
        m_psz_root->Add( ps_top, 0, wxEXPAND | wxALL, 5 );
        
        // A number of checkboxes inside a wrap sizer 
        wxSizer *ps_mid = new wxStaticBoxSizer( wxVERTICAL, this, _T("With check-boxes") );
        wxSizer *ps_mid_wrap = new wxWrapSizer(wxHORIZONTAL);
        ps_mid->Add( ps_mid_wrap, 100, wxEXPAND );
        for( int ix=0; ix<6; ix++ )
            ps_mid_wrap->Add( new wxCheckBox(this,wxID_ANY,wxString::Format(_T("Option %d"),ix+1)), 0, wxALIGN_CENTRE|wxALIGN_CENTER_VERTICAL, 5 );
        m_psz_root->Add( ps_mid, 100, wxEXPAND | wxALL, 5 );

        // A shaped item inside a box sizer
        wxSizer *ps_bottom = new wxStaticBoxSizer( wxVERTICAL, this, _T("With wxSHAPED item") );
        wxSizer *ps_bottom_box = new wxBoxSizer(wxHORIZONTAL);
        ps_bottom->Add( ps_bottom_box, 100, wxEXPAND );
        ps_bottom_box->Add( new wxListBox(this,wxID_ANY,wxPoint(0,0),wxSize(70,70)), 0, wxEXPAND|wxSHAPED );
        ps_bottom_box->Add( 10,10 );
        ps_bottom_box->Add( new wxCheckBox(this,wxID_ANY,_T("A much longer option...")), 100, 0, 5 );
        //ps_root->Add( ps_bottom_box, 100, wxEXPAND | wxALL, 5 );
        m_psz_root->Add( ps_bottom, 100, wxEXPAND | wxALL, 5 );

        // OK Button 
        m_psz_root->Add( new wxButton(this,wxID_OK,_T("OK"),wxDefaultPosition,wxSize(100,30)),
                      0, wxALIGN_CENTER, 20 );
        m_psz_root->Add( 20,20 );
        
        DoLayoutAndMinSize( size );
    }

    ~WrapDialog( ){ delete m_psz_root; }
    
protected:
    void DoLayoutAndMinSize( const wxSize& sz )
    {
        // Split size into non-client and client size 
        wxSize sz_nc = GetNonClientSize( );
        wxSize sz_cl = sz - sz_nc;

        // It's important to redo the layout _before_ querying for a new min size. 
        // The min size returned will be slightly different when a new line 
        // of items are just about to be added (and items wrapped onto that line).
        m_psz_root->SetDimension( 0,0, sz_cl.x, sz_cl.y );
        
        // Calculate min size of window with this geometry.
        // NOTE: With wrap sizers, min size will be different depending on 
        // how the window is currently laid out.
        wxSize sz_min = m_psz_root->CalcMin();
        SetMinSize( sz_min + sz_nc );
    }

    void OnSize( wxSizeEvent& e )
    {
        printf( "OnSize: (%d,%d)\n", e.GetSize().x, e.GetSize().y );

        // Redo the layout and update window min size
        DoLayoutAndMinSize( e.GetSize() );

        // Must skip event for thinghs to work as usual
        e.Skip();
    }

    wxSize GetNonClientSize( )    
    { 
        return GetSize()-GetClientSize(); 
    }

private:
    wxSizer *m_psz_root;

    DECLARE_EVENT_TABLE();
};


BEGIN_EVENT_TABLE(WrapDialog, wxDialog)
    EVT_SIZE(WrapDialog::OnSize)
END_EVENT_TABLE()


class WrapTestApp : public wxApp 
{
public:
    WrapTestApp() { }

    virtual bool OnInit() 
    {
        WrapDialog dlg(NULL,wxID_ANY,_T("Wrap Sizer Test Dialog"), 
                        wxPoint(200,200), wxSize(250,350));
        dlg.ShowModal();
        return false;
    }
    
    DECLARE_EVENT_TABLE();
};

IMPLEMENT_APP(WrapTestApp);

BEGIN_EVENT_TABLE(WrapTestApp, wxApp)
END_EVENT_TABLE()


 	  	 

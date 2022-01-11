
//
// DlgTest sample, test on GTK.
// 


//#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <stdlib.h>
#include "wx/log.h"

#define ID_NEW_MINSIZE        1001
#define ID_NEW_LARGER         1002
#define ID_NEW_MINSIZE_TIMER  1003
#define ID_NEW_LARGER_TIMER   1004

wxPoint RandOff( int d ){
    return wxPoint( (rand()%d) - d/2, (rand()%d) - d/2 );
}



class TestDlg : public wxDialog {
public: 
    TestDlg( wxWindow *prnt, const wxChar *title, 
             wxSize size, wxSize min_size, bool timer_layout ) 
        : wxDialog(prnt,wxID_ANY,_T("Test"),
                   prnt->GetPosition()+RandOff(100), size, 
                   wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER), 
          m_sb_sz(wxVERTICAL,this,_T("Static box label")) 
          { 
          
        // Setting dlg min size
        m_sz_set = size;
        m_sz_min = min_size;
        SetMinSize( m_sz_min );
        
        wxSize sz = GetSize();
        // Here we get an incorrect value when our requested size is close to min size.
        printf( "Reading back size: (%d,%d)\n", sz.x, sz.y );
        
        // Populating static box sizer 
        m_sb_sz.Add( new wxSizerItem(10,10,10,0,0,NULL) );
        m_sb_sz.Add( new wxStaticText(this,wxID_ANY,_T("Enter text here:")) );
        m_sb_sz.Add( new wxSizerItem(3,10,3,0,0,NULL) );
        m_sb_sz.Add( new wxTextCtrl(this,wxID_ANY), 0, wxEXPAND, 0 );
        m_sb_sz.Add( new wxSizerItem(10,20,10,0,0,NULL) );
          
        // Buttons sizer 
        wxBoxSizer *pbsz = new wxBoxSizer(wxHORIZONTAL);
        pbsz->Add( new wxSizerItem(10,10,10,0,0,NULL) );
        pbsz->Add( new wxButton(this,wxID_OK) );
        pbsz->Add( new wxSizerItem(5,10,5,0,0,NULL) );
        pbsz->Add( new wxButton(this,wxID_CANCEL) );
        pbsz->Add( new wxSizerItem(10,10,10,0,0,NULL) );
        
        m_sb_sz.Add( pbsz, 10, wxEXPAND, 0 );
        
        // Space at bottom
        m_sb_sz.Add( new wxSizerItem(10,0,5,0,0,NULL) );
        
        
        // Set size of root sizer 
        m_tm_size.SetOwner(this);
        if( !timer_layout ){
            sz = GetClientSize(); 
            printf( "GetClientSize in ctor - (%d,%d) \n", sz.x, sz.y );
            m_sb_sz.SetDimension( 0,0, sz.x, sz.y );
            m_sz_last = sz;
        }
        else {
            // Setting the layout with a small random delay after initial window creation.
            m_tm_size.Start( rand()&0x3f, true );
        }
        
    }
    
    ~TestDlg( ){ } 
    
    const wxSize& GetNcSize() {
        static wxSize st_nc_sz; 
        if( st_nc_sz.y<=0 )
            st_nc_sz = GetSize()-GetClientSize();
        return st_nc_sz;
    }

    void OnSize( wxSizeEvent& e ){
        // To help trigger the layout offset bug, we stay away 
        // from below auto resizing. 
        /*
        // Update min size 
        SetMinSize( m_sz_min );
        
        // Too early call?
        if( GetNcSize().y<=0 ) return;
    
        wxSize sz = e.GetSize() - GetNcSize();
        if( sz!=m_sz_last ){
            // Redo layout 
            m_sb_sz.SetDimension( 0,0, sz.x, sz.y );
            m_sz_last = sz;
        }
        */
    }
    
    void OnTimer( wxTimerEvent& evt ){ 
        //wxSize sz = m_sz_set-GetNcSize(); // Client size 
        wxSize sz = GetClientSize();
        printf( "GetClientSize in OnTimer - (%d,%d) \n", sz.x, sz.y );
        m_sb_sz.SetDimension( 0,0, sz.x, sz.y );
        m_sz_last = sz;
    }
    
    wxSize           m_sz_last, m_sz_min, m_sz_set;
    wxStaticBoxSizer m_sb_sz;
    wxTimer          m_tm_size;
    
    DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(TestDlg, wxDialog)
	EVT_SIZE(TestDlg::OnSize)
	EVT_TIMER(wxID_ANY,TestDlg::OnTimer)
END_EVENT_TABLE()



class MainDlg : public wxDialog {
public:
	MainDlg( wxWindow *prnt, int id, const wxChar *title, wxPoint pos, wxSize size ) :
		wxDialog(prnt,id,title,pos,size,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER) { 
        
		m_pb_new_min = new wxButton( this, ID_NEW_MINSIZE, _T("New min sized dlg"), wxPoint(10,30) );
		m_pb_new = new wxButton( this, ID_NEW_LARGER, _T("New dlg"), wxPoint(10,70) );
		m_pb_new_min_timer = new wxButton( this, ID_NEW_MINSIZE_TIMER, _T("New min sized dlg - timer"), wxPoint(10,110) );
		m_pb_new_timer = new wxButton( this, ID_NEW_LARGER_TIMER, _T("New dlg - timer"), wxPoint(10,150) );
	}
	
	virtual ~MainDlg(){ }
	
    void OnNewMinSize( wxCommandEvent& e ){ 
        // Create a test dialog with size == min size
        TestDlg dlg( this, _T("Initial size should equal MinSize"), 
                     wxSize(200,150), wxSize(200,150), false );
        dlg.ShowModal();
    }

    void OnNew( wxCommandEvent& e ){
        // Create a test dialog with size > min size
        TestDlg dlg( this, _T("Initial size larger than MinSize"), 
                     wxSize(300,200), wxSize(200,150), false );
        dlg.ShowModal();
    }

    void OnNewMinSizeTimer( wxCommandEvent& e ){ 
        // Create a test dialog with size == min size
        TestDlg dlg( this, _T("Initial size should equal MinSize - timer"), 
                     wxSize(200,150), wxSize(200,150), true );
        dlg.ShowModal();
    }

    void OnNewTimer( wxCommandEvent& e ){
        // Create a test dialog with size > min size
        TestDlg dlg( this, _T("Initial size larger than MinSize - timer"), 
                     wxSize(300,200), wxSize(200,150), true );
        dlg.ShowModal();
    }


private:
	wxButton 	*m_pb_new_min;
	wxButton 	*m_pb_new;
	wxButton 	*m_pb_new_min_timer;
	wxButton 	*m_pb_new_timer;
    
	wxTimer m_timer;
	
	DECLARE_EVENT_TABLE();
};


BEGIN_EVENT_TABLE(MainDlg, wxDialog)
	EVT_BUTTON( ID_NEW_MINSIZE, MainDlg::OnNewMinSize )
	EVT_BUTTON( ID_NEW_LARGER, MainDlg::OnNew )
	EVT_BUTTON( ID_NEW_MINSIZE_TIMER, MainDlg::OnNewMinSizeTimer )
	EVT_BUTTON( ID_NEW_LARGER_TIMER, MainDlg::OnNewTimer )
END_EVENT_TABLE()


/*void MainDlg::OnTimer( wxTimerEvent& e ){
}*/



class MyApp : public wxApp {
public:
	virtual bool OnInit() {
		MainDlg dlg( NULL,wxID_ANY,_T("Test Dlg"), wxPoint(200,200), wxSize(300,220) );
		dlg.ShowModal();
		return false;
	}
	
};

IMPLEMENT_APP(MyApp);


 	  	 

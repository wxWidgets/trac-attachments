
//
// DlgTest sample, test on GTK.
// 


#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <stdlib.h>
#include "wx/log.h"

#define ID_MOVE_NEW		1001
#define ID_MOVE_SAME 	1002
#define ID_INC_SIZE 	1003


wxPoint RandOff( int d ){
    return wxPoint( (rand()%d) - d/2, (rand()%d) - d/2 );
}

class TestDlg : public wxDialog {
public: 
    TestDlg( wxWindow *prnt, const wxChar *title, wxSize size, wxSize min_size ) 
        : wxDialog(prnt,wxID_ANY,_T("Test"),
                   prnt->GetPosition()+RandOff(100), size, 
                   wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER), 
          m_sb_sz(wxVERTICAL,this,_T("Static box label")) { 
          
        // Setting dlg min size
        m_sz_set = size;
        m_sz_min = min_size;
        SetMinSize( m_sz_min );
        
        wxSize sz = GetSize();
        // ### Here we get an incorrect value when our requested size is 
        // close to min size!
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
        
        // Bottom space 
        m_sb_sz.Add( new wxSizerItem(10,0,5,0,0,NULL) );
        
        // Set size of root sizer 
        //wxSize sz = size-GetNcSize(); // Client size 
        //m_sb_sz.SetDimension( 0,0, sz.x, sz.y );
        //m_sz_last = sz;
        
        // Setting the layout with a small random delay after initial 
        // window creation.
        m_tm_size.SetOwner(this);
        m_tm_size.Start( rand()&0x3f, true );
    }
    
    ~TestDlg( ){ 
        // It seems StaticBoxSizer destruction contains a bug unless this is done
        wxStaticBox *psb = m_sb_sz.GetStaticBox();
        if( psb ) 
            psb->SetContainingSizer(NULL);
    } 
    
    const wxSize& GetNcSize() {
        static wxSize st_nc_sz; 
        if( st_nc_sz.y<=0 )
            st_nc_sz = GetSize()-GetClientSize();
        return st_nc_sz;
    }

    void OnSize( wxSizeEvent& e ){
        // To help trigger the layout offset bug, we stay away 
        // from below auto resizing. 
        return;
        
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
    }
    
    void OnTimer( wxTimerEvent& evt ){ 
        wxSize sz = m_sz_set-GetNcSize(); // Client size 
        m_sb_sz.SetDimension( 0,0, sz.x, sz.y );
        m_sz_last = sz;
    }
    
    wxSize           m_sz_last, m_sz_min, m_sz_set;
    wxStaticBoxSizer m_sb_sz;
    wxTimer          m_tm_size;
    
    DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(TestDlg, wxDialog)
	//EVT_TIMER(wxID_ANY,MainDlg::OnTimer)
	EVT_SIZE(TestDlg::OnSize)
	EVT_TIMER(wxID_ANY,TestDlg::OnTimer)
	//EVT_BUTTON(wxID_CANCEL,TestDlg::OnCancel)
END_EVENT_TABLE()



class MainDlg : public wxDialog {
public:
	MainDlg( wxWindow *prnt, int id, const wxChar *title, wxPoint pos, wxSize size ) :
		wxDialog(prnt,id,title,pos,size,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER) { 
		m_pb_new_min = new wxButton( this, ID_MOVE_NEW, _T("New min sized dlg"), wxPoint(10,30) );
		m_pb_new = new wxButton( this, ID_MOVE_SAME, _T("New dlg"), wxPoint(10,70) );
	}
	
	virtual ~MainDlg(){ }
	
private:
	void OnNewMinSize( wxCommandEvent &event );
	void OnNew( wxCommandEvent &event );

	wxButton 	*m_pb_new_min;
	wxButton 	*m_pb_new;
	
	wxTimer m_timer;
	
	DECLARE_EVENT_TABLE();
};


BEGIN_EVENT_TABLE(MainDlg, wxDialog)
	//EVT_TIMER(wxID_ANY,MainDlg::OnTimer)
	EVT_BUTTON(ID_MOVE_NEW,MainDlg::OnNewMinSize)
	EVT_BUTTON(ID_MOVE_SAME,MainDlg::OnNew)
END_EVENT_TABLE()


/*void MainDlg::OnTimer( wxTimerEvent& e ){
}*/

void MainDlg::OnNewMinSize( wxCommandEvent& e ){ 
    // Create a test dialog with its size 
    // being equal to its min size
    TestDlg dlg( this, _T("Initial size should equal MinSize"), 
                 wxSize(200,150), wxSize(200,150) );
    dlg.ShowModal();
}

void MainDlg::OnNew( wxCommandEvent& e ){
    // Create a test dialog with its size 
    // being equal to its min size
    TestDlg dlg( this, _T("Initial size larger than MinSize"), 
                 wxSize(300,200), wxSize(200,150) );
    dlg.ShowModal();
}


class MyApp : public wxApp {
public:
	virtual bool OnInit() {
		MainDlg dlg( NULL,wxID_ANY,_T("Test Dlg"), wxPoint(200,200), wxSize(300,220) );
		dlg.ShowModal();
		return false;
	}
	
};

IMPLEMENT_APP(MyApp);


 	  	 

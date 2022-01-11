
//
// Sample to show differences in ProcessEvent and AddPendingEvent 
// Generates a crash when using AddPendingEvent while ProcessEvent
// for the same command goes well. 
// 


#include <wx/wxprec.h>
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


// Command to popup text control 
#define ID_POPUP_EDIT_CLOSE   500 

// Custom edit control
class CustomEditCtrl : public wxTextCtrl {
public:
    CustomEditCtrl(wxWindow *prnt, const wxPoint& pos, const wxSize& size ) : 
        wxTextCtrl(prnt,wxID_ANY,_T("Edit text here..."), pos,size) {
    }
    void OnEditClose( wxCommandEvent& evt ){
        // For non TLW, this is just a wrapper to: delete this
        Destroy();
    }
    
	DECLARE_EVENT_TABLE();
};


BEGIN_EVENT_TABLE(CustomEditCtrl, wxTextCtrl)
	EVT_MENU(ID_POPUP_EDIT_CLOSE,CustomEditCtrl::OnEditClose)
END_EVENT_TABLE()


// Commands to dialog 
#define ID_POPUP_OPEN           1000 
#define ID_POPUP_CLOSE_PROCESS  1001 
#define ID_POPUP_CLOSE_PENDING  1002 

class PendingTestDialog: public wxDialog {
public:
	PendingTestDialog( wxWindow *prnt, int id, const wxChar *title, wxPoint pos, wxSize size ) 
        : wxDialog(prnt,id,title,pos,size) {
        m_pw_edit = NULL;
		m_pb_open = new wxButton( this, ID_POPUP_OPEN, _T("Open Popup Window"), wxPoint(40,40) );
		m_pb_close_process = new wxButton( this, ID_POPUP_CLOSE_PROCESS, _T("Close (process)"), wxPoint(40,100) );
		m_pb_close_pending = new wxButton( this, ID_POPUP_CLOSE_PENDING, _T("Close (pending)"), wxPoint(40,160) );
        EnableButtons( );
	}
	
protected:
    wxButton *m_pb_open;
    wxButton *m_pb_close_process;
    wxButton *m_pb_close_pending;
    wxWindow *m_pw_edit;
    
    void EnableButtons(){
        m_pb_open->Enable(m_pw_edit==NULL);
        m_pb_close_process->Enable(m_pw_edit!=NULL);
        m_pb_close_pending->Enable(m_pw_edit!=NULL);
    }
    
	void OnPopupOpen( wxCommandEvent &event ){
        if( !m_pw_edit ){
            m_pw_edit = new CustomEditCtrl(this,wxPoint(150,100),wxSize(100,50));
            EnableButtons( );
        }
    }
    
	void OnPopupCloseProcess( wxCommandEvent &event ){
        wxASSERT(m_pw_edit);
        wxCommandEvent evt(wxEVT_COMMAND_MENU_SELECTED,ID_POPUP_EDIT_CLOSE);
        m_pw_edit->ProcessEvent( evt );
        m_pw_edit = NULL;
        
        EnableButtons( );
    }
    
	void OnPopupClosePendning( wxCommandEvent &event ){
        wxASSERT(m_pw_edit);
        wxCommandEvent evt(wxEVT_COMMAND_MENU_SELECTED,ID_POPUP_EDIT_CLOSE);
        m_pw_edit->AddPendingEvent( evt );
        m_pw_edit = NULL;
        
        EnableButtons( );
    }

	DECLARE_EVENT_TABLE();
};


BEGIN_EVENT_TABLE(PendingTestDialog, wxDialog)
	EVT_BUTTON(ID_POPUP_OPEN,PendingTestDialog::OnPopupOpen)
	EVT_BUTTON(ID_POPUP_CLOSE_PROCESS,PendingTestDialog::OnPopupCloseProcess)
	EVT_BUTTON(ID_POPUP_CLOSE_PENDING,PendingTestDialog::OnPopupClosePendning)
END_EVENT_TABLE()


class MyApp : public wxApp {
public:
	virtual bool OnInit() {
		PendingTestDialog dlg(NULL,wxID_ANY,_T("Move Test"), wxPoint(200,200), wxSize(300,220));
		dlg.ShowModal();
		return false;
	}
};

IMPLEMENT_APP(MyApp);


 	  	 

/////////////////////////////////////////////////////////////////////////////
// This tiny app look at how size events are generated during top level construction.
// This currently differs on platforms, and this minimal app can spot that difference
// when run with different ports.
/////////////////////////////////////////////////////////////////////////////

#include <wx/wxprec.h>
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class InitSizeTestDialog : public wxDialog 
{
public:
    InitSizeTestDialog( wxWindow *prnt, int id, const wxChar *title, wxPoint pos, wxSize size ) :
        wxDialog(prnt,id,title,pos,size,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER) 
    { 
        // No events to start with
        m_sz_evt_cnt = 0;

        // Label + info
        wxStaticText *plabel = new wxStaticText( this, wxID_ANY, _T("#Size events:"), wxPoint(20,30), wxSize(100,25) );
        m_pcnt = new wxStaticText( this, wxID_ANY, _T("0"), wxPoint(120,30), wxSize(50,25) );
        
        // OK Button 
        new wxButton( this, wxID_OK, _T("OK"), wxPoint(50,70), wxSize(100,30) );
    }

protected:
    void OnSize( wxSizeEvent& e )
    {
        // Notification to stdout (needs console on Windows)
        printf( "OnSize event: (%d,%d)\n", e.GetSize().x, e.GetSize().y );

        // Show in dialog itself
        char buf[16]; 
        sprintf( buf, "%d", ++m_sz_evt_cnt );
        m_pcnt->SetLabel( buf );
    }

    int m_sz_evt_cnt;
    wxStaticText *m_pcnt;

private:
    DECLARE_EVENT_TABLE();
};


BEGIN_EVENT_TABLE(InitSizeTestDialog, wxDialog)
    EVT_SIZE(InitSizeTestDialog::OnSize)
END_EVENT_TABLE()


class InitSizeTestApp : public wxApp 
{
public:
    InitSizeTestApp() { }

    virtual bool OnInit() 
    {
        InitSizeTestDialog dlg(NULL,wxID_ANY,_T("Initial Size Event Test Dialog"), 
                                wxPoint(200,100), wxSize(200,150));
        dlg.ShowModal();
        return false;
    }
    
    DECLARE_EVENT_TABLE();
};

IMPLEMENT_APP(InitSizeTestApp);

BEGIN_EVENT_TABLE(InitSizeTestApp, wxApp)
END_EVENT_TABLE()


 	  	 

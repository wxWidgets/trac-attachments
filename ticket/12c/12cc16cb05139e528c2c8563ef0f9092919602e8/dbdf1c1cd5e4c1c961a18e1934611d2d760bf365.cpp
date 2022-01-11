/*
 * First Example
 * If this function MyFrame::OnCheckBug called from different control ( test button ), it's alright,
 * but if we call it from popup menu by right click on listctrl item...  ;)
 */

/*
 * Second Example
 * Just increase LIST_CTRL_SIZE for 100 items and scroll listctrl
 */

#define LIST_CTRL_SIZE 1

#include "wx/wx.h"
#include "wx/listctrl.h"
#include "wx/dynarray.h"


class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};


class MyListCtrl: public wxListCtrl
{
public:
    MyListCtrl(
        wxWindow *parent,
        const wxWindowID id,
        const wxPoint& pos,
        const wxSize& size,
        long style 
        ): wxListCtrl(parent, id, pos, size, style)
    {
    }

    void OnCacheHint( wxListEvent& event );
    void OnItemRightClick( wxListEvent& event );    

    void SetDataProvider( wxArrayInt *data );

private:
    virtual wxString OnGetItemText( long item, long column ) const;

    wxArrayInt *m_dataProvider;

    DECLARE_EVENT_TABLE()
};


class MyFrame: public wxFrame
{
public:
    MyFrame(const wxChar *title, int x, int y, int w, int h);

protected:
    void OnCheckBug( wxCommandEvent &event );

    wxBoxSizer *m_rootSizer;
    MyListCtrl *m_listCtrl;
    wxTextCtrl *m_logWindow;
    wxButton   *m_testButton;

    wxArrayInt *m_dataProvider;
    
private:
    DECLARE_EVENT_TABLE()
};


const int ID_CHECK_BUG = 1000;
const int ID_LIST_CTRL = 1001;


BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_CHECK_BUG, MyFrame::OnCheckBug)
    EVT_BUTTON(ID_CHECK_BUG, MyFrame::OnCheckBug)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(MyListCtrl, wxListCtrl)
    EVT_LIST_CACHE_HINT(ID_LIST_CTRL, MyListCtrl::OnCacheHint)
    EVT_LIST_ITEM_RIGHT_CLICK(ID_LIST_CTRL, MyListCtrl::OnItemRightClick)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)


bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( wxT("Enable Window Bug Test"), 50, 50, 450, 340 );

    frame->Show( true );

    SetTopWindow( frame );

    return true;
}


MyFrame::MyFrame(const wxChar *title, int x, int y, int w, int h)
       : wxFrame((wxFrame *)NULL, -1, title, wxPoint(x, y), wxSize(w, h))
{
    m_rootSizer = new wxBoxSizer( wxVERTICAL );

    m_listCtrl = new MyListCtrl(
        this, 
        ID_LIST_CTRL,
        wxDefaultPosition, 
        wxDefaultSize,
        wxLC_REPORT | wxLC_VIRTUAL | wxSUNKEN_BORDER | wxLC_EDIT_LABELS
    );

    m_rootSizer->Add( m_listCtrl, 1, wxGROW );

    m_listCtrl->InsertColumn( 0, _T("Column") );

    m_testButton = new wxButton(
        this,
        ID_CHECK_BUG,
        "Check Bug!"
    );
    
    m_rootSizer->Add( m_testButton, 0, wxGROW );

    m_logWindow = new wxTextCtrl(
        this, 
        -1, 
        wxEmptyString,
        wxDefaultPosition, 
        wxDefaultSize,
        wxTE_MULTILINE | wxSUNKEN_BORDER
    );

    m_rootSizer->Add( m_logWindow, 1, wxGROW );
        
    SetSizer( m_rootSizer );

    wxLog::SetActiveTarget( new wxLogTextCtrl( m_logWindow ) );

    m_dataProvider = new wxArrayInt();
    
    for ( size_t i = 0; i < LIST_CTRL_SIZE; i++ )
        m_dataProvider->Add( 0 );

    m_listCtrl->SetDataProvider( m_dataProvider );
}


void MyFrame::OnCheckBug( wxCommandEvent &WXUNUSED(event) )
{
    wxLogMessage( "Check Bug!" );

    for ( size_t i = 0; i < m_dataProvider->GetCount(); i++ )
        m_dataProvider->Item( i ) = 0;
    
    wxLogMessage( "Outer Enable( 0 )" );
    m_listCtrl->Enable( 0 );
    
    wxLogMessage( "Outer Enable( 1 )" );
    m_listCtrl->Enable( 1 );

    wxLogMessage( "MyListCtrl::IsEnabled() = %d", m_listCtrl->IsEnabled() );
    wxLogMessage( "::IsWindowEnabled( MyListCtrl::GetHWND ) = %d", ::IsWindowEnabled( (HWND)m_listCtrl->GetHWND() ) );
}


wxString MyListCtrl::OnGetItemText( long item, long column ) const
{
    int value = m_dataProvider->Item( item );
     
    if ( value == 0 )
    {
        wxLogMessage( "Internal Enable( 0 )" );
        ((wxWindow *)this)->Enable( 0 );

        m_dataProvider->Item( item ) = 100 + item;   

        wxLogMessage( "Internal Enable( 1 )" );
        ((wxWindow *)this)->Enable( 1 );        
    }

    return wxString::Format( _T("Item %ld"), m_dataProvider->Item( item ) );
}


void MyListCtrl::OnCacheHint( wxListEvent& event )
{
    wxLogMessage( "OnCacheHint: Items %ld .. %ld", event.GetCacheFrom(), event.GetCacheTo() );
}


void MyListCtrl::OnItemRightClick( wxListEvent& event )
{
    wxLogMessage( "OnItemRightClick" );

    wxMenu menu;

    menu.Append( ID_CHECK_BUG, _T("Check Bug!") );

    PopupMenu(&menu, event.GetPoint() );
}


void MyListCtrl::SetDataProvider( wxArrayInt *data )
{
    m_dataProvider = data;

    SetItemCount( data->GetCount() );
}


 	  	 

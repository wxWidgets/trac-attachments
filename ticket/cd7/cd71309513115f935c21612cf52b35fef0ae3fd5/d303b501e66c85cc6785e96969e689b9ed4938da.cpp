/////////////////////////////////////////////////////////////////////////////
// Name:        MyServer.cpp
// Author:      XX
// Created:     XX/XX/XX
// Copyright:   
/////////////////////////////////////////////////////////////////////////////


// For compilers that support precompilation
#include "wx/wxprec.h"

#include "wx/wx.h"

#include "wx/socket.h"

const int ID_MENU = 10000;
const int ID_START_SERVER = 10003;
const int ID_STOP_SERVER = 10004;
const int ID_TEST = 10005;

enum
{
  SERVER_ID = 100,
  SERVER_SOCKET_ID,
  ID_TEST_TIMER
};



//----------------------------------------------------------------------------
// MyFrame
//----------------------------------------------------------------------------

WX_DECLARE_LIST(wxSocketBase, MySocketList);

class MyFrame: public wxFrame
{
public:
    // constructors and destructors
    MyFrame( wxWindow *parent, wxWindowID id, const wxString &title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_FRAME_STYLE );
    ~MyFrame();
    
    
private:
    // WDR: method declarations for MyFrame
    void CreateMyMenuBar();
    
private:
    // WDR: member variable declarations for MyFrame
    
    // if we are a server
    wxSocketServer *m_server;
    MySocketList    m_clients;
    
    wxTextCtrl     *m_textCtrl;
    
    wxTimer         m_testTimer;
    int             m_testCounter;
    
private:
    // WDR: handler declarations for MyFrame
    void OnTest( wxCommandEvent &event );
    void OnStopServer( wxCommandEvent &event );
    void OnStartServer( wxCommandEvent &event );
    void OnStopClient( wxCommandEvent &event );
    void OnStartClient( wxCommandEvent &event );
    void OnAbout( wxCommandEvent &event );
    void OnQuit( wxCommandEvent &event );
    
    void SendTextToClient( wxSocketBase *client, const wxString &text );
    void SendText( const wxString &text );

    void OnServerEvent( wxSocketEvent &event );
    void OnServerSocketEvent( wxSocketEvent &event );
   
    void OnTestTimer( wxTimerEvent &event );

    void StartServer();
    void StopServer();
    
    void OnUpdateUIEvent( wxUpdateUIEvent &event );
    void UpdateStatusBar();

private:
    DECLARE_EVENT_TABLE()
};

//----------------------------------------------------------------------------
// MyApp
//----------------------------------------------------------------------------

class MyApp: public wxApp
{
public:
    MyApp();
    
    virtual bool OnInit();
    virtual int OnExit();
};


//------------------------------------------------------------------------------
// MyFrame
//------------------------------------------------------------------------------

#include <wx/listimpl.cpp>
WX_DEFINE_LIST(MySocketList);

// WDR: event table for MyFrame

BEGIN_EVENT_TABLE(MyFrame,wxFrame)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
    EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
    EVT_CLOSE(MyFrame::OnCloseWindow)
    EVT_SOCKET(SERVER_ID,  MyFrame::OnServerEvent)
    EVT_SOCKET(SERVER_SOCKET_ID,  MyFrame::OnServerSocketEvent)
    EVT_MENU( ID_START_SERVER, MyFrame::OnStartServer )
    EVT_MENU( ID_STOP_SERVER, MyFrame::OnStopServer )
    EVT_TIMER( ID_TEST_TIMER, MyFrame::OnTestTimer )
    EVT_UPDATE_UI_RANGE( ID_MENU, ID_MENU+100, MyFrame::OnUpdateUIEvent )
    EVT_MENU( ID_TEST, MyFrame::OnTest )
END_EVENT_TABLE()

MyFrame::MyFrame( wxWindow *parent, wxWindowID id, const wxString &title,
    const wxPoint &position, const wxSize& size, long style ) :
    wxFrame( parent, id, title, position, size, style ), m_testTimer( this, ID_TEST_TIMER )
{
    m_server = NULL;
    m_testCounter = 0;
    
    m_textCtrl = new wxTextCtrl( this, -1, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );

    CreateMyMenuBar();
    
    CreateStatusBar(2);
    SetStatusText( wxT("Welcome!") );
    
    StartServer();
}

MyFrame::~MyFrame()
{
    StopServer();
}


void MyFrame::CreateMyMenuBar()
{
    wxMenuBar *menubar = new wxMenuBar;
    
    wxMenu* item1 = new wxMenu;
    item1->Append( wxID_ABOUT, wxT("About"), wxT("") );
    item1->AppendSeparator();
    item1->Append( ID_START_SERVER, wxT("Start server"), wxT("") );
    item1->Append( ID_STOP_SERVER, wxT("Stop server"), wxT("") );
    item1->AppendSeparator();
    item1->Append( ID_TEST, wxT("Start test\tCtrl-T"), wxT("") );
    item1->AppendSeparator();
    item1->Append( wxID_EXIT, wxT("Quit"), wxT("") );
    menubar->Append( item1, wxT("File") );
    
    SetMenuBar( menubar );
}


void MyFrame::StartServer()
{
     if (m_server)
         return;

     wxIPV4address addr;
     addr.Service( 3000 );
     m_server = new wxSocketServer( addr, wxSOCKET_WAITALL );
     
    if (!m_server->IsOk())
    {
        delete m_server;
        m_server = NULL;
    }
    else
    {
        m_server->SetEventHandler( *this, SERVER_ID );
        m_server->SetNotify( wxSOCKET_CONNECTION_FLAG );
        m_server->Notify( true );
    }
    
    UpdateStatusBar();
}

void MyFrame::StopServer()
{
    if (m_server)
        delete m_server;
    m_server = NULL;
    
    UpdateStatusBar();
}


void MyFrame::OnTest( wxCommandEvent &event )
{
    m_testTimer.Start( 50 );
}

void MyFrame::OnStartServer( wxCommandEvent &event )
{
    StartServer();
}

void MyFrame::OnStopServer( wxCommandEvent &event )
{
    StopServer();
}

void MyFrame::OnAbout( wxCommandEvent &event )
{
    wxMessageDialog dialog( this, wxT("Welcome to MiniServer"),
        wxT("About MiniServer"), wxOK|wxICON_INFORMATION );
    dialog.ShowModal();
}

void MyFrame::OnQuit( wxCommandEvent &event )
{
     Close( true );                     
}

void MyFrame::SendTextToClient( wxSocketBase *client, const wxString &text )
{
    wxUint32 id = 1;   // ID for Text

    const wxScopedCharBuffer buf( text.utf8_str() );
    wxUint32 len = strlen( buf ) + 1;
    
    // wxIPV4address addr;
    // client->GetPeer( addr );
    // wxPrintf( "Sending buffer with len %u to socket host %s ip %s\n", len, addr.Hostname(), addr.IPAddress() );
    
    client->Write( &id, sizeof(id) );
    if (client->LastWriteCount() != sizeof(id)) 
        wxPrintf( "ID not fully written\n" );
    if (client->Error())
        wxPrintf( "Error after writing ID\n" );
    
    client->Write( &len, sizeof(len) );
    if (client->LastWriteCount() != sizeof(len))
        wxPrintf( "len not fully written\n" );
    if (client->Error())
        wxPrintf( "Error after writing len\n" );
        
    client->Write( buf, len );
    if (client->LastWriteCount() != len)
        wxPrintf( "buf not fully written\n" );
    if (client->Error())
        wxPrintf( "Error after writing buf\n" );

    // wxPrintf( "Finished writing %s\n", text );
}

void MyFrame::SendText( const wxString &text )
{
    if (m_server && m_server->IsOk())
    {
        // wxPrintf( "SendText in server: %s\n", text );
        
        for ( MySocketList::iterator iter = m_clients.begin(); iter != m_clients.end(); ++iter )
        {
            wxSocketBase *client = *iter;
            SendTextToClient( client, text );
        }
        
        return;
    }
}

void MyFrame::OnServerEvent( wxSocketEvent &event )
{
    if (event.GetSocketEvent() != wxSOCKET_CONNECTION)
    {
        wxLogError( "Server socket unknown event" );
        return;
    }
       
    wxSocketBase *socket = m_server->Accept ( false );
    
    if (socket)
    {
        socket->SetEventHandler(*this, SERVER_SOCKET_ID);
        socket->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
        socket->Notify(true);
    
        m_clients.push_back( socket );
    }
    else
    {
        wxLogError( "could not accept new conncetion" );
        return;
    }

    UpdateStatusBar();
}

void MyFrame::OnServerSocketEvent( wxSocketEvent &event )
{
    wxSocketBase *socket = event.GetSocket();

    if (event.GetSocketEvent() == wxSOCKET_INPUT)
    {
        wxLogError( "Should not get this at all" );

    } else
    if (event.GetSocketEvent() == wxSOCKET_LOST)
    {
        m_clients.remove( socket );

      // Destroy() should be used instead of delete wherever possible,
      // due to the fact that wxSocket uses 'delayed events' (see the
      // documentation for wxPostEvent) and we don't want an event to
      // arrive to the event handler (the frame, here) after the socket
      // has been deleted. Also, we might be doing some other thing with
      // the socket at the same time; for example, we might be in the
      // middle of a test or something. Destroy() takes care of all
      // this for us.

       socket->Destroy();
       UpdateStatusBar();
    }
}

void MyFrame::OnTestTimer( wxTimerEvent &event )
{
    wxString text;
    text.Printf( "Test text %i", m_testCounter );
    SendText( text );
    m_testCounter ++;
    if (m_testCounter == 100)
    {
        m_testTimer.Stop();
        m_testCounter = 0;
    }
}

void MyFrame::UpdateStatusBar()
{
    if (m_server && m_server->IsOk())
    {
        wxString s;
        if (m_clients.GetCount() == 1)
            s.Printf( "Server connected to 1 client" );
        else
            s.Printf( "Server connected to %i clients", (int) m_clients.GetCount() );
            
        SetStatusText( s, 0 );
    }
    else
    {
        SetStatusText( "Server not running", 0);
    }
}

void MyFrame::OnUpdateUIEvent( wxUpdateUIEvent &event )
{
    if (event.GetId() == ID_STOP_SERVER)
        event.Enable( m_server && m_server->IsOk() );
    else 
    if (event.GetId() == ID_START_SERVER)
        event.Enable( m_server == NULL );
}

//------------------------------------------------------------------------------
// MyApp
//------------------------------------------------------------------------------

IMPLEMENT_APP(MyApp)

MyApp::MyApp()
{
}

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( NULL, -1, "MiniServer", wxPoint(20,20), wxSize(700,540) );
    frame->Show( true );
    
    return true;
}

int MyApp::OnExit()
{
    return 0;
}


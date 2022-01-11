/////////////////////////////////////////////////////////////////////////////
// Name:        MyClient.cpp
// Author:      XX
// Created:     XX/XX/XX
// Copyright:   
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation
#include "wx/wxprec.h"

#include "wx/wx.h"

#include "wx/socket.h"

const int ID_MENU = 10000;
const int ID_START_CLIENT = 10003;
const int ID_STOP_CLIENT = 10004;


enum
{
  CLIENT_SOCKET_ID = 100
};


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
    void CreateMyMenuBar();
    
private:
    wxTextCtrl     *m_textCtrl;
    wxSocketClient *m_client;
    

private:
    void OnStopClient( wxCommandEvent &event );
    void OnStartClient( wxCommandEvent &event );
    void OnAbout( wxCommandEvent &event );
    void OnQuit( wxCommandEvent &event );
    
    bool ReadString( wxSocketBase *socket, wxString &text );

    void OnClientSocketEvent( wxSocketEvent &event );

    void StartClient();
    void StopClient();
    
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

// WDR: event table for MyFrame

BEGIN_EVENT_TABLE(MyFrame,wxFrame)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
    EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
    EVT_CLOSE(MyFrame::OnCloseWindow)
    EVT_SOCKET(CLIENT_SOCKET_ID, MyFrame::OnClientSocketEvent)
    EVT_MENU( ID_START_CLIENT, MyFrame::OnStartClient )
    EVT_MENU( ID_STOP_CLIENT, MyFrame::OnStopClient )
    EVT_UPDATE_UI_RANGE( ID_MENU, ID_MENU+100, MyFrame::OnUpdateUIEvent )
END_EVENT_TABLE()

MyFrame::MyFrame( wxWindow *parent, wxWindowID id, const wxString &title,
    const wxPoint &position, const wxSize& size, long style ) :
    wxFrame( parent, id, title, position, size, style )
{
    m_client = NULL;
    
    m_textCtrl = new wxTextCtrl( this, -1, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );

    CreateMyMenuBar();
    
    CreateStatusBar(2);
    SetStatusText( wxT("Welcome!") );
    
    StartClient();
}

MyFrame::~MyFrame()
{
    StopClient();
}

void MyFrame::CreateMyMenuBar()
{
    wxMenuBar *menubar = new wxMenuBar;
    
    wxMenu* item1 = new wxMenu;
    item1->Append( wxID_ABOUT, wxT("About"), wxT("") );
    item1->AppendSeparator();
    item1->Append( ID_START_CLIENT, wxT("Connect to server"), wxT("") );
    item1->Append( ID_STOP_CLIENT, wxT("Stop connection to server"), wxT("") );
    item1->AppendSeparator();
    item1->Append( wxID_EXIT, wxT("Quit"), wxT("") );
    menubar->Append( item1, wxT("File") );
    
    SetMenuBar( menubar );
}


void MyFrame::StartClient()
{
    // Create the socket
    m_client = new wxSocketClient();

    // Setup the event handler and subscribe to most events
    m_client->SetEventHandler(*this, CLIENT_SOCKET_ID );
    m_client->SetNotify( wxSOCKET_CONNECTION_FLAG |
                         wxSOCKET_INPUT_FLAG |
                         wxSOCKET_LOST_FLAG );
    m_client->Notify(true);
}

void MyFrame::StopClient()
{  
    if (m_client)
        delete m_client;
    m_client = NULL;
}

void MyFrame::OnStartClient( wxCommandEvent &event )
{
    wxIPV4address addr;
    
    // Ask user for server address
    wxString hostname = wxGetTextFromUser(
        "Enter the address of the MyServer server:",
        "Connect ...",
        "localhost" );
    if ( hostname.empty() )
        return;

    SetStatusText( "Client not connected" );

    addr.Hostname(hostname);
    addr.Service(3000);
    m_client->Connect( addr, false);
}

void MyFrame::OnStopClient( wxCommandEvent &event )
{
    m_client->Close();
}

void MyFrame::OnAbout( wxCommandEvent &event )
{
    wxMessageDialog dialog( this, wxT("Welcome to my MiniClient"),
        wxT("About MiniClient"), wxOK|wxICON_INFORMATION );
    dialog.ShowModal();
}

void MyFrame::OnQuit( wxCommandEvent &event )
{
     Close( true );                     
}

bool MyFrame::ReadString( wxSocketBase *socket, wxString &text )
{ 
    wxUint32 len;
    socket->Read( &len, sizeof(len) );
    
    if (socket->Error())
       wxLogError( "Read error in ReadString len" );
    if (socket->LastReadCount() != sizeof(len))
       wxLogError( "ReadString len not fully read" );

    wxCharBuffer buf( len+1 );
    socket->Read( buf.data(), len );
    text = wxString::FromUTF8( buf.data(), len );
    
    if (socket->Error())
       wxLogError( "Read error in ReadString buf" );
    if (socket->LastReadCount() != len)
       wxLogError( "ReadString buf not fully read" );

    return true;
}

void MyFrame::OnClientSocketEvent( wxSocketEvent &event )
{
    wxSocketBase *socket = event.GetSocket();

    if (event.GetSocketEvent() == wxSOCKET_CONNECTION)
    {
        if (m_client && m_client->IsConnected())
        {
            // wxPrintf( "block\n" );
            m_client->SetFlags( wxSOCKET_WAITALL | wxSOCKET_BLOCK );
        }

        UpdateStatusBar();
    }
    else if (event.GetSocketEvent() == wxSOCKET_LOST)
    {
        UpdateStatusBar();
    }
    else if (event.GetSocketEvent() == wxSOCKET_INPUT)
    {
        wxUint32 id = 0;
        socket->Read( &id, sizeof(id) );
        
        if (id == 1)    // ID for text
        {
            wxString text;
            if (ReadString( socket, text ))
            {
                m_textCtrl->AppendText( text );
                m_textCtrl->AppendText( "\n" );
            }
        }
        else
        {
            wxLogError( "Client socket wrong data" );
        }
        
    }
    else 
    {
        wxLogError( "Client socket unknown event" );
        return;
    }
}

void MyFrame::UpdateStatusBar()
{
    if (m_client && m_client->IsConnected())
    {
        wxIPV4address addr;
        m_client->GetPeer(addr);
        wxString s;
        s.Printf( "Client connected to %s : %d", addr.IPAddress(), addr.Service() );
        SetStatusText( s, 0 );
    }
    else
    {
        SetStatusText( "Client not connected", 0);
    }
}

void MyFrame::OnUpdateUIEvent( wxUpdateUIEvent &event )
{
    if (event.GetId() == ID_STOP_CLIENT)
        event.Enable( m_client && m_client->IsConnected() );
    else 
    if (event.GetId() == ID_START_CLIENT)
        event.Enable( m_client && !m_client->IsConnected() );
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
    MyFrame *frame = new MyFrame( NULL, -1, "MiniClient", wxPoint(20,20), wxSize(700,540) );
    frame->Show( true );
    
    return true;
}

int MyApp::OnExit()
{
    return 0;
}


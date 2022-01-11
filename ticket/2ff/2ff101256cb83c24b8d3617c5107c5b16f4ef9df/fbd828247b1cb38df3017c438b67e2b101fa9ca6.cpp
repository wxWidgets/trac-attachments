#include "wx/wx.h"

enum {
    ID_SCROLL = 101
};


class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

    void OnScrollBitmap(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnExit(wxCommandEvent& WXUNUSED(event)) { Close(); }

private:
    wxPanel * m_Panel;
    wxBitmap m_Bitmap;

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_SCROLL, MyFrame::OnScrollBitmap)
    EVT_MENU(wxID_EXIT, MyFrame::OnExit)
wxEND_EVENT_TABLE()


class MyApp : public wxApp
{
public:
    virtual bool OnInit() 
    {
        wxApp::OnInit();
        MyFrame *frame = new MyFrame("Bitmap blit bug");
        frame->Show(true);
        return true;
    }
};


wxIMPLEMENT_APP(MyApp);

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
    SetIcon(wxICON(sample));

    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    fileMenu->Append(ID_SCROLL, "&Scroll Bitmap", "Scroll by one pixel" );
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");

    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");

    SetMenuBar(menuBar);

    m_Panel = new wxPanel(this);
    wxBoxSizer * sizer = new wxBoxSizer(wxVERTICAL);
    m_Panel->SetSizer(sizer);

    wxMemoryDC dcbmp;
    m_Bitmap.Create( 200, 200, 24 );
    dcbmp.SelectObject( m_Bitmap );
    dcbmp.SetBrush( *wxBLACK_BRUSH );
    dcbmp.DrawRectangle( 0, 0, 9999, 9999 );
    dcbmp.SetPen( *wxGREEN_PEN );

    // Draw cross hatch.

    for( int i = 0; i < 200; i+=25 )
    {
        dcbmp.DrawLine( i, 0, 200, 200-i );
        dcbmp.DrawLine( 0, i, 200-i, 200 );
        dcbmp.DrawLine( i, 0, 0, i );
        dcbmp.DrawLine( 200, i, i, 200 );
    }

    m_Panel->Bind( wxEVT_PAINT, &MyFrame::OnPaint, this );
}


// event handlers

void MyFrame::OnPaint( wxPaintEvent & event )
{
    wxPaintDC dc( m_Panel );
    wxSize size = m_Panel->GetSize();
    wxMemoryDC dcbmp;
    dcbmp.SelectObject( m_Bitmap );
    dc.StretchBlit(
        0, 0, size.x, size.y,
        &dcbmp, 0, 0, 200, 200
    );
}

void MyFrame::OnScrollBitmap( wxCommandEvent & event )
{
    wxMemoryDC dcbmp( m_Bitmap );
    dcbmp.Blit( 0, 1, 200, 199, &dcbmp, 0, 0 );
    Refresh();
}



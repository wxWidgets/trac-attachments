#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};


class MyCanvas: public wxScrolledWindow
{
public:
    MyCanvas() { }
    MyCanvas( wxWindow *parent ) : wxScrolledWindow( parent, wxID_ANY,
                            wxDefaultPosition, wxDefaultSize,
                            wxSUNKEN_BORDER ){
    SetBackgroundColour(*wxWHITE);
    }

    void OnPaint( wxPaintEvent& WXUNUSED(event) ){
		wxPaintDC dc( this );
		PrepareDC( dc );
		dc.Clear();
		dc.DrawRectangle( 0,0,10,10 );
		}

    void OnClientDCPaint( void ){
 		wxClientDC dc( this );
 		PrepareDC( dc );
		dc.Clear();
		dc.DrawRectangle( 0,0,10,10 );
		}

    void OnWindowDCPaint( void ){
 		wxWindowDC dc( this );
 		PrepareDC( dc );
		dc.Clear();
		dc.DrawRectangle( 0,0,10,10 );
		}

private:
    DECLARE_DYNAMIC_CLASS(MyCanvas)
    DECLARE_EVENT_TABLE()
};

IMPLEMENT_DYNAMIC_CLASS(MyCanvas, wxScrolledWindow)

BEGIN_EVENT_TABLE(MyCanvas, wxScrolledWindow)
    EVT_PAINT(MyCanvas::OnPaint)
END_EVENT_TABLE()

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    void OnQuit(wxCommandEvent& WXUNUSED(event)){ Close(true); }
    void OnAbout(wxCommandEvent& WXUNUSED(event)){ wxMessageBox(wxT("The wxClientDC OSX bug sample.\n(c) EUA 2012"), wxT("About Caret"), wxOK | wxICON_INFORMATION, this);}
    void OnDrawClientDC( wxCommandEvent& WXUNUSED(event) ){ m_canvas->OnClientDCPaint(); }
    void OnDrawWindowDC( wxCommandEvent& WXUNUSED(event) ){ m_canvas->OnWindowDCPaint(); }
    
private:
    MyCanvas *m_canvas;
    DECLARE_EVENT_TABLE()
};

enum{
    Menu_Quit = 1, Menu_About,  Menu_OnDrawClientDC, Menu_OnDrawWindowDC};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Menu_Quit,  MyFrame::OnQuit)
    EVT_MENU(Menu_About, MyFrame::OnAbout)
    EVT_MENU(Menu_OnDrawClientDC, MyFrame::OnDrawClientDC)
    EVT_MENU(Menu_OnDrawWindowDC, MyFrame::OnDrawWindowDC)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit(){
    if ( !wxApp::OnInit() )
        return false;
    MyFrame *frame = new MyFrame(wxT("wxClientDC bug sample"), wxPoint(50, 50), wxSize(450, 340));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, wxID_ANY, title, pos, size){
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(Menu_OnDrawClientDC, wxT("&wxCliendDC Draw"));
    menuFile->Append(Menu_OnDrawWindowDC, wxT("&wxWindowDC Draw"));
    menuFile->AppendSeparator();
    menuFile->Append(Menu_About, wxT("&About\tCtrl-A"), wxT("Show about dialog"));
    menuFile->AppendSeparator();
    menuFile->Append(Menu_Quit, wxT("E&xit\tAlt-X"), wxT("Quit this program"));
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, wxT("&File"));
    SetMenuBar(menuBar);
    m_canvas = new MyCanvas(this);
}

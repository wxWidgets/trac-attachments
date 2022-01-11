/////////////////////////////////////////////////////////////////////////////
// Name:        widget.cpp
// Purpose:     wxHtml testing example
//              Demonstrates embedded controls
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma implementation "test.cpp"
    #pragma interface "test.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif


#include "wx/html/htmlwin.h"

//#include "../../sample.xpm"

int g_widgetType = 0;

/*


TAG HANDER FOR 'MYBIND' TAG


*/

#include "wx/html/m_templ.h"


TAG_HANDLER_BEGIN(MYBIND, "MYBIND")

TAG_HANDLER_PROC(tag)
{
    wxWindow *wnd;
    int ax, ay;
    int fl = 0;

    tag.ScanParam(wxT("X"), wxT("%i"), &ax);
    tag.ScanParam(wxT("Y"), wxT("%i"), &ay);

    if (tag.HasParam(wxT("FLOAT"))) fl = ax;

    if (g_widgetType == 0)
        wnd = new wxChoice(m_WParser->GetWindow(), wxID_ANY);
    else
        wnd = new wxTextCtrl(m_WParser->GetWindow(), wxID_ANY, tag.GetParam(wxT("NAME")), wxPoint(0,0), wxSize(ax, ay), wxTE_MULTILINE);

    //wnd = new wxButton(m_WParser->GetWindow(), wxID_ANY, tag.GetParam(wxT("NAME")),
        //wxPoint(0,0), wxSize(ax, ay));

    wnd->Show(true);

    m_WParser->GetContainer()->InsertCell(new wxHtmlWidgetCell(wnd, fl));

    return false;
}

TAG_HANDLER_END(MYBIND)



TAGS_MODULE_BEGIN(MyBind)

    TAGS_MODULE_ADD(MYBIND)

TAGS_MODULE_END(MyBind)


// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnBack(wxCommandEvent& event);
    void OnForward(wxCommandEvent& event);
    void OnToggleWidgetType(wxCommandEvent& event);
    void OnForceRefresh(wxCommandEvent& event);

private:
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
};

// Define a new frame type: this is going to be our main frame
class MyWindow : public wxWindow
{
public:
    // ctor(s)
    // frame constructor
    MyWindow(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize)
    : wxWindow(parent, id, pos, size)
    {
    }


    // event handlers (these functions should _not_ be virtual)
    void OnPaint(wxPaintEvent& event);

private:
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = 1,
    Minimal_Back,
    Minimal_Forward,
    Minimal_WidgetType,
    Minimal_ForceRefresh,

    // controls start here (the numbers are, of course, arbitrary)
    Minimal_Text = 1000,
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_Back, MyFrame::OnBack)
    EVT_MENU(Minimal_Forward, MyFrame::OnForward)
    EVT_MENU(Minimal_WidgetType, MyFrame::OnToggleWidgetType)
    EVT_MENU(Minimal_ForceRefresh, MyFrame::OnForceRefresh)
END_EVENT_TABLE()


BEGIN_EVENT_TABLE( MyWindow, wxWindow )

    EVT_PAINT( MyWindow::OnPaint )

END_EVENT_TABLE()

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also declares the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MyApp)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// `Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // Create the main application window
    MyFrame *frame = new MyFrame( _("wxHtmlWindow testing application"),
        wxDefaultPosition, wxSize(640, 480) );

    // Show it and tell the application that it's our main window
    // @@@ what does it do exactly, in fact? is it necessary here?
    frame->Show(true);
    SetTopWindow(frame);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

wxHtmlWindow *html;
wxWindow *testWindow;

// frame constructor
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, wxID_ANY, title, pos, size)
{
    // create a menu bar
    wxMenu *menuFile = new wxMenu;
    wxMenu *menuNav = new wxMenu;

    menuFile->Append(Minimal_Quit, _("E&xit"));
    menuNav->Append(Minimal_Back, _("Go &BACK"));
    menuNav->Append(Minimal_Forward, _("Go &FORWARD"));
    menuNav->Append(Minimal_WidgetType, _("&Toggle the widget type\tF2"));
    menuNav->Append(Minimal_ForceRefresh, _("Force a test window refresh\tF3"));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, _("&File"));
    menuBar->Append(menuNav, _("&Navigate"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);

    //SetIcon(wxIcon(sample_xpm));
    
#if wxUSE_STATUSBAR
    CreateStatusBar(2);
#endif // wxUSE_STATUSBAR

    int w,h;
    GetClientSize(&w, &h);

    html = new wxHtmlWindow(this, 11111, wxPoint(0, 0) , wxSize(w, h/2));
    html -> SetRelatedFrame(this, _("wxHTML Demo: '%s'"));
#if wxUSE_STATUSBAR
    html -> SetRelatedStatusBar(1);
#endif // wxUSE_STATUSBAR
    testWindow = new MyWindow(this, 11112, wxPoint(0, h/2) , wxSize(w, h/2)); 
    html -> LoadPage(wxT("start.htm"));

}


// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnBack(wxCommandEvent& WXUNUSED(event))
{
    if (!html -> HistoryBack()) wxMessageBox(_("You reached prehistory era!"));
}


void MyFrame::OnForward(wxCommandEvent& WXUNUSED(event))
{
    if (!html -> HistoryForward()) wxMessageBox(_("No more items in history!"));
}

void MyFrame::OnToggleWidgetType(wxCommandEvent& WXUNUSED(event))
{
    g_widgetType = (g_widgetType == 0)? 1  : 0;
    html -> LoadPage(wxT("start.htm"));
    testWindow->Refresh();
}

void MyFrame::OnForceRefresh(wxCommandEvent& WXUNUSED(event))
{
    testWindow->Refresh();
    wxLog::SetTraceMask(wxTraceMessages);
    wxLogDebug("TRACE ON MyFrame=%08lx, testWindow=%08lx , html=%08lx",this, testWindow, html);
}

void MyWindow::OnPaint( wxPaintEvent& event )
{
    wxLog::SetTraceMask(0);
    wxLogDebug("TRACE OFF");
    wxPaintDC dc(this);
    PrepareDC(dc);
    dc.DrawText("This text does not always show", 10, 10);

    event.Skip();
}

 	  	 

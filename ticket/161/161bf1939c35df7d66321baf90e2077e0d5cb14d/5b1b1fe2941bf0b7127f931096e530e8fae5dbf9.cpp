/////////////////////////////////////////////////////////////////////////////
// Name:        minimal.cpp
// Purpose:     Minimal wxWidgets sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

			// Biehl
	wxPen								gCyanPen;

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows it is in resources and even
// though we could still include the XPM here it would be unused)
#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "../sample.xpm"
#endif

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

	MyApp ();
    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit() wxOVERRIDE;
};

class MyFrame;

// define a scrollable canvas for drawing onto
class MyCanvas: public wxScrolledWindow
{
public:
    MyCanvas( MyFrame *parent );

    void OnPaint(wxPaintEvent &event);
    void OnMouseMove(wxMouseEvent &event);
    void OnMouseDown(wxMouseEvent &event);
    void OnMouseUp(wxMouseEvent &event);

    void ToShow(int show) { m_show = show; Refresh(); }
    int GetPage() { return m_show; }

    // set or remove the clipping region
    void Clip(bool clip) { m_clip = clip; Refresh(); }
#if wxUSE_GRAPHICS_CONTEXT
    bool HasRenderer() const { return m_renderer != NULL; }
    void UseGraphicRenderer(wxGraphicsRenderer* renderer);
    bool IsDefaultRenderer() const
    {   if ( !m_renderer ) return false;
        return m_renderer == wxGraphicsRenderer::GetDefaultRenderer();
    }
    bool IsRendererName(const wxString& name) const
    {   if ( !m_renderer ) return name.empty();
        return m_renderer->GetName() == name;
    }
    wxGraphicsRenderer* GetRenderer() const { return m_renderer; }
#endif // wxUSE_GRAPHICS_CONTEXT
    void UseBuffer(bool use) { m_useBuffer = use; Refresh(); }
    void ShowBoundingBox(bool show) { m_showBBox = show; Refresh(); }
    void GetDrawingSize(int* width, int* height) const;

    void Draw(wxDC& dc);

protected:
    enum DrawMode
    {
        Draw_Normal,
        Draw_Stretch
    };

    void DrawTestLines( int x, int y, int width, wxDC &dc );
    void DrawTestPoly(wxDC& dc);
    void DrawTestBrushes(wxDC& dc);
    void DrawText(wxDC& dc);
    void DrawImages(wxDC& dc, DrawMode mode);
    void DrawWithLogicalOps(wxDC& dc);
#if wxDRAWING_DC_SUPPORTS_ALPHA || wxUSE_GRAPHICS_CONTEXT
    void DrawAlpha(wxDC& dc);
#endif
#if wxUSE_GRAPHICS_CONTEXT
    void DrawGraphics(wxGraphicsContext* gc);
#endif
    void DrawRegions(wxDC& dc);
    void DrawCircles(wxDC& dc);
    void DrawSplines(wxDC& dc);
    void DrawDefault(wxDC& dc);
    void DrawGradients(wxDC& dc);
    void DrawSystemColours(wxDC& dc);

    void DrawRegionsHelper(wxDC& dc, wxCoord x, bool firstTime);

private:
    MyFrame *m_owner;

    int          m_show;
    wxBitmap     m_smile_bmp;
    wxIcon       m_std_icon;
    bool         m_clip;
    //wxOverlay    m_overlay;
    bool         m_rubberBand;
    wxPoint      m_anchorpoint;
    wxPoint      m_currentpoint;
#if wxUSE_GRAPHICS_CONTEXT
    wxGraphicsRenderer* m_renderer;
#endif
    bool         m_useBuffer;
    bool         m_showBBox;
    wxCoord      m_sizeX;
    wxCoord      m_sizeY;

    wxDECLARE_EVENT_TABLE();
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

private:
    MyCanvas   *m_canvas;

    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT
};

// ----------------------------------------------------------------------------
// MyCanvas
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them.
wxBEGIN_EVENT_TABLE(MyCanvas, wxScrolledWindow)
    EVT_PAINT  (MyCanvas::OnPaint)
    //EVT_MOTION (MyCanvas::OnMouseMove)
    //EVT_LEFT_DOWN (MyCanvas::OnMouseDown)
    //EVT_LEFT_UP (MyCanvas::OnMouseUp)
wxEND_EVENT_TABLE()

//#include "smile.xpm"

MyCanvas::MyCanvas(MyFrame *parent)
        : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                           wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE)
{
    m_owner = parent;
    //m_show = File_ShowDefault;
    //m_smile_bmp = wxBitmap(smile_xpm);
    //m_std_icon = wxArtProvider::GetIcon(wxART_INFORMATION);
    m_clip = false;
    m_rubberBand = false;
#if wxUSE_GRAPHICS_CONTEXT
    m_renderer = NULL;
#endif
    m_useBuffer = false;
    m_showBBox = false;
    m_sizeX = 0;
    m_sizeY = 0;
}



void MyCanvas::OnPaint(wxPaintEvent &WXUNUSED(event))
{
        wxPaintDC pdc(this);
        Draw(pdc);
}



void MyCanvas::Draw(wxDC& pdc)
{
/*
#if wxUSE_GRAPHICS_CONTEXT
    wxGCDC gdc;

    if ( m_renderer )
    {
        wxGraphicsContext* context;
        if ( wxPaintDC *paintdc = wxDynamicCast(&pdc, wxPaintDC) )
        {
            context = m_renderer->CreateContext(*paintdc);
        }
        else if ( wxMemoryDC *memdc = wxDynamicCast(&pdc, wxMemoryDC) )
        {
            context = m_renderer->CreateContext(*memdc);
        }
#if wxUSE_METAFILE && defined(wxMETAFILE_IS_ENH)
        else if ( wxMetafileDC *metadc = wxDynamicCast(&pdc, wxMetafileDC) )
        {
            context = m_renderer->CreateContext(*metadc);
        }
#endif
        else
        {
            wxFAIL_MSG( "Unknown wxDC kind" );
            return;
        }

        gdc.SetBackground(GetBackgroundColour());
        gdc.SetGraphicsContext(context);
    }

    wxDC &dc = m_renderer ? static_cast<wxDC&>(gdc) : pdc;
#else
*/
    wxDC &dc = pdc ;
//#endif

    // Adjust scrolled contents for screen drawing operations only.
    if ( /*wxDynamicCast(&pdc, wxBufferedPaintDC) ||*/
         wxDynamicCast(&pdc, wxPaintDC) )
    {
        PrepareDC(dc);
    }

    m_owner->PrepareDC(dc);

    dc.Clear();

	  //dc.SetPen(*wxMEDIUM_GREY_PEN);
	  dc.SetPen (gCyanPen);
	  for ( int i = 0; i < 200; i++ )
			dc.DrawLine (0, i*10, i*10, 0);
	/*
    switch ( m_show )
    {
        case File_ShowDefault:
            DrawDefault(dc);
            break;

        case File_ShowCircles:
            DrawCircles(dc);
            break;

        case File_ShowSplines:
            DrawSplines(dc);
            break;

        case File_ShowRegions:
            DrawRegions(dc);
            break;

        case File_ShowText:
            DrawText(dc);
            break;

        case File_ShowLines:
            DrawTestLines( 0, 100, 0, dc );
            DrawTestLines( 0, 320, 1, dc );
            DrawTestLines( 0, 540, 2, dc );
            DrawTestLines( 0, 760, 6, dc );
            break;

        case File_ShowBrushes:
            DrawTestBrushes(dc);
            break;

        case File_ShowPolygons:
            DrawTestPoly(dc);
            break;

        case File_ShowMask:
            DrawImages(dc, Draw_Normal);
            break;

        case File_ShowMaskStretch:
            DrawImages(dc, Draw_Stretch);
            break;

        case File_ShowOps:
            DrawWithLogicalOps(dc);
            break;

#if wxDRAWING_DC_SUPPORTS_ALPHA || wxUSE_GRAPHICS_CONTEXT
        case File_ShowAlpha:
            DrawAlpha(dc);
            break;
#endif // wxDRAWING_DC_SUPPORTS_ALPHA || wxUSE_GRAPHICS_CONTEXT
#if wxUSE_GRAPHICS_CONTEXT
        case File_ShowGraphics:
            DrawGraphics(gdc.GetGraphicsContext());
            break;
#endif

        case File_ShowGradients:
            DrawGradients(dc);
            break;

        case File_ShowSystemColours:
            DrawSystemColours(dc);
            break;

        default:
            break;
    }
	
    // For drawing with raw wxGraphicsContext
    // there is no bounding box to obtain.
    if ( m_showBBox
#if wxUSE_GRAPHICS_CONTEXT
         && m_show != File_ShowGraphics
#endif // wxUSE_GRAPHICS_CONTEXT
       )
    {
        dc.SetPen(wxPen(wxColor(0, 128, 0), 1, wxPENSTYLE_DOT));
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.DrawRectangle(dc.MinX(), dc.MinY(), dc.MaxX()-dc.MinX()+1, dc.MaxY()-dc.MinY()+1);
    }

    // Adjust drawing area dimensions only if screen drawing is invoked.
    if ( wxDynamicCast(&pdc, wxBufferedPaintDC) ||
         wxDynamicCast(&pdc, wxPaintDC) )
    {
        wxCoord x0, y0;
        dc.GetDeviceOrigin(&x0, &y0);
        m_sizeX = dc.LogicalToDeviceX(dc.MaxX()) - x0 + 1;
        m_sizeY = dc.LogicalToDeviceY(dc.MaxY()) - y0 + 1;
    }
	 */
}


// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
wxEND_EVENT_TABLE()

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
wxIMPLEMENT_APP(MyApp);

MyApp::MyApp ()
{
			// Biehl
	
	gCyanPen.SetColour (*wxCYAN);
	
}

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;

    // create the main application window
    MyFrame *frame = new MyFrame("Minimal wxWidgets App");

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
    // set the frame icon
    SetIcon(wxICON(sample));

#if wxUSE_MENUS
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, "&About\tF1", "Show about dialog");

    fileMenu->Append(Minimal_Quit, "E&xit\tAlt-X", "Quit this program");

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#else // !wxUSE_MENUS
    // If menus are not available add a button to access the about box
    wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* aboutBtn = new wxButton(this, wxID_ANY, "About...");
    aboutBtn->Bind(wxEVT_BUTTON, &MyFrame::OnAbout, this);
    sizer->Add(aboutBtn, wxSizerFlags().Center());
#endif // wxUSE_MENUS/!wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText("Welcome to wxWidgets!");
#endif // wxUSE_STATUSBAR

    m_canvas = new MyCanvas (this);
	
}	// end "MyFrame"


// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxString::Format
                 (
                    "Welcome to %s!\n"
                    "\n"
                    "This is the minimal wxWidgets sample\n"
                    "running under %s.",
                    wxVERSION_STRING,
                    wxGetOsDescription()
                 ),
                 "About wxWidgets minimal sample",
                 wxOK | wxICON_INFORMATION,
                 this);
}

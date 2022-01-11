// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#if !wxUSE_GLCANVAS
    #error "OpenGL required: set wxUSE_GLCANVAS to 1 and rebuild the library"
#endif

#include "cube.h"


/*----------------------------------------------------------------
  Implementation of Test-GLCanvas
-----------------------------------------------------------------*/

BEGIN_EVENT_TABLE(TestGLCanvas, wxGLCanvas)
    EVT_SIZE(TestGLCanvas::OnSize)
    EVT_PAINT(TestGLCanvas::OnPaint)
    EVT_ERASE_BACKGROUND(TestGLCanvas::OnEraseBackground)
    EVT_ENTER_WINDOW( TestGLCanvas::OnEnterWindow )
END_EVENT_TABLE()

TestGLCanvas::TestGLCanvas(wxWindow *parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size, long style, const wxString& name)
    : wxGLCanvas(parent, (wxGLCanvas*) NULL, id, pos, size, 0 , name )
{
    m_init = false;
    m_gllist = 0;
}

TestGLCanvas::TestGLCanvas(wxWindow *parent, const TestGLCanvas *other,
    wxWindowID id, const wxPoint& pos, const wxSize& size, long style,
    const wxString& name )
    : wxGLCanvas(parent, other->GetContext(), id, pos, size, 0, name)
{
    m_init = false;
    m_gllist = other->m_gllist; // share display list
}

TestGLCanvas::~TestGLCanvas()
{
}

void TestGLCanvas::Render()
{
    wxPaintDC dc(this);

#ifndef __WXMOTIF__
    if (!GetContext()) return;
#endif

    SetCurrent();
    // Init OpenGL once, but after SetCurrent
    if (!m_init)
    {
        InitGL();
        m_init = true;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f);
    glMatrixMode(GL_MODELVIEW);

    /* clear color and depth buffers */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if( m_gllist == 0 )
    {
        m_gllist = glGenLists( 1 );
        glNewList( m_gllist, GL_COMPILE_AND_EXECUTE );
        /* draw six faces of a cube */
        glBegin(GL_QUADS);
        glNormal3f( 0.0f, 0.0f, 1.0f);
        glVertex3f( 0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f,-0.5f, 0.5f); glVertex3f( 0.5f,-0.5f, 0.5f);

        glNormal3f( 0.0f, 0.0f,-1.0f);
        glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f(-0.5f, 0.5f,-0.5f);
        glVertex3f( 0.5f, 0.5f,-0.5f); glVertex3f( 0.5f,-0.5f,-0.5f);

        glNormal3f( 0.0f, 1.0f, 0.0f);
        glVertex3f( 0.5f, 0.5f, 0.5f); glVertex3f( 0.5f, 0.5f,-0.5f);
        glVertex3f(-0.5f, 0.5f,-0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);

        glNormal3f( 0.0f,-1.0f, 0.0f);
        glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f( 0.5f,-0.5f,-0.5f);
        glVertex3f( 0.5f,-0.5f, 0.5f); glVertex3f(-0.5f,-0.5f, 0.5f);

        glNormal3f( 1.0f, 0.0f, 0.0f);
        glVertex3f( 0.5f, 0.5f, 0.5f); glVertex3f( 0.5f,-0.5f, 0.5f);
        glVertex3f( 0.5f,-0.5f,-0.5f); glVertex3f( 0.5f, 0.5f,-0.5f);

        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f(-0.5f,-0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, 0.5f,-0.5f);
        glEnd();

        glEndList();
    }
    else
    {
        glCallList(m_gllist);
    }

    glFlush();
    SwapBuffers();
}

void TestGLCanvas::OnEnterWindow( wxMouseEvent& WXUNUSED(event) )
{
    SetFocus();
}

void TestGLCanvas::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
    Render();
}

void TestGLCanvas::OnSize(wxSizeEvent& event)
{
    // this is also necessary to update the context on some platforms
    wxGLCanvas::OnSize(event);

    // set GL viewport (not called by wxGLCanvas::OnSize on all platforms...)
    int w, h;
    GetClientSize(&w, &h);
#ifndef __WXMOTIF__
    if (GetContext())
#endif
    {
        SetCurrent();
        glViewport(0, 0, (GLint) w, (GLint) h);
    }
}

void TestGLCanvas::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
  // Do nothing, to avoid flashing.
}

void TestGLCanvas::InitGL()
{
    SetCurrent();

    /* set viewing projection */
    glMatrixMode(GL_PROJECTION);
    glFrustum(-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f);

    /* position viewer */
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0.0f, 0.0f, -2.0f);

    /* position object */
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(30.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}


/* -----------------------------------------------------------------------
  Main Window
-------------------------------------------------------------------------*/

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
END_EVENT_TABLE()

// My frame constructor
MyFrame::MyFrame(wxWindow *parent, const wxString& title, const wxPoint& pos,
    const wxSize& size, long style)
    : wxFrame(parent, wxID_ANY, title, pos, size, style), aui_manager(this)
{
}

MyFrame::~MyFrame()
{
    aui_manager.UnInit();
}

void MyFrame::init()
{
    // Show the frame


    wxAuiPaneInfo pane_info;

    pane_info.Dockable().MaximizeButton().MinSize(640,480);

    wxWindow *left = new TestGLCanvas(this, wxID_ANY, wxDefaultPosition, wxSize(1024,768));

    wxWindow *right = new TestGLCanvas(this, wxID_ANY, wxDefaultPosition, wxSize(1024,768));

    wxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    sizer->Add(left, 1, wxEXPAND);

    sizer->Add(right, 1, wxEXPAND);

    SetSizerAndFit(sizer);

    aui_manager.AddPane(left, wxAuiPaneInfo(pane_info).Left().Layer(1).Position(1));

    aui_manager.AddPane(right, wxAuiPaneInfo(pane_info).Right().Layer(1).Position(2));

    aui_manager.Update();
}

/*------------------------------------------------------------------
  Application object ( equivalent to main() )
------------------------------------------------------------------ */

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxString str = wxT("wxWidgets OpenGL Cube Sample");

    MyFrame *frame = new MyFrame(NULL, str, wxDefaultPosition, wxSize(1024,768));

   frame->Show();

    frame->init();

    SetTopWindow(frame);

    return true;
}

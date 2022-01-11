// minimal_filedialog_glcanvas_bug.h
// 6/23/2009
// K. Loux

#include <wx/dcclient.h>

#include "minimal_filedialog_glcanvas_bug.h"

// Application entry point ==============================================================
IMPLEMENT_APP(TestApp)

bool TestApp::OnInit()
{
    MainFrame *frame = new MainFrame();
    frame->Show();

    return true;
}

// Main Frame object ====================================================================
MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, _T("Bug Test"), wxDefaultPosition, wxSize(500, 500))
{
    RenderWindow *renwin = new RenderWindow(this, wxID_ANY, wxDefaultPosition, GetSize());
}

// wxGLCanvas object ====================================================================
RenderWindow::RenderWindow(wxWindow *parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size, long style) : wxGLCanvas(
    parent, id, pos, size, style | wxFULL_REPAINT_ON_RESIZE)
{
    Initialized = false;
}

BEGIN_EVENT_TABLE(RenderWindow, wxGLCanvas)
    EVT_PAINT(RenderWindow::OnPaint)
    EVT_ERASE_BACKGROUND(RenderWindow::OnEraseBackground)
    EVT_MOTION(RenderWindow::OnMouseMotion)
END_EVENT_TABLE()

void RenderWindow::Render()
{
    SetCurrent();

    if (!Initialized)
    {
        InitGL();

        // Create file dialog before rendering to demonstrate the bug
        wxFileDialog filedlg(this);
        filedlg.ShowModal();
    }

    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Background color
    glClearColor(0.4f, 0.4f, 0.8f, 1.0f);

    // Draw a triangle
    glMatrixMode(GL_MODELVIEW);

    glNormal3d(0.0, 0.0, 1.0);
    glColor3d(1.0, 0.0, 0.0);

    glBegin(GL_TRIANGLES);
        glVertex3d(1.0, 0.0, 0.0);
        glVertex3d(0.0, 1.0, 0.0);
        glVertex3d(-1.0, 0.0, 0.0);
    glEnd();

    glFlush();
    SwapBuffers();
}

void RenderWindow::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
    wxPaintDC dc(this);
    Render();
}

void RenderWindow::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
    // Do nothing; avoid flashing
}

void RenderWindow::OnMouseMotion(wxMouseEvent& event)
{
    // BUG!!!
    // This event gets triggered when the following is true:
    //   1.  wxFileDialog is on top of the wxGLCanvas
    //   2.  User selects file in dialog box by double clicking
    // These actions should not trigger this event.
    // Not sure if these "clues" are valuable...
    //   The event is NOT triggered if the clicking does not occur over
    //   the canvas area.
    //   The event is NOT triggered if a sub-directory is selected by
    //   double clicking.
    if (event.LeftIsDown())
    {
        glMatrixMode(GL_MODELVIEW);
        glRotated(10.0, 0.0, 0.0, 1.0);
        Render();
    }
}

void RenderWindow::InitGL()
{
    SetCurrent();
    
    glEnable(GL_COLOR_MATERIAL);

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-2.0, 2.0, -2.0, 2.0, 1.0, 5.0);

    // Move the camera back a little bit
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0, 0.0, -1.0);

    Initialized = true;
}
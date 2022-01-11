// minimal_filedialog_glcanvas_bug.h
// 6/23/2009
// K. Loux
#ifndef MINIMAL_FILEDIALOG_GLCANVAS_BUG_H
#define MINIMAL_FILEDIALOG_GLCANVAS_BUG_H

#include <wx/wx.h>
#include <wx/glcanvas.h>

// Application entry point ==============================================================
class TestApp : public wxApp
{
public:
    bool OnInit();
};

DECLARE_APP(TestApp)

// Main Frame object ====================================================================
class MainFrame : public wxFrame
{
public:
    MainFrame();
};

// wxGLCanvas object ====================================================================
class RenderWindow : public wxGLCanvas
{
public:
    RenderWindow(wxWindow *parent, wxWindowID id,
        const wxPoint& pos, const wxSize& size, long style = 0);

    void Render();
    void InitGL();

private:
    void OnPaint(wxPaintEvent& event);
    void OnEraseBackground(wxEraseEvent& event);
    void OnMouseMotion(wxMouseEvent& event);

    bool Initialized;

    DECLARE_EVENT_TABLE()
};


#endif// MINIMAL_FILEDIALOG_GLCANVAS_BUG_H
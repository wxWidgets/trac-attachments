#ifndef _WX_CUBE_H_
#define _WX_CUBE_H_

#include "wx/glcanvas.h"
#include <wx/aui/framemanager.h>

// Define a new application type
class MyApp: public wxApp
{
public:
    bool OnInit();
};

// Define a new frame type
class TestGLCanvas;

class MyFrame: public wxFrame
{
public:

    MyFrame(wxWindow *parent, const wxString& title, const wxPoint& pos,
            const wxSize& size, long style = wxDEFAULT_FRAME_STYLE);

    ~MyFrame();

    void init();

    wxAuiManager aui_manager;

    DECLARE_EVENT_TABLE()
};

#if wxUSE_GLCANVAS

class TestGLCanvas: public wxGLCanvas
{
    friend class MyFrame;
public:
    TestGLCanvas( wxWindow *parent, wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0, const wxString& name = _T("TestGLCanvas") );

    TestGLCanvas( wxWindow *parent, const TestGLCanvas *other,
        wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = 0,
        const wxString& name = _T("TestGLCanvas") );

    ~TestGLCanvas();

    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnEraseBackground(wxEraseEvent& event);
    void OnEnterWindow(wxMouseEvent& event);

    void Render();
    void InitGL();
private:
    bool   m_init;
    GLuint m_gllist;

DECLARE_EVENT_TABLE()
};

#endif // #if wxUSE_GLCANVAS

#endif // #ifndef _WX_CUBE_H_

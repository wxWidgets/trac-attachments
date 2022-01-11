/////////////////////////////////////////////////////////////////////////////
// Name:        shaped.cpp
// Purpose:     Shaped Window sample
// Author:      Robin Dunn
// Modified by:
// Created:     28-Mar-2003
// Copyright:   (c) Robin Dunn
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

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers
#ifndef WX_PRECOMP
    #include "wx/app.h"
    #include "wx/log.h"
    #include "wx/frame.h"
    #include "wx/panel.h"
    #include "wx/stattext.h"
    #include "wx/menu.h"
    #include "wx/layout.h"
    #include "wx/msgdlg.h"
    #include "wx/image.h"
#endif

#include "wx/dcclient.h"
#include "wx/graphics.h"
#include "wx/image.h"

#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "../sample.xpm"
#endif

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// menu ids
enum
{
    Show_Shaped = 100,
};

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
    virtual bool OnInit() wxOVERRIDE;
};


// Main frame just contains the menu items invoking the other tests
class MainFrame : public wxFrame
{
public:
    MainFrame();

private:
    void OnShowShaped(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

class ShapedPanel : public wxPanel
{
public:
    // ctor(s)
    ShapedPanel(wxWindow *parent);
    
    // event handlers (these functions should _not_ be virtual)
    void OnLeftDown(wxMouseEvent& evt);
    void OnLeftUp(wxMouseEvent& evt);
    void OnMouseMove(wxMouseEvent& evt);
    
private:
    wxPoint  m_delta;
    
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};


// Define a new frame type: this is going to the frame showing the
// effect of wxFRAME_SHAPED
class ShapedFrame : public wxFrame
{
public:
    // ctor(s)
    ShapedFrame(wxWindow *parent);

    // event handlers (these functions should _not_ be virtual)
    void OnExit(wxMouseEvent& evt);
    void OnPaint(wxPaintEvent& evt);

private:

    wxBitmap m_bmp;
    
    wxTextCtrl*    m_pText;
    wxButton*      m_pBtn;
    

    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};


// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

IMPLEMENT_APP(MyApp)

// `Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    wxInitAllImageHandlers();

    new MainFrame;

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(Show_Shaped, MainFrame::OnShowShaped)
    EVT_MENU(wxID_EXIT, MainFrame::OnExit)
wxEND_EVENT_TABLE()

MainFrame::MainFrame()
         : wxFrame(NULL, wxID_ANY, "wxWidgets Shaped Sample",
                   wxDefaultPosition, wxSize(200, 100))
{
    SetIcon(wxICON(sample));

    wxMenuBar * const mbar = new wxMenuBar;
    wxMenu * const menuFrames = new wxMenu;
    menuFrames->Append(Show_Shaped, "Show &shaped window\tCtrl-S");
    menuFrames->AppendSeparator();
    menuFrames->Append(wxID_EXIT, "E&xit");

    mbar->Append(menuFrames, "&Show");
    SetMenuBar(mbar);

    Show();
}

void MainFrame::OnShowShaped(wxCommandEvent& WXUNUSED(event))
{
    ShapedFrame *shapedFrame = new ShapedFrame(this);
    shapedFrame->Show(true);
}

void MainFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
    Close();
}

// ----------------------------------------------------------------------------
// shaped panel
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(ShapedPanel, wxPanel)
EVT_LEFT_DOWN(ShapedPanel::OnLeftDown)
EVT_LEFT_UP(ShapedPanel::OnLeftUp)
EVT_MOTION(ShapedPanel::OnMouseMove)
wxEND_EVENT_TABLE()

// panel constructor
ShapedPanel::ShapedPanel(wxWindow *parent)
: wxPanel(parent, wxID_ANY)
{
}

void ShapedPanel::OnLeftDown(wxMouseEvent& evt)
{
    CaptureMouse();
    wxPoint pos = ClientToScreen(evt.GetPosition());
    wxPoint origin = GetParent()->GetPosition();
    int dx =  pos.x - origin.x;
    int dy = pos.y - origin.y;
    m_delta = wxPoint(dx, dy);
}

void ShapedPanel::OnLeftUp(wxMouseEvent& WXUNUSED(evt))
{
    if (HasCapture())
    {
        ReleaseMouse();
    }
}

void ShapedPanel::OnMouseMove(wxMouseEvent& evt)
{
    wxPoint pt = evt.GetPosition();
    if (evt.Dragging() && evt.LeftIsDown())
    {
        wxPoint pos = ClientToScreen(pt);
        GetParent()->Move(wxPoint(pos.x - m_delta.x, pos.y - m_delta.y));
    }
}

// ----------------------------------------------------------------------------
// shaped frame
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(ShapedFrame, wxFrame)
    EVT_RIGHT_UP(ShapedFrame::OnExit)
    EVT_PAINT(ShapedFrame::OnPaint)
wxEND_EVENT_TABLE()


// frame constructor
ShapedFrame::ShapedFrame(wxWindow *parent)
       : wxFrame(parent, wxID_ANY, wxEmptyString,
                  wxDefaultPosition, wxSize(360, 360),
                  0
                  | wxFRAME_SHAPED
                  | wxSIMPLE_BORDER
                  | wxFRAME_NO_TASKBAR
                  | wxSTAY_ON_TOP
				)
{
    m_bmp = wxBitmap(wxT("shape.bmp"), wxBITMAP_TYPE_BMP);
    SetSize(wxSize(m_bmp.GetWidth(), m_bmp.GetHeight()));
    wxColour color(46, 49, 146, 255);
	SetShape(wxRegion(m_bmp, color));
    
    ShapedPanel *panel = new ShapedPanel(this);
    
    m_pText = new wxTextCtrl(panel, wxID_ANY, wxT("Hello World!"), wxPoint(100, 100), wxSize(100, 30), wxTE_READONLY);
    m_pBtn = new wxButton(panel, wxID_ANY, wxT("Click me!"), wxPoint(100, 160), wxSize(100, 30), wxBORDER_NONE);
}

void ShapedFrame::OnExit(wxMouseEvent& WXUNUSED(evt))
{
    Close();
}

void ShapedFrame::OnPaint(wxPaintEvent& WXUNUSED(evt))
{
    wxPaintDC dc(this);
    dc.DrawBitmap(m_bmp, 0, 0, true);
}


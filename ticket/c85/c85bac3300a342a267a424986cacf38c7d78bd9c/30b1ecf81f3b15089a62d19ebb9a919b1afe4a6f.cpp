// ButtonGL_Problem
// This small program demonstrates an incompatibility that exists between wxButton objects
// with coloured backgrounds and wxGLWindows for certain Windows 10 computers.
// Some Windows 10 computers corrected display when wxButton objects have coloured 
// backgrounds, others do not.
// Written by A.W. Bailey, SAIC.
// This program is based on the Cube example program written by Julian Smart.
// The program can be switched between compiling with a wxButton with a coloured
// background and one with a plain background by including or excluding 
// the #define statement below.

#define USE_COLOURED_BUTTON 

#include "ButtonGL_Problem.h"
#include "wx/wxprec.h"
#include "stdafx.h"
#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/panel.h"
#include "wx/button.h"
#include "wx/colour.h"




wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    new MyFrame();

    return true;
}

int MyApp::OnExit()
{
    return wxApp::OnExit();
}



// ----------------------------------------------------------------------------
// MyFrame: main application window
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_NEW, MyFrame::OnNewWindow)
    EVT_MENU(wxID_CLOSE, MyFrame::OnClose)
wxEND_EVENT_TABLE()

MyFrame::MyFrame()
       : wxFrame(NULL, wxID_ANY, wxT("wxWidgets OpenGL Cube Sample"))
{
	SetClientSize(400, 400);
	wxPanel* mypanel = new wxPanel(this, -1, wxDefaultPosition, GetClientSize());
	wxBoxSizer* bs = new wxBoxSizer(wxVERTICAL);
	mypanel->SetSizer(bs);
	wxButton* mybutton = new wxButton(mypanel, -1, "A button");
	bs->Add(mybutton, 0, wxALL, 10);
#ifdef USE_COLOURED_BUTTON
	mybutton->SetBackgroundColour(wxColour(0, 255, 255));
#endif
	CubeCanvas* mycanvas = new CubeCanvas(mypanel);
	bs->Add(mycanvas, 1, wxEXPAND, 0);
	mypanel->Layout();
	mypanel->Refresh();
	mypanel->Update();
	Show();
}


void MyFrame::OnClose(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnNewWindow( wxCommandEvent& WXUNUSED(event) )
{
    new MyFrame();
}

CubeContext::CubeContext(wxGLCanvas* canvas)
	: wxGLContext(canvas)
{

	SetCurrent(*canvas);

	// set up the parameters we want to use
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// add slightly more light, the default lighting is rather dark
	GLfloat ambient[] = { 0.5, 0.5, 0.5, 0.5 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// set viewing projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f);

}

void CubeContext::DrawRotatedCube()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -2.0f);
	glRotatef(30.0, 1.0f, 0.0f, 0.0f);
	glRotatef(30.0, 0.0f, 1.0f, 0.0f);

	// draw six faces of a cube of size 1 centered at (0, 0, 0)
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

	glFlush();

}


BEGIN_EVENT_TABLE(CubeCanvas, wxGLCanvas)
EVT_PAINT(CubeCanvas::OnPaint)
EVT_SIZE(CubeCanvas::OnSize)
END_EVENT_TABLE()


CubeCanvas::CubeCanvas(wxWindow *parent)
// With perspective OpenGL graphics, the wxFULL_REPAINT_ON_RESIZE style
// flag should always be set, because even making the canvas smaller should
// be followed by a paint event that updates the entire canvas with new
// viewport settings.
	: wxGLCanvas(parent, wxID_ANY, NULL,
		wxDefaultPosition, wxDefaultSize,
		//wxDefaultPosition, wxSize(200,200),
		wxFULL_REPAINT_ON_RESIZE)
{
	//SetSize(GetParent()->GetClientSize());
	mpContext = new CubeContext(this);
}

void CubeCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	// This is required even though dc is not used otherwise.
	wxPaintDC dc(this);

	// Set the OpenGL viewport according to the client size of this canvas.
	// This is done here rather than in a wxSizeEvent handler because our
	// OpenGL rendering context (and thus viewport setting) is used with
	// multiple canvases: If we updated the viewport in the wxSizeEvent
	// handler, changing the size of one canvas causes a viewport setting that
	// is wrong when next another canvas is repainted.

	const wxSize ClientSize = GetClientSize();
	//const wxSize ClientSize(500, 500);

	// Render the graphics and swap the buffer
	glViewport(0, 0, ClientSize.x, ClientSize.y);
	mpContext->DrawRotatedCube();


	SwapBuffers();
}

void CubeCanvas::OnSize(wxSizeEvent& event)
{
	//wxSize newsize = GetParent()->GetClientSize();
	//SetSize(newsize);
	event.Skip();
	//Layout();
	//Refresh();
	//Update();
	//SetSize(500, 500);
}




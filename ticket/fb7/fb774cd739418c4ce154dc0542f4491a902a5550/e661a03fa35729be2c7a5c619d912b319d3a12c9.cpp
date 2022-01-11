/*
 * wxGLTest.cpp
 *
 *  Created on: 06.03.2016
 *      Author: david
 */


#include "wxGLTest.h"


#define MAKE_USE_OF_NEW_SYNTAX


// --------------------------------------------------------
// GL Primitive data
// --------------------------------------------------------

typedef struct
{
  GLfloat x;
  GLfloat y;
  GLfloat z;
} GlVertexPos3f;

GlVertexPos3f quadVertices[4] =
{
  {-0.5f, -0.5f,  0.0f},
  { 0.5f, -0.5f,  0.0f},
  { 0.5f,  0.5f,  0.0f},
  {-0.5f,  0.5f,  0.0f}
};


// ----------------------------------------------------
// Gl canvas
// ----------------------------------------------------

GLCanvas::GLCanvas(wxWindow *parent,
 		   const wxGLAttributes &dispAttrs,
		   wxWindowID id,
		   const wxPoint &position,
		   const wxSize &size,
		   long style,
		   const wxString &name,
		   const wxPalette &palette)
:
  wxGLCanvas(parent, dispAttrs, id, position, size, style | wxFULL_REPAINT_ON_RESIZE, name, palette),
  mGLInitialized(false),
  mOrthoFieldOfView(2.0)
{
  this->mViewportSize = this->GetClientSize();
  this->mViewportAspectRatio = ((double)this->mViewportSize.GetX()) / ((double)this->mViewportSize.GetY());

  // create the context
  this->mGLCTX = new wxGLContext(this);

  // bind events
  this->Bind(wxEVT_SIZE, &GLCanvas::OnSize, this);
  this->Bind(wxEVT_PAINT, &GLCanvas::OnPaint, this);
  this->Bind(wxEVT_ERASE_BACKGROUND, &GLCanvas::OnEraseBackground, this);
}

GLCanvas::GLCanvas(wxWindow *parent,
		   wxWindowID id,
		   const int *attribList,
		   const wxPoint &position,
		   const wxSize &size,
		   long style,
		   const wxString &name,
		   const wxPalette &palette)
:
  wxGLCanvas(parent, id, attribList, position, size, style | wxFULL_REPAINT_ON_RESIZE, name, palette),
  mGLInitialized(false),
  mOrthoFieldOfView(2.0)
{
  this->mViewportSize = this->GetClientSize();
  this->mViewportAspectRatio = ((double)this->mViewportSize.GetX()) / ((double)this->mViewportSize.GetY());

  // create the context
  this->mGLCTX = new wxGLContext(this);

  // bind events
  this->Bind(wxEVT_SIZE, &GLCanvas::OnSize, this);
  this->Bind(wxEVT_PAINT, &GLCanvas::OnPaint, this);
  this->Bind(wxEVT_ERASE_BACKGROUND, &GLCanvas::OnEraseBackground, this);
}

GLCanvas::~GLCanvas ()
{
  // unbind events
  this->Unbind(wxEVT_ERASE_BACKGROUND, &GLCanvas::OnEraseBackground, this);
  this->Unbind(wxEVT_PAINT, &GLCanvas::OnPaint, this);
  this->Unbind(wxEVT_SIZE, &GLCanvas::OnSize, this);

  // clean up
  delete this->mGLCTX;
}

void GLCanvas::OnSize (wxSizeEvent& event)
{
  // get the new size of the viewport
  this->mViewportSize = this->GetClientSize();

  // calculate the view aspect ratio
  this->mViewportAspectRatio = ((double)this->mViewportSize.GetX()) / ((double)this->mViewportSize.GetY());
}

void GLCanvas::OnPaint (wxPaintEvent& event)
{
  // wxPaintDC is always needed to enable drawing to a widget
  // as this is allocated in this scope it will automatically deleted at the end of the routine
  wxPaintDC paintDC(this);

  // set the GL context we are using
  this->SetCurrent(*(this->mGLCTX));

  // check if we already initialized GL usage
  if (!this->mGLInitialized)
  {
    this->InitGL();
  }

  // setup the viewport dimensions
  glViewport(0, 0, (GLint)this->mViewportSize.GetX(), (GLint)this->mViewportSize.GetY());


  // Clear
  glClearColor( 0.3f, 0.4f, 0.6f, 1.0f );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


  // setup the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (this->mViewportAspectRatio >= 1.0)
  {
    glOrtho(-(0.5 * this->mOrthoFieldOfView * this->mViewportAspectRatio), (0.5 * this->mOrthoFieldOfView * this->mViewportAspectRatio),
	    -(0.5 * this->mOrthoFieldOfView), (0.5 * this->mOrthoFieldOfView),
	    -1.0, 1.0);
  }
  else
  {
    glOrtho(-(0.5 * this->mOrthoFieldOfView), (0.5 * this->mOrthoFieldOfView),
	  -(0.5 * this->mOrthoFieldOfView / this->mViewportAspectRatio), (0.5 * this->mOrthoFieldOfView / this->mViewportAspectRatio),
	  -1.0, 1.0);
  }



  // setup the model view matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Transformations


  // Primitives

  glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); glVertex3fv(&quadVertices[0].x);
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f); glVertex3fv(&quadVertices[1].x);
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f); glVertex3fv(&quadVertices[2].x);
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); glVertex3fv(&quadVertices[3].x);
  glEnd();

  // Flush
  glFlush();

  // Swap
  SwapBuffers();

}

void
GLCanvas::OnEraseBackground (wxEraseEvent& event)
{
  // Do nothing, to avoid flashing on MSW
}


void GLCanvas::InitGL ()
{
  // setup render pipeline
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_DITHER);

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
  glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
  glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
  glHint(GL_FOG_HINT, GL_FASTEST);
  glHint(GL_GENERATE_MIPMAP_HINT, GL_FASTEST);
  glHint(GL_TEXTURE_COMPRESSION_HINT, GL_FASTEST);
  glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
  glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT, GL_DONT_CARE);

  glShadeModel(GL_SMOOTH);


  this->mGLInitialized = true;
}

// ----------------------------------------------------
// Main window based on wxFrame
// ----------------------------------------------------

MainWindow::MainWindow (wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
:
  wxFrame(parent, id, title, pos, size, style, name)
{
  wxMenuItem *menuFileExit;

  this->SetSizeHints(wxDefaultSize, wxDefaultSize);

  this->mStatusBar = this->CreateStatusBar(1, wxSTB_DEFAULT_STYLE, wxID_ANY);

  this->mMainMenuBar = new wxMenuBar(0);

  this->mMenuFile = new wxMenu();
  menuFileExit = new wxMenuItem(this->mMenuFile, wxID_ANY, wxString(wxT("E&xit")), wxString(wxT("Close the Application")), wxITEM_NORMAL);
  this->mMenuFile->Append(menuFileExit);

  this->mMainMenuBar->Append(this->mMenuFile, wxString(wxT("&File")));

  this->SetMenuBar(this->mMainMenuBar);

  this->Center(wxBOTH);

  this->Bind(wxEVT_COMMAND_MENU_SELECTED, &MainWindow::OnMenuFileExit, this, menuFileExit->GetId());

  this->Show(true);


#ifdef MAKE_USE_OF_NEW_SYNTAX
  wxGLAttributes glAttributes;

  glAttributes.Defaults().RGBA().DoubleBuffer().Depth(16).Stencil(8).SampleBuffers(1).Samplers(4).EndList();

  this->mGLCanvas = new GLCanvas(this, glAttributes, wxID_ANY, wxDefaultPosition, this->GetClientSize(), wxBORDER_SUNKEN);
#else

  const int glAttribList[] =
  {
      WX_GL_RGBA,
      WX_GL_DOUBLEBUFFER,
      WX_GL_DEPTH_SIZE, 16,
      WX_GL_STENCIL_SIZE, 8,
      WX_GL_SAMPLE_BUFFERS, 1,
      WX_GL_SAMPLES, 4,
      0, 0 // end of list
  };

  this->mGLCanvas = new GLCanvas(this, wxID_ANY, glAttribList, wxDefaultPosition, this->GetClientSize(), wxBORDER_SUNKEN);
#endif // MAKE_USE_OF_NEW_SYNTAX

}

MainWindow::~MainWindow ()
{
  this->Unbind(wxEVT_COMMAND_MENU_SELECTED, &MainWindow::OnMenuFileExit, this, wxID_ANY);
}

void MainWindow::OnMenuFileExit (wxCommandEvent& event)
{
  this->Close(true);
}

// ----------------------------------------------------
// APPLICATION
// ----------------------------------------------------

IMPLEMENT_APP(Application)

bool Application::OnInit (void)
{
  if (!wxApp::OnInit()) return false;

  MainWindow *mainWindow;

  mainWindow = new MainWindow(NULL, wxID_ANY, wxString(wxT("OpenGL-Test")), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE);


  mainWindow->Show(true);

  return true;
}


/*
 * wxGLTest.h
 *
 *  Created on: 06.03.2016
 *      Author: david
 */

#ifndef WXGLTEST_H_
#define WXGLTEST_H_

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/frame.h>
#include <wx/statusbr.h>
#include <wx/menu.h>
#include <wx/glcanvas.h>

// ----------------------------------------------------
// APPLICATION
// ----------------------------------------------------

class Application : public wxApp
{
public:
  virtual bool OnInit();
};


// ----------------------------------------------------
// Gl canvas
// ----------------------------------------------------

class GLCanvas : public wxGLCanvas
{
public:
  GLCanvas(wxWindow *parent,
	   const wxGLAttributes &dispAttrs,
	   wxWindowID id = wxID_ANY,
	   const wxPoint &position = wxDefaultPosition,
	   const wxSize &size = wxDefaultSize,
	   long style = 0,
	   const wxString &name = wxGLCanvasName,
	   const wxPalette &palette = wxNullPalette);

  GLCanvas(wxWindow *parent,
	   wxWindowID id = wxID_ANY,
	   const int *attribList = NULL,
	   const wxPoint &position = wxDefaultPosition,
	   const wxSize &size = wxDefaultSize,
	   long style = 0,
	   const wxString &name = wxGLCanvasName,
	   const wxPalette &palette = wxNullPalette);

  virtual ~GLCanvas();

protected:
  void OnSize(wxSizeEvent &event);
  void OnPaint(wxPaintEvent &event);
  void OnEraseBackground(wxEraseEvent &event);

  void InitGL();

  wxGLContext *mGLCTX;
  bool mGLInitialized;
  wxSize mViewportSize;
  double mViewportAspectRatio;
  double mOrthoFieldOfView;
};

// ----------------------------------------------------
// Main window based on wxFrame
// ----------------------------------------------------

class MainWindow : public wxFrame
{
public:
  MainWindow (wxWindow *parent,
	      wxWindowID id,
	      const wxString &title,
	      const wxPoint &position = wxDefaultPosition,
	      const wxSize &size = wxDefaultSize,
	      long style = wxDEFAULT_FRAME_STYLE,
	      const wxString &name = wxFrameNameStr);
  virtual ~MainWindow();

protected:
  virtual void OnMenuFileExit(wxCommandEvent &event);

  wxStatusBar *mStatusBar;
  wxMenuBar   *mMainMenuBar;
  wxMenu      *mMenuFile;

  GLCanvas    *mGLCanvas;
};

#endif /* WXGLTEST_H_ */

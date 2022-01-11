// ButtonGL_Problem
// This small program demonstrates an incompatibility that exists between wxButton objects
// with coloured backgrounds and wxGLWindows for certain Windows 10 computers.
// Some Windows 10 computers corrected display when wxButton objects have coloured 
// backgrounds, others do not.
// Written by A.W. Bailey, SAIC.
// This program is based on the Cube example program written by Julian Smart.

#ifndef _WX_CUBE_H_
#define _WX_CUBE_H_

#include "wx/glcanvas.h"
#include "wx/panel.h"
#include "wx/frame.h"

// Define a new application type
class MyApp : public wxApp
{
public:
    MyApp() 
	{ 
	
	}

    // virtual wxApp methods
    virtual bool OnInit() wxOVERRIDE;
	virtual int OnExit() wxOVERRIDE;
};



// Define a new frame type
class MyFrame : public wxFrame
{
public:
    MyFrame();

private:
    void OnClose(wxCommandEvent& event);
	void OnNewWindow(wxCommandEvent& event);

	DECLARE_EVENT_TABLE()
};

class CubeContext : public wxGLContext
{
public:
	CubeContext(wxGLCanvas* canvas);


	// render the cube showing it at given angles
	void DrawRotatedCube();
};


class CubeCanvas : public wxGLCanvas
{
public:
	CubeCanvas(wxWindow *parent);

	void setCurrent()
	{
		mpContext->SetCurrent(*this);
	}

private:
	CubeContext* mpContext;
	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);

	DECLARE_EVENT_TABLE()
};



#endif // _WX_CUBE_H_

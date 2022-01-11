#include "wx/wx.h"

#include "wx/dialog.h"
#include "wx/notebook.h"
#include "wx/stattext.h"
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/glcanvas.h>


class MyDialog: public wxDialog
{
    public:
        MyDialog();


DECLARE_EVENT_TABLE()
};

class MyApp : public wxApp
{
    public:
        virtual bool OnInit();
};

bool MyApp::OnInit()
{
    MyDialog dlg;
    dlg.ShowModal();
    return false;
}

IMPLEMENT_APP(MyApp)

class MyGLCanvas : public wxGLCanvas
{
public:
     MyGLCanvas(wxWindow* parent, float r, float g, float b);
     void OnPaint(wxPaintEvent& event);
     void OnEraseBackground(wxEraseEvent& event);

private:
    float m_r;
    float m_g;
    float m_b;
    wxGLContext *m_context;
DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyGLCanvas, wxGLCanvas)
    EVT_PAINT(MyGLCanvas::OnPaint)
    EVT_ERASE_BACKGROUND(MyGLCanvas::OnEraseBackground)
END_EVENT_TABLE()


MyGLCanvas::MyGLCanvas(wxWindow* parent, float r, float g, float b) : 
    wxGLCanvas(parent, wxID_ANY, NULL, wxDefaultPosition), m_r(r), m_g(g), m_b(b)
{
    m_context = new wxGLContext( this );
}

void MyGLCanvas::OnPaint(wxPaintEvent& event)
{   
    wxPaintDC dc(this);
    SetCurrent( *m_context );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(m_r, m_g, m_b, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glFlush();
    SwapBuffers();
}

void  MyGLCanvas::OnEraseBackground(wxEraseEvent& event)
{
}

BEGIN_EVENT_TABLE(MyDialog, wxDialog )
END_EVENT_TABLE()

MyDialog::MyDialog() : wxDialog(NULL, wxID_ANY, _("MAC wxGLCanvas bug demo"),
		wxDefaultPosition, wxSize(640, 480), wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX)
{
    wxBoxSizer* itemBoxSizerV = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(itemBoxSizerV);

    wxNotebook* itemNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxSize(512, 384), wxCLIP_CHILDREN );

    itemBoxSizerV->Add(itemNotebook, 1, wxGROW|wxALL, 5);

	wxStaticText* text = new wxStaticText(this, wxID_ANY, 
			_("On MAC wxNotebook updates are broken until the last(blue) tab is activated"));
	
    itemBoxSizerV->Add(text, 0, wxGROW|wxALL, 5);
	
    wxBoxSizer* itemBoxSizerH = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizerV->Add(itemBoxSizerH, 0, wxALIGN_RIGHT|wxALL, 5);

    wxButton* itemButton = new wxButton( this, wxID_CANCEL, _("&Close"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizerH->Add(itemButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);

    MyGLCanvas* glCanvas;
    wxPanel* panel;
    wxBoxSizer *topSizer;
    
    // red
    panel = new wxPanel(itemNotebook, wxID_ANY);
    topSizer = new wxBoxSizer(wxVERTICAL);
    glCanvas = new MyGLCanvas(panel, 255.f, 0, 0);
    topSizer->Add(glCanvas, 1, wxEXPAND);
    panel->SetSizer(topSizer);
    itemNotebook->AddPage(panel, _("RedGlCanvas"));
    
    // green
    panel = new wxPanel(itemNotebook, wxID_ANY);
    topSizer = new wxBoxSizer(wxVERTICAL);
    glCanvas = new MyGLCanvas(panel, 0, 255.f, 0);
    topSizer->Add(glCanvas, 1, wxEXPAND);
    panel->SetSizer(topSizer);
    itemNotebook->AddPage(panel, _("GreenGlCanvas"));
    
    // blue
    panel = new wxPanel(itemNotebook, wxID_ANY);
    topSizer = new wxBoxSizer(wxVERTICAL);
    glCanvas = new MyGLCanvas(panel, 0, 0, 255.f);
    topSizer->Add(glCanvas, 1, wxEXPAND);
    panel->SetSizer(topSizer);
    itemNotebook->AddPage(panel, _("BlueGlCanvas"));

    // old: works without wxPanel
    //glCanvas = new MyGLCanvas(itemNotebook, 255.f, 0, 0);
    //itemNotebook->AddPage(glCanvas, _("RedGlCanvas"));

    //glCanvas = new MyGLCanvas(itemNotebook, 0, 255.f, 0);
    //itemNotebook->AddPage(glCanvas, _("GreenGlCanvas"));
    
    //glCanvas = new MyGLCanvas(itemNotebook, 0, 0, 255.f);
    //itemNotebook->AddPage(glCanvas , _("BlueGlCanvas"));
}


 	  	 

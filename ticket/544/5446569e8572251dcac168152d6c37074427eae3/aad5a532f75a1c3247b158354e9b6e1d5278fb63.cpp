
#include <wx/wx.h>
#include <wx/glcanvas.h>

// Define a new application type
class MyApp: public wxApp
{
public:
    bool OnInit();
};

class TestGLCanvas: public wxGLCanvas
{
private:
	GLfloat xrot;
	GLfloat yrot;

public:
    TestGLCanvas(wxWindow *parent, wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = 0,
        const wxString& name = _T("TestGLCanvas"), int *gl_attrib = NULL);

   ~TestGLCanvas(){};

    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);

    DECLARE_EVENT_TABLE()
};


class MyFrame: public wxFrame
{
public:
    MyFrame(wxFrame *frame, const wxString& title, const wxPoint& pos,
        const wxSize& size, long style = wxDEFAULT_FRAME_STYLE);

    virtual ~MyFrame() {}

	wxPanel* left;
	wxPanel* right;
	wxButton* button;
    TestGLCanvas* canvas;

private :

    void OnButton(wxCommandEvent& event);

DECLARE_EVENT_TABLE()
};


static GLfloat verts[3][3] = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};

static void draw_surface()
{
    GLint i;
    {
        glBegin( GL_TRIANGLE_STRIP );
        for (i=0;i<3;i++)
        {
            glVertex3fv( verts[i] );
        }
        glEnd();
    }
}

static void draw(GLfloat xrot, GLfloat yrot)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum( -1.0, 1.0, -1.0, 1.0, 5.0, 25.0 );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef( 0.0, 0.0, -6.0 );



    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glPushMatrix();
    glRotatef( yrot, 0.0f, 1.0f, 0.0f );
    glRotatef( xrot, 1.0f, 0.0f, 0.0f );

    draw_surface();

    glPopMatrix();

    glFlush();
}



// The following part was written for wxWidgets 1.66
MyFrame *frame = NULL;

IMPLEMENT_APP(MyApp)

// `Main program' equivalent, creating windows and returning main app frame
bool MyApp::OnInit()
{
    // Create the main frame window
    frame = new MyFrame(NULL, "GLCanvas Reparent test", wxDefaultPosition, wxDefaultSize);

	// create the 2 frames and the button
	frame->left = new wxPanel(frame, wxID_ANY);
	frame->right = new wxPanel(frame, wxID_ANY);
	frame->button = new wxButton(frame, 10001, "Reparent");
	wxBoxSizer* s = new wxBoxSizer(wxHORIZONTAL);
	s->Add(frame->left, 1, wxEXPAND);
	s->Add(frame->button, 0, wxEXPAND);
	s->Add(frame->right, 1, wxEXPAND);
	frame->left->SetBackgroundColour(*wxRED);
	frame->right->SetBackgroundColour(*wxGREEN);
	frame->SetSizer(s);


	// create the GL canvas
    int gl_attrib[20] = { WX_GL_RGBA, WX_GL_MIN_RED, 1, WX_GL_MIN_GREEN, 1,
        WX_GL_MIN_BLUE, 1, WX_GL_DEPTH_SIZE, 1,
        WX_GL_DOUBLEBUFFER,
        None };

	frame->canvas = new TestGLCanvas(frame->left, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _T("TestGLCanvas1"), gl_attrib );
	frame->canvas->SetSize(100, 100);

	s->Layout();
    frame->Show(true);

    return true;
}

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON(10001, MyFrame::OnButton)
END_EVENT_TABLE()

MyFrame::MyFrame(wxFrame *frame, const wxString& title, const wxPoint& pos,
    const wxSize& size, long style)
    : wxFrame(frame, wxID_ANY, title, pos, size, style)
{
}

void MyFrame::OnButton( wxCommandEvent& WXUNUSED(event) )
{
	if (left->GetChildren().IsEmpty()) {
		std::cout << "right -> left" << std::endl;
		canvas->Reparent(left);
	}
	else {
		std::cout << "left -> right" << std::endl;
		canvas->Reparent(right);
	}
}

/*
 * TestGLCanvas implementation
 */

BEGIN_EVENT_TABLE(TestGLCanvas, wxGLCanvas)
    EVT_SIZE(TestGLCanvas::OnSize)
    EVT_PAINT(TestGLCanvas::OnPaint)
END_EVENT_TABLE()

TestGLCanvas::TestGLCanvas(wxWindow *parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size, long style,
    const wxString& name, int* gl_attrib)
    : wxGLCanvas(parent, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE, name, gl_attrib)
{
}


void TestGLCanvas::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
    wxPaintDC dc(this);
    SetCurrent();
    draw(xrot, yrot);
    SwapBuffers();
}

void TestGLCanvas::OnSize(wxSizeEvent& event)
{
    wxGLCanvas::OnSize(event);

    int w, h;
    GetClientSize(&w, &h);
	SetCurrent();
	glViewport(0, 0, (GLint) w, (GLint) h);
}


 	  	 

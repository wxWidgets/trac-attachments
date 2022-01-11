#include <stdio.h>
#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <wx/notebook.h>
//#include <wx/glcanvas.h>
#include <GL/glut.h>


class GLpanel : public wxGLCanvas
{
	public:
		GLpanel(wxWindow *parent, /*brainPanel *panel_,*/ wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = _T("GLpanel"),
			int *gl_attrib = NULL)
		: wxGLCanvas(parent,id,pos,size,style,name,gl_attrib)
		{
			std::cout << " GLPanel created" << std::endl;
		}
		~GLpanel() {}
		void Render()
		{
			SetCurrent();

			//wxPaintDC(this);

			glClearColor(0.0, 0.0, 0.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT);
			glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);

				glBegin(GL_POLYGON);
				glColor3f(1.0, 1.0, 1.0);
				glVertex2f(-0.5, -0.5);
				glVertex2f(-0.5, 0.5);
				glVertex2f(0.5, 0.5);
				glVertex2f(0.5, -0.5);
				glColor3f(0.4, 0.5, 0.4);
				glVertex2f(0.0, -0.8);
				glEnd();

				glBegin(GL_POLYGON);
				glColor3f(1.0, 0.0, 0.0);
				glVertex2f(0.1, 0.1);
				glVertex2f(-0.1, 0.1);
				glVertex2f(-0.1, -0.1);
				glVertex2f(0.1, -0.1);
				glEnd();

				// using a little of glut
				glColor4f(0,0,1,1);
				glutWireTeapot(0.4);

				glLoadIdentity();
				glColor4f(2,0,1,1);
				glutWireTeapot(0.6);
				// done using glut
			glFlush();
			SwapBuffers();
		}
		void Paintit(wxPaintEvent& event) { Render(); }

	protected:

		DECLARE_EVENT_TABLE()

};

BEGIN_EVENT_TABLE(GLpanel, wxGLCanvas)
    EVT_PAINT    (GLpanel::Paintit)
END_EVENT_TABLE()

class brainPanel : public wxPanel
{
public:
	brainPanel( wxWindow* parent )
	: wxPanel( parent ) {

		SetSize(wxSize(1068, 768));
			wxBoxSizer* bSizer18;
			bSizer18 = new wxBoxSizer( wxVERTICAL );

			wxNotebook *m_notebook2 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
			wxPanel *m_panel19 = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );

			wxFlexGridSizer* fgSizer63;
			fgSizer63 = new wxFlexGridSizer( 1, 3, 0, 0 );
			fgSizer63->SetFlexibleDirection( wxBOTH );
			fgSizer63->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

			m_panel19->SetSizer( fgSizer63 );
			m_panel19->Layout();
			fgSizer63->Fit( m_panel19 );
			m_notebook2->AddPage( m_panel19, wxT("1"), true );

			wxPanel *m_panel20 = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
			wxFlexGridSizer* fgSizer64;
			fgSizer64 = new wxFlexGridSizer( 1, 3, 0, 0 );
			fgSizer64->SetFlexibleDirection( wxBOTH );
			fgSizer64->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
			m_panel20->SetSizer( fgSizer64 );
			m_panel20->Layout();
			fgSizer64->Fit( m_panel20 );
			m_notebook2->AddPage( m_panel20, wxT("2"), false );

			wxPanel *m_panel21 = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
			wxFlexGridSizer* fgSizer65;
			fgSizer65 = new wxFlexGridSizer( 1, 3, 0, 0 );
			fgSizer65->SetFlexibleDirection( wxBOTH );
			fgSizer65->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
			m_panel21->SetSizer( fgSizer65 );
			m_panel21->Layout();
			fgSizer65->Fit( m_panel21 );
			m_notebook2->AddPage( m_panel21, wxT("3"), false );

			bSizer18->Add( m_notebook2, 1, wxEXPAND | wxALL, 5 );

			button = new wxButton( this, wxID_ANY, wxT("Draw"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT|wxNO_BORDER );
			bSizer18->Add( button, 0, 0, 5 );

			this->SetSizer( bSizer18 );
			this->Layout();

		win1_1 = new GLpanel( m_panel19, -1, wxDefaultPosition, wxSize(300,200), wxRAISED_BORDER );
		fgSizer63->Add( win1_1, 1, wxEXPAND, 5 );
		win1_2 = new GLpanel( m_panel19, -1, wxDefaultPosition, wxSize(300,200), wxRAISED_BORDER  );
		fgSizer63->Add( win1_2, 1, wxEXPAND, 5 );
		win1_3 = new GLpanel( m_panel19, -1, wxDefaultPosition, wxSize(300,200), wxRAISED_BORDER  );
		fgSizer63->Add( win1_3, 1, wxEXPAND, 5 );

		win2_1 = new GLpanel( m_panel20, -1, wxDefaultPosition, wxSize(300,200), wxRAISED_BORDER );
		fgSizer64->Add( win2_1, 1, wxEXPAND, 5 );
		win2_2 = new GLpanel( m_panel20, -1, wxDefaultPosition, wxSize(300,200), wxRAISED_BORDER  );
		fgSizer64->Add( win2_2, 1, wxEXPAND, 5 );
		win2_3 = new GLpanel( m_panel20, -1, wxDefaultPosition, wxSize(300,200), wxRAISED_BORDER  );
		fgSizer64->Add( win2_3, 1, wxEXPAND, 5 );

		win3_1 = new GLpanel( m_panel21, -1, wxDefaultPosition, wxSize(300,200), wxRAISED_BORDER );
		fgSizer65->Add( win3_1, 1, wxEXPAND, 5 );
		win3_2 = new GLpanel( m_panel21, -1, wxDefaultPosition, wxSize(300,200), wxRAISED_BORDER  );
		fgSizer65->Add( win3_2, 1, wxEXPAND, 5 );
		win3_3 = new GLpanel( m_panel21, -1, wxDefaultPosition, wxSize(300,200), wxRAISED_BORDER  );
		fgSizer65->Add( win3_3, 1, wxEXPAND, 5 );

		button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( brainPanel::Activate ), NULL, this );
	}
	~brainPanel() {
		button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( brainPanel::Activate ), NULL, this );
	}
	
	void Activate(wxCommandEvent& event)
	{
			std::cout << " win1_1" << std::endl; win1_1->Render();
			std::cout << " win1_2" << std::endl; win1_2->Render();
			std::cout << " win1_3" << std::endl; win1_3->Render();
			std::cout << " win2_1" << std::endl; win2_1->Render();
			std::cout << " win2_2" << std::endl; win2_2->Render();
			std::cout << " win2_3" << std::endl; win2_3->Render();
			std::cout << " win3_1" << std::endl; win3_1->Render();
			std::cout << " win3_2" << std::endl; win3_2->Render();
			std::cout << " win3_3" << std::endl; win3_3->Render();
	}

protected:
	GLpanel *win1_1, *win1_2, *win1_3, *win2_1, *win2_2, *win2_3, *win3_1, *win3_2, *win3_3;
	wxButton *button;

};

class brainFrame : public wxFrame
{
public:
	brainFrame( wxWindow *parent = NULL, int id = -1 )
	: wxFrame( parent, id , wxT("Test for wxGLCanvas"), wxDefaultPosition, wxDefaultSize)
	{
		SetSize(wxSize(1068, 768));
		wxBoxSizer* sizer = new wxBoxSizer( wxHORIZONTAL );
		brainPanel *panel = new brainPanel( this );
		sizer->Add( panel, 1, wxEXPAND);
    		SetSizer(sizer);
    		SetAutoLayout(true);
	}

	~brainFrame()
	{
	}
};


class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

IMPLEMENT_APP( MyApp );

bool MyApp::OnInit()
{
	int argc = 1;
	char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str() };
	glutInit(&argc, argv);

	brainFrame* frame = new brainFrame();
	frame->Centre();
	frame->Show();
	return true;
}

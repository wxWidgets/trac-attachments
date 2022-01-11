
#include <wx/wx.h>
#include <wx/glcanvas.h>

wxGLContext* context = NULL;

class TestCanvas : public wxGLCanvas {
private:
	wxColour colour;

public:
	TestCanvas(wxWindow* parent, wxColour colour) : wxGLCanvas(parent, -1, NULL) {
		this->colour = colour;

		// Bind paint event
		Bind(wxEVT_PAINT, &TestCanvas::onPaint, this);
	}
	~TestCanvas() {}

	void onPaint(wxPaintEvent& e) {
		wxPaintDC(this);

		// Create context if needed
		if (!context)
			context = new wxGLContext(this);

		// Set context
		context->SetCurrent(*this);

		// Setup opengl things
		glViewport(0, 0, GetSize().x, GetSize().y);
		glClearColor((float)colour.Red()/255.0f, (float)colour.Green()/255.0f, (float)colour.Blue()/255.0f, 1.0f);

		// Projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, GetSize().x, GetSize().y, 0, -1, 100);

		// View
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glClear(GL_COLOR_BUFFER_BIT);
		SwapBuffers();
	}
};

class MainWindow : public wxFrame {
private:
	TestCanvas* test_canvas;
	wxButton*	btn_toggle;

public:
	MainWindow() : wxFrame(NULL, -1, "GLCanvas Test") {
		// Create widgets
		wxPanel* panel = new wxPanel(this, -1);
		test_canvas = new TestCanvas(panel, wxColour(255, 0, 0));
		btn_toggle = new wxButton(this, -1, "Toggle");
		
		// Setup layout
		panel->SetInitialSize(wxSize(500, 500));
		wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
		SetSizer(sizer);
		sizer->Add(panel, 1, wxEXPAND|wxALL, 4);
		sizer->Add(btn_toggle, 0, wxALL, 4);
		
		sizer = new wxBoxSizer(wxVERTICAL);
		panel->SetSizer(sizer);
		sizer->Add(test_canvas, 1, wxEXPAND);
		
		// Bind events
		btn_toggle->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::onBtnToggle, this);

		Layout();
	}
	~MainWindow() {}
	
	void onBtnToggle(wxCommandEvent& e) {
		if (test_canvas->IsShown())
			test_canvas->Show(false);
		else
			test_canvas->Show(true);
		
		Layout();
		Update();
		Refresh();
	}
};

class wxMiniApp : public wxApp {
public:
	virtual bool OnInit();
	void OnClick(wxCommandEvent& event) { GetTopWindow()->Close(); }
};

IMPLEMENT_APP(wxMiniApp);

bool wxMiniApp::OnInit() {
    SetTopWindow(new MainWindow());
    GetTopWindow()->Show();

    return true;
}

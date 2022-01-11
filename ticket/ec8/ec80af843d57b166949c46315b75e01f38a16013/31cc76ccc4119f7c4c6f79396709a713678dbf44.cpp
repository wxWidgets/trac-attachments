

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// Define a new frame type: this is going to be our main frame
class MainWindow : public wxFrame
{
public:
    // ctor(s)
    MainWindow();

    void initAndCreate(void);
};


// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MyApp)


// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;

    // create the main application window
    MainWindow *frame = new MainWindow;
    frame->initAndCreate();

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}


// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MainWindow::MainWindow() : wxFrame(NULL, wxID_ANY, "")
{
}

void 
MainWindow::initAndCreate(void)
{
    Show(true);
	Maximize();
    SetIcon(wxICON(sample));
    SetTitle("Bug wxTextCtrl");

    //Main panel
	wxPanel *panel = new wxPanel(this);
	panel->SetSize(GetClientSize());

    wxBoxSizer *sizerCol = new wxBoxSizer(wxVERTICAL);
    
    wxTextCtrl *textLog = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    char txt[1000];
    for (int i = 0; i < 150; i++) {
    	sprintf(txt, "[%3d] ", i);
    	textLog->AppendText(txt);
        textLog->AppendText("aaazzzeeerrrtttaaazzzeeerrrtttaaazzzeeerrrtttaaazzzeeerrrtttyyyaaazzzeeerrrtttaaazzzeeerrrttteerrraaazzzeeerrraaazzzeeerrraaazzzeeerrraaazzzeeerrrtttaaazzzeeerrrtttaaazzzzeeerrrtttaaazzzeeerrrtttaaazzzeeerrrtttaaazzz\n");
    }


    sizerCol->Add(textLog, 1, wxGROW | wxALL, 10);
    
    
    panel->SetSizer(sizerCol);
    panel->Layout();

    Refresh();
    Update();
}




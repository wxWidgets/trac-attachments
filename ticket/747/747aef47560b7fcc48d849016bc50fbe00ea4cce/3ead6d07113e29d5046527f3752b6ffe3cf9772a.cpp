/////////////////////////////////////////////////////////////////////////////
// Name:        minimal.cpp
// Purpose:     Minimal wxWidgets sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/notebook.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif


// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows it is in resources and even
// though we could still include the XPM here it would be unused)
//#ifndef wxHAS_IMAGES_IN_RESOURCES
//#include "../sample.xpm"
//#endif

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
    virtual bool OnInit() override;
};

class MyPanel : public wxScrolledWindow
{
public:
    MyPanel(wxWindow * parent,
            wxWindowID id = wxID_ANY,
            const wxPoint & pos = wxDefaultPosition,
            const wxSize & size = wxDefaultSize,
            long style = wxHSCROLL|wxVSCROLL,
            const wxString & name = "scrolledWindow") : wxScrolledWindow(parent, id, pos, size, style, name)
    {
        SetScrollRate(10, 10);

        wxBoxSizer * pSizer_0 = new wxBoxSizer(wxHORIZONTAL);

        wxGrid * pGrid = new wxGrid(this, wxID_ANY);
        int rows = 100;
        int cols = 100;
        pGrid->CreateGrid(rows, cols);
        for (int row = 0; row < rows; ++row)
        {
            for (int col = 0; col < cols; ++col)
            {
                pGrid->SetCellValue("Test", row, col);
            }
        }


        pSizer_0->Add(pGrid, 1, wxEXPAND);

        SetSizer(pSizer_0);
    }
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString & title);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent & event);
    void OnAbout(wxCommandEvent & event);
private:
private:
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(Minimal_Quit, MyFrame::OnQuit)
EVT_MENU(Minimal_About, MyFrame::OnAbout)
wxEND_EVENT_TABLE()

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
wxIMPLEMENT_APP(MyApp);

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if (!wxApp::OnInit())
        return false;

    // create the main application window
    MyFrame * frame = new MyFrame("Minimal wxWidgets App");

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)

    frame->SetSize(400, 300);

    frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString & title)
    : wxFrame(NULL, wxID_ANY, title)
{
    // set the frame icon
//    SetIcon(wxICON(sample));

    #if wxUSE_MENUS
    // create a menu bar
    wxMenu * fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu * helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, "&About\tF1", "Show about dialog");

    fileMenu->Append(Minimal_Quit, "E&xit\tAlt-X", "Quit this program");

    // now append the freshly created menu to the menu bar...
    wxMenuBar * menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
    #else // !wxUSE_MENUS
    // If menus are not available add a button to access the about box
    wxSizer * sizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton * aboutBtn = new wxButton(this, wxID_ANY, "About...");
    aboutBtn->Bind(wxEVT_BUTTON, &MyFrame::OnAbout, this);
    sizer->Add(aboutBtn, wxSizerFlags().Center());
    SetSizer(sizer);
    #endif // wxUSE_MENUS/!wxUSE_MENUS

    #if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText("Welcome to wxWidgets!");
    #endif // wxUSE_STATUSBAR

    wxBoxSizer * pSizer_0 = new wxBoxSizer(wxHORIZONTAL);

    {
        wxNotebook * pNB = new wxNotebook(this, wxID_ANY);
        {
            wxPanel * pPage = new wxPanel(pNB, wxID_ANY);
            {
                wxBoxSizer * pSizer_0_0 = new wxBoxSizer(wxHORIZONTAL);
                {
                    MyPanel * pPanel = new MyPanel(pPage, wxID_ANY);
                    pSizer_0_0->Add(pPanel, 1, wxEXPAND);
                }
                pPage->SetSizer(pSizer_0_0);
            }
            pNB->InsertPage(0, pPage, "Test Page", true);
        }
        pSizer_0->Add(pNB, 1, wxEXPAND);

        {
            wxBoxSizer * pSizer_0_0 = new wxBoxSizer(wxVERTICAL);
            pSizer_0_0->Add(new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(100, 30)));
            pSizer_0_0->Add(new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(100, 30)));
            pSizer_0_0->Add(new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(100, 30)));
            pSizer_0_0->Add(new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(100, 30)));
            pSizer_0->Add(pSizer_0_0);
        }
    }

    SetSizer(pSizer_0);
}


// event handlers

void MyFrame::OnQuit(wxCommandEvent & WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent & WXUNUSED(event))
{
    wxMessageBox(wxString::Format
    (
        "Welcome to %s!\n"
        "\n"
        "This is the minimal wxWidgets sample\n"
        "running under %s.",
        wxVERSION_STRING,
        wxGetOsDescription()
    ),
                 "About wxWidgets minimal sample",
                 wxOK | wxICON_INFORMATION,
                 this);
}

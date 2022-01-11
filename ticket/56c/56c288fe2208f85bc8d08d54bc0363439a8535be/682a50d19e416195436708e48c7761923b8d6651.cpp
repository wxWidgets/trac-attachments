// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/grid.h>

#include <exception>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
    virtual void OnUnhandledException() override;
    virtual bool OnExceptionInMainLoop() override;
};
class MyFrame : public wxFrame
{
public:
    MyFrame();
private:
    void OnExit(wxCommandEvent& event);
    void OnCharHook(wxKeyEvent& event);
    void OnChar(wxKeyEvent& event);
};
enum
{
    ID_Hello = 1
};

wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}


void MyApp::OnUnhandledException()
{
    wxMessageBox("Unhandled Exception", "Unhandled Exception");
}

bool MyApp::OnExceptionInMainLoop()
{
    wxMessageBox("Exception in MainLoop", "Exception in Main Loop");
    return true;
}

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "wxGrid")
{
    wxGrid* grid = new wxGrid(this, wxID_ANY);
    grid->Bind(wxEVT_CHAR_HOOK, &MyFrame::OnCharHook, this);
    grid->Bind(wxEVT_CHAR, &MyFrame::OnChar, this);
}
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnCharHook(wxKeyEvent& event)
{
    if (event.GetKeyCode() == 'E')
    {
        throw std::runtime_error("EXCEPTION IN OnCharHook!");
    }
    event.Skip();
}

void MyFrame::OnChar(wxKeyEvent& event)
{
    if (event.GetKeyCode() == 'x')
    {
        throw std::runtime_error("EXCEPTION IN OnChar!");
    }
    event.Skip();
}
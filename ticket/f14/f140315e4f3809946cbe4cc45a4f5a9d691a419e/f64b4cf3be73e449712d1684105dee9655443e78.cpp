#include <wx/wx.h>

class Test : protected wxFrame
{
public:
    Test();

private:
    void close(wxCloseEvent& event);
    void sizing(wxSizeEvent& event);

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(Test, wxFrame)
    EVT_CLOSE(Test::close)
wxEND_EVENT_TABLE()

Test::Test() : wxFrame(NULL, wxID_ANY, "Test")
{
    Bind(wxEVT_SIZING, &Test::sizing, this);
    Show();
}

void Test::sizing(wxSizeEvent& event)
{
    printf("Sizing");
}

void Test::close(wxCloseEvent& event)
{
    printf("Closing");
}

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    Test* frame = new Test();
    return true;
}
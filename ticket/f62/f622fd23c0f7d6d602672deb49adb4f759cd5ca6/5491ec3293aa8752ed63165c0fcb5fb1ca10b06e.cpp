#include <wx/wx.h>

class MyApp : public wxApp
{
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnMouseWheel(wxMouseEvent& event);
private:
    wxPanel *panel;
};

bool MyApp::OnInit()
{
    new MyFrame(_("Move the red box with mouse wheel"), wxPoint(100, 100), wxSize(500, 500));
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
    new wxStaticText(this, wxID_ANY, "", wxPoint(0, 0));
    panel = new wxPanel(this, wxID_ANY, wxPoint(225, 225), wxSize(50, 50), wxSIMPLE_BORDER);
    panel->SetBackgroundColour("RED");

    Bind(wxEVT_MOUSEWHEEL, &MyFrame::OnMouseWheel, this);
    Show();
}

void MyFrame::OnMouseWheel(wxMouseEvent& event)
{
    /*wxLogMessage("Axis: %s, rotation: %d",
        event.GetWheelAxis() == wxMOUSE_WHEEL_VERTICAL ? "vert" : "horz",
        event.GetWheelRotation());*/

    int offset = event.GetWheelRotation() > 0 ? 10 : -10;
    wxPoint pos = panel->GetPosition();
    if (event.GetWheelAxis() == wxMOUSE_WHEEL_VERTICAL)
        pos.y -= offset; // positive offset is up, negative is down (Windows/Linux convention)
    else
        pos.x += offset; // positive offset is right, negative is left (Windows/Linux convention)
    panel->Move(pos);
}

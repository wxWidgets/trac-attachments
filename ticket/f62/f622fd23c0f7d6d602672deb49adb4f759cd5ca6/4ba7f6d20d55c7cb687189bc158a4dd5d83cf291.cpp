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
    MyFrame *frame = new MyFrame(_("Move the white box with mouse wheel"), wxPoint(100, 100), wxSize(500, 500));
    frame->Connect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(MyFrame::OnMouseWheel));
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, -1, title, pos, size)
{
    wxPanel *parent = new wxPanel(this, wxID_ANY);
    panel = new wxPanel(parent, wxID_ANY, wxPoint(225, 225), wxSize(50, 50), wxSIMPLE_BORDER);
    panel->SetBackgroundColour("WHITE");
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

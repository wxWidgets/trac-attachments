#include <wx/wx.h>
class CApp : public wxApp
{
public:
    bool OnInit() {
        // Create the main frame.
        wxFrame * frame = new wxFrame(NULL, wxID_ANY, wxEmptyString);
        frame->SetCursor(*wxCROSS_CURSOR);
        frame->SetBackgroundColour(wxColor(0x00, 0x33, 0x00));
        // Create two child windows for comparison.
        wxWindow * child = new wxWindow(frame, wxID_ANY, wxPoint(10, 10), wxSize(300, 60));
        child->SetCursor(*wxHOURGLASS_CURSOR);
        new wxWindow(frame, wxID_ANY, wxPoint(10, 100), wxSize(300, 60)); // This one is supposed to inherit the cursor, but it in reality will not.
        // Enter the message loop.
        frame->Centre(wxBOTH);
        frame->Show(true);
        return true;
    }
};
DECLARE_APP(CApp)
IMPLEMENT_APP(CApp)

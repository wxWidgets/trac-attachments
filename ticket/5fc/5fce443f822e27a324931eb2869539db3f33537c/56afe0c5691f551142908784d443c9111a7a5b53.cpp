
#include <wx/wx.h>

class MyFrame : public wxFrame
{
public:

    MyFrame(wxWindow* parent,
            wxWindowID id,
            const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxDEFAULT_FRAME_STYLE)
        : wxFrame(parent, id, title, pos, size, style) { }

private:

    void OnMove(wxMoveEvent& event)
    {
        printf("OnMove()\n");
    }

    void OnLeftDown(wxMouseEvent& event)
    {
        Show(true);
    }

    DECLARE_EVENT_TABLE();
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MOVE(MyFrame::OnMove)
    EVT_LEFT_DOWN(MyFrame::OnLeftDown)
END_EVENT_TABLE()



class MyApp : public wxApp
{
public:
    bool OnInit()
    {
        wxFrame* frame = new MyFrame(NULL,
                                     wxID_ANY,
                                     wxT("Test"),
                                     wxDefaultPosition,
                                     wxSize(200, 200));
        SetTopWindow(frame);
        frame->Show();
        return true;
    }
};

DECLARE_APP(MyApp);
IMPLEMENT_APP(MyApp);


 	  	 

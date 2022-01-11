#include "wx/wx.h"

class StaticTextCtrl : public wxStaticText
{
public:
    StaticTextCtrl(wxWindow *parent, const wxString& label) : wxStaticText(parent, wxID_ANY, label) {}

    void onMouseLeftUp(wxMouseEvent& event);
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(StaticTextCtrl, wxStaticText)
EVT_LEFT_UP(StaticTextCtrl::onMouseLeftUp)
wxEND_EVENT_TABLE()

void StaticTextCtrl::onMouseLeftUp(wxMouseEvent& WXUNUSED(event))
{
    this->SetForegroundColour(wxColour(rand() % 255, rand() % 255, rand() % 255));
    //this->Refresh(); //the issue is gone with these calls of repainting
    //this->Update();
}

class StatusBar : public wxStatusBar
{
public:
    StatusBar(wxWindow *parent) : wxStatusBar(parent, wxID_ANY, wxST_SIZEGRIP | wxFULL_REPAINT_ON_RESIZE, "App Status Bar")
    {
        pStTxt = new StaticTextCtrl(this, "Status bar pane text foreground colour");
        pStTxt->SetBackgroundColour(*wxWHITE);
    }
    virtual ~StatusBar()
    {
        delete pStTxt, pStTxt = nullptr;
    }

    StaticTextCtrl* pStTxt;
};

class MainFrame : public wxFrame
{
public:
    MainFrame() : wxFrame((wxWindow *)NULL, -1, "Main Frame", wxDefaultPosition, wxSize(320, 200))
    {
        wxStatusBar *statbarOld = GetStatusBar();

        if (statbarOld)
        {
            SetStatusBar(NULL);
            delete statbarOld;
        }

        StatusBar *sb = new StatusBar(this);
        SetStatusBar(sb);
        PositionStatusBar();
    }
};

class App : public wxApp
{
public:
    virtual bool OnInit()
    {
        MainFrame *pFrame = new MainFrame();
        pFrame->Show(true);
        SetTopWindow(pFrame);
        return true;
    }
};

DECLARE_APP(App)
IMPLEMENT_APP(App)

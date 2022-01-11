// This is a simple application which demonstrates a bug in the
// wxRichText scrolling optimization.

#include "wx/app.h"
#include "wx/event.h"
#include "wx/menu.h"
#include "wx/sizer.h"
#include "wx/frame.h"
#include "wx/richtext/richtextctrl.h"

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title, wxWindowID id);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnScrollToBottom(wxCommandEvent& event);
    void OnSetToLargeText(wxCommandEvent& event);
    void OnSetToSmallText(wxCommandEvent& event);
    void FillWithText(int totalParagraphs);

private:
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();

    wxRichTextCtrl* m_richTextCtrl;
};

wxIMPLEMENT_APP(MyApp);

// IDs for the controls and the menu commands
enum
{
    ID_SCROLL_TO_BOTTOM = 100,
    ID_LARGE_TEXT,
    ID_SMALL_TEXT,
    ID_RICHTEXT_CTRL,
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT,           MyFrame::OnQuit)
    EVT_MENU(ID_SCROLL_TO_BOTTOM, MyFrame::OnScrollToBottom)
    EVT_MENU(ID_LARGE_TEXT,       MyFrame::OnSetToLargeText)
    EVT_MENU(ID_SMALL_TEXT,       MyFrame::OnSetToSmallText)
wxEND_EVENT_TABLE()


// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

bool MyApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    MyFrame *frame = new MyFrame(wxT("wxRichTextCtrl Scrolling Repro App"), wxID_ANY);
    frame->Show(true);

    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title, wxWindowID id)
       : wxFrame(NULL, id, title)
{
    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(wxID_EXIT, _("&Quit"));

    wxMenu* reproMenu = new wxMenu;
    reproMenu->Append(ID_SCROLL_TO_BOTTOM, _("&Scroll To Bottom"));
    reproMenu->Append(ID_LARGE_TEXT,       _("Fill With &Large Text"));
    reproMenu->Append(ID_SMALL_TEXT,       _("Fill With &Small Text"));

    // append the menus to the frame
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(reproMenu, wxT("&Repro"));
    SetMenuBar(menuBar);

    m_richTextCtrl = new wxRichTextCtrl(
        this,
        ID_RICHTEXT_CTRL,
        wxEmptyString,
        wxDefaultPosition,
        wxDefaultSize,
        wxVSCROLL|wxHSCROLL);

    // Seed the rich text control with enough text.
    FillWithText(1000);
}

void MyFrame::FillWithText(int totalParagraphs)
{
    const wxString paragraph(wxT("This is a simple paragraph that exists to take up enough "
                                 "space that the scrollbar appears and that the richtext "
                                 "control uses its optimization to back resize events.\n"));
    m_richTextCtrl->Clear();
    m_richTextCtrl->WriteText(wxT("TOP\n"));
    for (int i = 0; i < totalParagraphs; i++)
    {
        m_richTextCtrl->WriteText(paragraph);
    }
    m_richTextCtrl->WriteText(wxT("BOTTOM\n"));
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnScrollToBottom(wxCommandEvent& WXUNUSED(event))
{
    // Force a trivial resize event.
    static int increment = 1;
    int width;
    int height;
    GetSize(&width, &height);
    SetSize(width + increment, height);
    increment *= -1;

    // Scroll to bottom
    wxTextPos lastPosition = m_richTextCtrl->GetLastPosition();
    m_richTextCtrl->ScrollIntoView(lastPosition, WXK_UP);
}

void MyFrame::OnSetToLargeText(wxCommandEvent& WXUNUSED(event))
{
    // Fill with enough text to show the bug
    FillWithText(1000);
}

void MyFrame::OnSetToSmallText(wxCommandEvent& WXUNUSED(event))
{
    // Fill with enough text to the scrollbar and
    // the expected behavior.
    FillWithText(5);
}

// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/artprov.h>

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title);
private:
    void OnExit(wxCommandEvent& event);
    DECLARE_EVENT_TABLE();
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)  	
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello World");
    frame->Show( true );
    return true;
}

MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title)
{	
    wxPanel *panel = new wxPanel(this, -1);
        
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxButton *btn = new wxButton(panel, -1, wxT("Click me"));
    vbox->Add(btn, 1, wxEXPAND);

    int style = wxTB_HORIZONTAL|wxTB_FLAT|wxTB_DOCKABLE|wxTB_TEXT;

#if SHOWBUG
    wxToolBar *tb = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, style);
#else
    wxToolBar *tb = CreateToolBar(style, wxID_ANY);
#endif

    tb->AddTool(0, wxT("Tool 1"), wxArtProvider::GetBitmap(wxART_GO_BACK));
    tb->AddTool(1, wxT("Tool 2"), wxArtProvider::GetBitmap(wxART_GO_FORWARD));
    tb->AddTool(2, wxT("Tool 3"), wxArtProvider::GetBitmap(wxART_GO_HOME));

    tb->Realize();

#if SHOWBUG
    SetToolBar(tb);
#endif
                        
    panel->SetSizer(vbox);  
    SetClientSize(panel->GetBestSize());
    SetMinClientSize(vbox->GetMinSize());
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

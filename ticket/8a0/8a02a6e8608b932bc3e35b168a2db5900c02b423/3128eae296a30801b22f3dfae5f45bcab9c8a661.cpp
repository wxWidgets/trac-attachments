// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

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

enum {ID_MAIN_TIMETEXT = 1, ID_MAIN_TIME, ID_MAIN_VOLTEXT, ID_MAIN_VOL, ID_MAIN_LAST,
	ID_MAIN_PLAY, ID_MAIN_PAUSE, ID_MAIN_STOP, ID_MAIN_NEXT};

MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title)
{	
    wxPanel *panel = new wxPanel(this, -1);
        
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxFlexGridSizer *gridSizer = new wxFlexGridSizer(2, 2, 0, 0);
		
    wxStaticText *timeText = new wxStaticText(panel, ID_MAIN_TIMETEXT, "00:00:00");
    wxSlider *timeSlider = new wxSlider(panel, ID_MAIN_TIME, 0, 0, 100);
	
    gridSizer->Add(timeText, 0, wxALL, 5);
    gridSizer->Add(timeSlider, 1, wxEXPAND);
	
    wxStaticText *volText = new wxStaticText(panel, ID_MAIN_VOLTEXT, "100%");
    wxSlider *volSlider = new wxSlider(panel, ID_MAIN_VOL, 0, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_INVERSE);
	
    gridSizer->Add(volText, 0, wxALL, 5);
    gridSizer->Add(volSlider, 1, wxEXPAND);
	
    gridSizer->AddGrowableCol(1, 1);
	
    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton *last_button = new wxButton(panel, ID_MAIN_LAST, "Last"); 
    wxButton *play_button = new wxButton(panel, ID_MAIN_PLAY, "Play"); 
    wxButton *pause_button = new wxButton(panel, ID_MAIN_PAUSE, "Pause"); 
    wxButton *stop_button = new wxButton(panel, ID_MAIN_STOP, "Stop"); 
    wxButton *next_button =  new wxButton(panel, ID_MAIN_NEXT, "Next"); 
	
    buttonSizer->Add(last_button, 1, wxEXPAND|wxALL, 5);
    buttonSizer->Add(play_button, 1, wxEXPAND|wxALL, 5);
    buttonSizer->Add(pause_button, 1, wxEXPAND|wxALL, 5);
    buttonSizer->Add(stop_button, 1, wxEXPAND|wxALL, 5);
    buttonSizer->Add(next_button, 1, wxEXPAND|wxALL, 5);
	
    vbox->Add(gridSizer, 0, wxEXPAND);
    vbox->Add(buttonSizer, 0, wxEXPAND);
        
    panel->SetSizer(vbox);
    SetClientSize(panel->GetBestSize()); 
    
#if 1
    // doesn't work correctly
    int height = GetSize().GetHeight();
    SetSizeHints(-1, height, -1, height);
#else
    // doesn't work either
    int height = panel->GetBestSize().GetHeight();
    SetMinClientSize(wxSize(-1, height));
    SetMaxClientSize(wxSize(-1, height));
#endif    
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

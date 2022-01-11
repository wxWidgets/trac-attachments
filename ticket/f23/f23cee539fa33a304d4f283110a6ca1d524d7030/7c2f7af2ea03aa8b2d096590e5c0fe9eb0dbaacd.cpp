// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/listctrl.h>

static const char *items[] = {"One", "One two", "One two three", "One two three four", "One two three four five", "One two three four five six", "One two three four five six seven"};

#define myprintf wxMessageOutput::Get()->Printf

class wxMyListView: public wxListView
{
public:
	wxMyListView(wxWindow *parent,
        	wxWindowID winid,
                const wxPoint& pos,
                const wxSize& size,
                long style) : wxListView(parent, winid, pos, size, style)
	{	
		EnableSystemTheme(false);
	}

	~wxMyListView()
	{
	}	
	
private:
	wxString OnGetItemText(long item, long column) const
	{
		return wxString(items[item]);		
	}

	wxDECLARE_NO_COPY_CLASS(wxMyListView);
}; 

static wxMyListView *lv;

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
		
    lv = new wxMyListView(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VIRTUAL|wxLC_NO_HEADER);    
    lv->AppendColumn("Column");                         
    lv->SetItemCount(7);
    lv->RefreshItem(7);
                                                       
    vbox->Add(lv, 1, wxEXPAND);
 
    panel->SetSizerAndFit(vbox);            
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

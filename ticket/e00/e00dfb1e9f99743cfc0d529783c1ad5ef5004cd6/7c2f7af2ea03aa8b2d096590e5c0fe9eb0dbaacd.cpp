// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/listctrl.h>

#define myprintf wxMessageOutput::Get()->Printf

class wxMyListView: public wxListView
{
public:
	wxMyListView::wxMyListView(wxWindow *parent,
        	wxWindowID winid,
                const wxPoint& pos,
                const wxSize& size,
                long style) : wxListView(parent, winid, pos, size, style)
	{	
	}

	wxMyListView::~wxMyListView()
	{
	}	
	
private:
	wxString wxMyListView::OnGetItemText(long item, long column) const
	{
		if(item >= 100) {
			return wxString("Now this is a very long item");
		} else {
			return wxString("A short item");
		}		
	}

	wxDECLARE_NO_COPY_CLASS(wxMyListView);
}; 

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
		
    wxMyListView *lv = new wxMyListView(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_VIRTUAL|wxLC_SINGLE_SEL|wxLC_HRULES);
    
    lv->AppendColumn(wxT("Column 1"));
    lv->AppendColumn(wxT("Column 2"));
    lv->AppendColumn(wxT("Column 3"));
    
    lv->SetItemCount(100);
    lv->SetColumnWidth(0, -1);
    lv->SetColumnWidth(1, -1);
    lv->SetColumnWidth(2, -1);
    
    lv->SetItemCount(200);
    lv->SetColumnWidth(0, -1);
    lv->SetColumnWidth(1, -1);
    lv->SetColumnWidth(2, -1);                           
                                                     
    vbox->Add(lv, 1, wxEXPAND);

    panel->SetSizerAndFit(vbox);    
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

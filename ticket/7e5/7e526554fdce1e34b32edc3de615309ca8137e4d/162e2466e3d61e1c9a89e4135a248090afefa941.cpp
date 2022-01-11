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
		const char *t[] = {"a", "b", "c", "d", "e"};
		
		return wxString(t[column]);
	}
	
	virtual int wxMyListView::OnGetItemColumnImage(long item, long column) const
	{
		return (column == 4) ? 0 : -1;
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
    wxBitmap *bm = new wxBitmap(60, 20, 32);
    
    wxImageList *il = new wxImageList(60, 20);  
    il->Add(*bm);
    
#if 1
    lv->AssignImageList(il, wxIMAGE_LIST_SMALL);     
#endif
    
    lv->AppendColumn(wxT("Value 1"));
    lv->AppendColumn(wxT("Value 2"));
    lv->AppendColumn(wxT("Value 3"));
    lv->AppendColumn(wxT("Value 4"));
    lv->AppendColumn(wxT("Color"));
            
    lv->SetItemCount(100);
    lv->SetColumnWidth(0, 53);
    lv->SetColumnWidth(1, 53);
    lv->SetColumnWidth(2, 53); 
    lv->SetColumnWidth(3, 53);
    lv->SetColumnWidth(4, 86);  
                                                   
    vbox->Add(lv, 1, wxEXPAND);

    panel->SetSizerAndFit(vbox);    
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

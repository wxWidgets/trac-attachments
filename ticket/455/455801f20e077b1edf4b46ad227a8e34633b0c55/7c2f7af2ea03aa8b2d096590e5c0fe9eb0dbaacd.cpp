// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/dataview.h>

#define myprintf wxMessageOutput::Get()->Printf

static wxDataViewListCtrl *dv;
	
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

static void evtcallback(wxCommandEvent &event) 
{ 				
	for(int k = 0; k < dv->GetItemCount(); k++) {						
		wxDataViewItem item = dv->RowToItem(k);
		myprintf("DATA0: %p\n", dv->GetItemData(item));						
	}	
}
		
MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title)
{	
    wxWindow *panel = new wxPanel(this, -1);
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    
    dv = new wxDataViewListCtrl(panel, wxID_ANY, wxDefaultPosition, wxSize(640, 200));
    
    dv->AppendToggleColumn(wxT("Toggle"));
    dv->AppendTextColumn(wxT("Column 1"), wxDATAVIEW_CELL_INERT);
    dv->AppendTextColumn(wxT("Column 2"), wxDATAVIEW_CELL_INERT);
    dv->AppendTextColumn(wxT("Column 3"), wxDATAVIEW_CELL_INERT, -1, wxALIGN_LEFT, wxDATAVIEW_COL_SORTABLE|wxDATAVIEW_COL_RESIZABLE);
    
    wxVector<wxVariant> data;
	
    data.push_back(wxVariant(true));			
    data.push_back(wxVariant("B"));							
    data.push_back(wxVariant("A"));							
    data.push_back(wxVariant("C"));							
    dv->AppendItem(data, (wxUIntPtr) 0);

    data.clear();
    data.push_back(wxVariant(false));	    
    data.push_back(wxVariant("A"));							
    data.push_back(wxVariant("B"));							
    data.push_back(wxVariant("B"));							
    dv->AppendItem(data, (wxUIntPtr) 1);
    
    dv->GetColumn(0)->SetWidth(wxCOL_WIDTH_AUTOSIZE);
    dv->GetColumn(1)->SetWidth(wxCOL_WIDTH_AUTOSIZE);
    dv->GetColumn(2)->SetWidth(wxCOL_WIDTH_AUTOSIZE);
    dv->GetColumn(3)->SetWidth(wxCOL_WIDTH_AUTOSIZE);
    
    wxButton *but = new wxButton(panel, -1, wxT("Clicky"));
    but->Bind(wxEVT_BUTTON, evtcallback, wxID_ANY, wxID_ANY);  

    vbox->Add(dv, 1, wxEXPAND);    
    vbox->Add(but, 0, wxEXPAND);	    					        	    					    
                
    panel->SetSizer(vbox);    
    SetClientSize(panel->GetBestSize());			
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

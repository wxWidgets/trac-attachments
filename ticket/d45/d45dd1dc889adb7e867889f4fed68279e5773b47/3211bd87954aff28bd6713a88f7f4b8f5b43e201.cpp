#include <wx/wx.h>
#include <wx/dataview.h>

//IMPLEMENT_APP(MainApp)

class MainFrame : public  wxFrame
{
    private:
        wxDataViewListCtrl *m_datalist;
	int m_column;

   public:
    MainFrame(wxWindow *parent): wxFrame(parent, wxID_ANY, "Testing a wxBug")
    {
	m_column = 1000;
        wxPanel *panel = new wxPanel(this, wxID_ANY);
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	panel->SetSizer(sizer);

	m_datalist = new wxDataViewListCtrl(panel, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(panel, wxSize(-1,-1)), wxDV_ROW_LINES|wxDV_MULTIPLE|wxDV_SINGLE);
    	sizer->Add(m_datalist, 1, wxEXPAND | wxALL, 5);

	wxButton *btn = new wxButton(panel, wxID_ANY, "Press to Reload");
	sizer->Add(btn, 0, wxEXPAND | wxALL, 5);

	btn->Bind(wxEVT_BUTTON, &MainFrame::OnReload, this);
    }

    void OnReload(wxCommandEvent& e)
    {
	m_datalist->ClearColumns();
	m_datalist->DeleteAllItems();

	m_datalist->AppendTextColumn("Column 1", wxDATAVIEW_CELL_EDITABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_NOT, wxDATAVIEW_COL_RESIZABLE | wxDATAVIEW_COL_SORTABLE);
	m_datalist->AppendTextColumn("Column 2", wxDATAVIEW_CELL_EDITABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_NOT, wxDATAVIEW_COL_RESIZABLE | wxDATAVIEW_COL_SORTABLE);
	m_datalist->AppendTextColumn("Column 3 Long very long one", wxDATAVIEW_CELL_EDITABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_NOT, wxDATAVIEW_COL_RESIZABLE | wxDATAVIEW_COL_SORTABLE);
	for(int i = 0; i < m_column; i++)
	{
	    wxVector<wxVariant> row;
            for(int col = 0; col < 3; col++)
	    {
                row.push_back(wxVariant("1233333444"));
	    }
	    m_datalist->AppendItem(row);
	}

	if(m_column > 0 ) m_column -= 200;
    }
};

class MainApp: public wxApp // MainApp is the class for our application 
{
     public:
	virtual bool OnInit()
	{
             MainFrame *f = new MainFrame(NULL);
	     f->Show();
	     SetTopWindow(f);
	     return true;
	}
};

IMPLEMENT_APP(MainApp) 





#include <wx/wx.h>

#include <wx/dataview.h>

const int ID_SHOW_DIALOG = wxID_HIGHEST + 1;
const int ID_MY_LIST = wxID_HIGHEST + 2;
const int ID_ADD_BUTTON = wxID_HIGHEST + 3;
const int ID_CLOSE_BUTTON = wxID_HIGHEST + 4;

class MyDialog: public wxDialog
{
	DECLARE_CLASS(MyDialog)
	DECLARE_EVENT_TABLE()
public:
	MyDialog();
	MyDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& caption = _T("Error"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxSize(640, 480),
		long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU);

	bool Create(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& caption = _T("Error"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxSize(640, 480),
		long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU);

protected:
	void OnAdd(wxCommandEvent& event);
	void OnClose(wxCommandEvent& event);

	wxDataViewListCtrl* listCtrl;
	wxDataViewColumn *col1;
	wxDataViewColumn *col2;
};

IMPLEMENT_CLASS(MyDialog, wxDialog);

BEGIN_EVENT_TABLE(MyDialog, wxDialog)
	EVT_BUTTON(ID_ADD_BUTTON, MyDialog::OnAdd)
	EVT_BUTTON(ID_CLOSE_BUTTON, MyDialog::OnClose)
END_EVENT_TABLE()

MyDialog::MyDialog(wxWindow* parent, wxWindowID id, const wxString& caption,
		const wxPoint& pos, const wxSize& size, long style)
{
	Create(parent, id, caption, pos, size, style);
}

bool MyDialog::Create(wxWindow* parent, wxWindowID id, const wxString& caption,
		const wxPoint& pos, const wxSize& size, long style)
{
	if (!wxDialog::Create(parent, id, caption, pos, size, style))
		return false;
	
	wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(sizer1);

	wxBoxSizer* sizer2 = new wxBoxSizer(wxVERTICAL);
	sizer1->Add(sizer2, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	listCtrl = new wxDataViewListCtrl(this, ID_MY_LIST, wxDefaultPosition, wxSize(300, 300));
	col1 = listCtrl->AppendTextColumn(_T("Col1"), wxDATAVIEW_CELL_EDITABLE, 300, wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE | wxDATAVIEW_COL_SORTABLE);
	col2 = listCtrl->AppendTextColumn(_T("Col2"), wxDATAVIEW_CELL_EDITABLE, -1, wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE | wxDATAVIEW_COL_SORTABLE);
	sizer2->Add(listCtrl);

	wxButton* addButton = new wxButton(this, ID_ADD_BUTTON, _T("Add"));
	sizer2->Add(addButton);

	wxButton* closeButton = new wxButton(this, ID_CLOSE_BUTTON, _T("Close"));
	sizer2->Add(closeButton);

	return true;
}

void MyDialog::OnAdd(wxCommandEvent& event)
{
	wxVector<wxVariant> mapping;
	mapping.push_back("");
	mapping.push_back("");
	
	listCtrl->AppendItem(mapping);

	int index = listCtrl->GetItemCount() - 1;
	if (index != wxNOT_FOUND) {
		wxDataViewItem item = listCtrl->RowToItem(index);
		// listCtrl->EnsureVisible(item);
		listCtrl->EditItem(item, col1);
	}
}

void MyDialog::OnClose(wxCommandEvent& event)
{
	Close();
}

class MainApp: public wxApp
{
public:
	virtual bool OnInit();
};

IMPLEMENT_APP(MainApp)

class MainFrame: public wxFrame
{
public:
	MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
 
	void ShowDialog(wxCommandEvent& event);

	wxMenuBar *MainMenu;
 
	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE (MainFrame, wxFrame)
	EVT_MENU(ID_SHOW_DIALOG, MainFrame::ShowDialog)
END_EVENT_TABLE()

bool MainApp::OnInit()
{
	MainFrame *MainWin = new MainFrame(
		_("Bug"), wxPoint(1, 1), wxSize(300, 200));
	MainWin->Show(TRUE);
	SetTopWindow(MainWin);
	return TRUE;
}

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
: wxFrame((wxFrame*) 0, -1, title, pos, size)
{
	CreateStatusBar(2);
 
	MainMenu = new wxMenuBar();
	wxMenu *menu = new wxMenu();
 
	menu->Append(ID_SHOW_DIALOG,
		_("&Show Dialog"), _("Show fault dialog"));

	MainMenu->Append(menu, _("&Menu"));
	SetMenuBar(MainMenu);
}


void MainFrame::ShowDialog(wxCommandEvent& WXUNUSED(event))
{
	MyDialog *dialog = new MyDialog(this);
	dialog->ShowModal();
}


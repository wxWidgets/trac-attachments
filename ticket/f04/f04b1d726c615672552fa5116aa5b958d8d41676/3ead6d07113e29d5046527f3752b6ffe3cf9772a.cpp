#include "wx/wxprec.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/listctrl.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnQuit(wxCommandEvent& event);
		void OnActivate(wxListEvent& event);
private:
		wxListCtrl* pListCtrl;
    DECLARE_EVENT_TABLE()
};

enum
{
    Minimal_Quit = 1,
    ID_MAINLIST,
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame(_T("ListCtrl Bug Tester"),
			wxDefaultPosition, wxDefaultSize);
		frame->Centre(wxBOTH);
    frame->Show(TRUE);
		SetTopWindow(frame);
    return TRUE;
}

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit, MyFrame::OnQuit)
    EVT_LIST_ITEM_ACTIVATED(ID_MAINLIST, MyFrame::OnActivate)
END_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame(NULL, -1, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(Minimal_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, _T("&File"));
    SetMenuBar(menuBar);

		wxPanel* pPanel = new wxPanel(this, -1);

//---------------------------------------------
//LIST CONTROL setup
		pListCtrl = new wxListCtrl(pPanel, ID_MAINLIST,
			wxDefaultPosition, wxSize(200, 100), wxLC_EDIT_LABELS | wxLC_REPORT);
		wxListItem itemCol;
		itemCol.m_mask = wxLIST_MASK_TEXT;
    itemCol.m_text = "Column ONE";
    pListCtrl->InsertColumn(0, itemCol);
    itemCol.m_text = "Column TWO";
    pListCtrl->InsertColumn(1, itemCol);
		long iIndex = pListCtrl->InsertItem(0, "First Item");
    pListCtrl->SetItem(iIndex, 1, "some more stuff");
		iIndex = pListCtrl->InsertItem(1, "Second Item");
    pListCtrl->SetItem(iIndex, 1, "more stuff");
//---------------------------------------------

		wxBoxSizer* mysizer = new wxBoxSizer(wxVERTICAL);
		mysizer->Add(pListCtrl, 1, wxEXPAND | wxALL, 10);
		wxButton* pButton = new wxButton(pPanel, -1, "Button");
		mysizer->Add(pButton, 0, wxALL, 10);

		pPanel->SetAutoLayout(TRUE);
		pPanel->SetSizer(mysizer);
		mysizer->SetSizeHints(pPanel); 
		mysizer->Fit(pPanel);

		SetAutoLayout(TRUE);
		wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);
		topsizer->Add( pPanel, 1, wxEXPAND );
		SetSizer( topsizer );
		topsizer->SetSizeHints(this); 
		topsizer->Fit(this);
}

//---------------------------------------------
//LIST CONTROL activation
void MyFrame::OnActivate(wxListEvent& event)
{
	pListCtrl->EditLabel( event.GetIndex() );
}
//---------------------------------------------

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}

 	  	 

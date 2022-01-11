#include "wx/wx.h"
#include "wx/treectrl.h"

class Frame : public wxFrame{
public:
	Frame::Frame(const wxString &, const wxPoint &, const wxSize &);

};

Frame::Frame(const wxString & a, const wxPoint & b, const wxSize &c) 
:wxFrame((wxWindow *)NULL,-1,a,b,c){	
	wxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
	wxTreeCtrl *tree = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_NO_LINES | wxTR_HAS_BUTTONS );
	wxPanel *panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );

	sizer->Add(tree,0,wxEXPAND);
	sizer->Add(panel,1,wxEXPAND);

	panel->SetBackgroundColour(*wxBLACK);

	wxTreeItemId rootItem = tree->AddRoot("!!!");
	bool test1 = tree->SetBackgroundColour(*wxWHITE);
	tree->SetOwnBackgroundColour(*wxWHITE);
	tree->SetItemBackgroundColour(rootItem,*wxWHITE);

	SetSizer(sizer);
}

class App : public wxApp{

public: 
	virtual bool App::OnInit(){
		wxInitAllImageHandlers();
		Frame *pFrame = new Frame(wxT("foo"),wxDefaultPosition,wxSize(640,480));
		pFrame->Show(TRUE);
		SetTopWindow(pFrame);
		return TRUE;
	}
};

DECLARE_APP(App)
IMPLEMENT_APP(App)
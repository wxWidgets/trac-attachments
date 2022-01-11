#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>

class SomeFrame: public wxFrame {
public:
	SomeFrame(wxWindow* parent, int id, const wxString& title);

	virtual void OnGridPropertyChange(wxPropertyGridEvent &event);

	DECLARE_EVENT_TABLE();
private:
	void set_properties();
	void do_layout();
	wxPropertyGrid* grid_1;
};


enum
{
	ID_PROPGRID=wxID_ANY+1,
};


SomeFrame::SomeFrame(wxWindow* parent, int id, const wxString& title) :
						wxFrame(parent, id, title)
{
	grid_1 = new wxPropertyGrid(this, ID_PROPGRID);
	grid_1->Append( new wxPropertyCategory("SomeCat"));
	grid_1->Append(new wxStringProperty("moahdata","moahdata","someData"));
 	do_layout();
}

BEGIN_EVENT_TABLE(SomeFrame,wxFrame)
    EVT_PG_CHANGING(ID_PROPGRID, SomeFrame::OnGridPropertyChange)
END_EVENT_TABLE()


void SomeFrame::OnGridPropertyChange(wxPropertyGridEvent &event)
{
	grid_1->Clear();
	

	grid_1->Append( new wxPropertyCategory("SomeCat"));

	grid_1->Append(new wxStringProperty("moahdata","moahdata","someData"));
	grid_1->Append(new wxStringProperty("moahdata1","moahdata1","someData"));
}

void SomeFrame::do_layout()
{
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    sizer_1->Add(grid_1, 1, wxEXPAND, 0);
    SetSizer(sizer_1);
    sizer_1->Fit(this);
    Layout();
}


class MyApp: public wxApp {
public:
    bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    SomeFrame* frame_1 = new SomeFrame(NULL, wxID_ANY, wxEmptyString);
    SetTopWindow(frame_1);
    frame_1->Show();
    return true;
}

#include <wx/wx.h>
#include <wx/aui/auibook.h>
#include <gtk/gtk.h>

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};
IMPLEMENT_APP(MyApp)

//----------------------------------------

class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title);

private:
};

// ----------------------------------------------------------------------------

bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame(_("test wxWindow Focus"));
	frame->SetSize(100,100);
	frame->Show();
	return true;
}


// ----------------------------------------------------------------------------

MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
	wxAuiNotebook *nb = new wxAuiNotebook(this, -1);

	wxPanel *p1 = new wxPanel(this, -1, wxPoint(0,0), wxSize(300, 300));
	wxTextCtrl *t11 = new wxTextCtrl(p1, -1, _(""), wxPoint(  0,   0), wxSize(200,  50));
	wxTextCtrl *t12 = new wxTextCtrl(p1, -1, _(""), wxPoint(  0, 100), wxSize(200,  50));
	
	wxPanel *p2 = new wxPanel(this, -1, wxPoint(0,0), wxSize(300, 300));
	wxTextCtrl *t21 = new wxTextCtrl(p2, -1, _(""), wxPoint(  0,   0), wxSize(200,  50));
	wxTextCtrl *t22 = new wxTextCtrl(p2, -1, _(""), wxPoint(  0, 100), wxSize(200,  50));
	
	nb->AddPage(p1, _("page 1"));
	nb->AddPage(p2, _("page 2"));
}

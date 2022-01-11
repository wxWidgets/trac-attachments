#include <wx/app.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/menu.h>

class app : public wxApp {
public:
	bool OnInit (void);
};

DECLARE_APP (app)
IMPLEMENT_APP (app)

bool app::OnInit (void)
{
	wxFrame *f = new wxFrame (NULL, -1, "Test");
	wxTextCtrl *t = new wxTextCtrl (f, -1);
	wxMenuBar *mb = new wxMenuBar;
	wxMenu *m = new wxMenu;
	mb->Append (m, "Edit");
	m->Append (wxID_CLEAR, "Delete\tDel");
	f->SetMenuBar (mb);

	SetTopWindow (f);
	f->Show();

	return true;
}

 	  	 

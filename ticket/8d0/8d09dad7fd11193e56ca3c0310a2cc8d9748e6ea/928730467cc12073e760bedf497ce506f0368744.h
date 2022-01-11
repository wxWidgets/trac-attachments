#include <wx/wx.h>

class App : public wxApp
{
	public :
		virtual bool OnInit();
		virtual int OnExit(){return 0;}
		void onClick(wxCommandEvent &event);
		
	private :
	wxFrame *frame;
	wxTextCtrl* textctrl;
};

DECLARE_APP(App);
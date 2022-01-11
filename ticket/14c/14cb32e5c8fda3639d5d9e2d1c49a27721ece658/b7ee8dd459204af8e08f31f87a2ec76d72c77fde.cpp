#include <wx/wx.h>

class MainFrame: public wxFrame {
    public:
    
    MainFrame(): wxFrame(NULL, wxID_ANY, wxT("")) {
        wxScrolledWindow* win = new wxScrolledWindow(this);
        wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
        
        for (int i = 0; i < 25; ++i) {
            wxButton* tmp = new wxButton(win, wxID_ANY, wxT("foo"));
            boxSizer->Add(tmp, 0, wxALL, 5);
        }
        
        win->SetSizer(boxSizer);
        win->FitInside();
        win->SetScrollRate(0, 1);
    }
};
    
class UserInterface: public wxApp {
    public:    
    bool OnInit() {
        MainFrame* frame = new MainFrame();
        
        SetTopWindow(frame);
        frame->Show(true);
        
        return true;
    }
};
    
IMPLEMENT_APP(UserInterface)

 	  	 

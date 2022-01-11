// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#define myprintf wxMessageOutput::Get()->Printf
	
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
		
MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title)
{	
    wxWindow *panel = new wxPanel(this, -1);
    wxSizer *vbox;
    
    wxScrolledWindow *w = new wxScrolledWindow(panel); 
    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    wxArrayString strings;
    strings.Add("Human");
    strings.Add("Elf");
    strings.Add("Dwarf");
    strings.Add("Hobbit");
    strings.Add("Gnome");
    
    wxBoxSizer *bs = new wxBoxSizer(wxHORIZONTAL);
    wxRadioBox *radio = new wxRadioBox(w, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, strings, 5, wxRA_SPECIFY_ROWS);
    bs->Add(0, 0, 1);
    bs->Add(radio);
    bs->Add(0, 0, 1);
    sizer->Add(bs, 0, wxEXPAND);
    
    strings.Clear();
    strings.Add("Warrior");
    strings.Add("Rogue");
    strings.Add("Bard");
    strings.Add("Monk");
    strings.Add("Magician");
    strings.Add("Archmage");
    
    bs = new wxBoxSizer(wxHORIZONTAL);
    radio = new wxRadioBox(w, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, strings, 6, wxRA_SPECIFY_ROWS);
    bs->Add(0, 0, 1);
    bs->Add(radio);
    bs->Add(0, 0, 1);
    sizer->Add(bs, 0, wxEXPAND);                        

    wxStaticBitmap *bm = new wxStaticBitmap(w, -1, wxBitmap(200, 100));
    sizer->Add(bm);
    
    w->SetScrollRate(10, 10);
    
    w->SetSizer(sizer);
    sizer->Fit(w);

    wxButton *b = new wxButton(panel, -1, wxT("F"));
                    
    vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(w, 1, wxEXPAND);
    vbox->Add(b, 0, wxEXPAND);

    panel->SetSizer(vbox);    
    SetClientSize(panel->GetBestSize());		
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

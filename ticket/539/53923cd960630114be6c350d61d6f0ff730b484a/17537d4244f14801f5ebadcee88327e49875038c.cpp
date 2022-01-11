/*This is compilable example*/


#include <wx/wx.h>   
#include <wx/html/htmlwin.h>
#include <wx/textctrl.h>
class MyFrame : public wxFrame {
public:
    MyFrame()
        : wxFrame(NULL, wxID_ANY, "Test")
    {
     // scrolled window
     wxScrolledWindow *scr_win= new wxScrolledWindow(this, wxID_ANY);
     
     //buttons
     wxButton *first_btn= new wxButton(scr_win, wxID_ANY, "button 1");
     wxButton *second_btn= new wxButton(scr_win, wxID_ANY, "button 2");
     wxButton *third_btn= new wxButton(scr_win, wxID_ANY, "button 3");
     wxButton *fourth_btn= new wxButton(scr_win, wxID_ANY, "button 3");
     
     //text input
     wxTextCtrl *some_input=new wxTextCtrl(scr_win, wxID_ANY, "some input here");
     
     //html window
     wxHtmlWindow *html_win=new wxHtmlWindow(scr_win,
                    wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_NEVER);
     for(int i=0;i<100;i++)
	{
	html_win->AppendToPage("<div> Some content of the wxHtmlWndow here </div>");
	html_win->AppendToPage("<div> Scrolling by the mouse wheel is not working if the mouse pointer is somewhere here </div><br>");
	}
   
    
    
     //Some sizings here
     wxBoxSizer *hor_one_szr=new wxBoxSizer(wxHORIZONTAL);
     hor_one_szr->Add(first_btn, 0, wxALL);
     hor_one_szr->AddSpacer(70);
     hor_one_szr->Add(second_btn, 0, wxALL);
     hor_one_szr->AddSpacer(40);
     hor_one_szr->Add(some_input, 1, wxALL|wxEXPAND);
     hor_one_szr->AddSpacer(5);
     
     wxBoxSizer *hor_sec_szr=new wxBoxSizer(wxHORIZONTAL);
     hor_sec_szr->Add(third_btn, 0, wxALL);
     hor_sec_szr->AddSpacer(70);
     hor_sec_szr->Add(fourth_btn, 0, wxALL);
     
     
     wxBoxSizer *scr_sizer=new wxBoxSizer(wxVERTICAL);
     scr_sizer->Add(new wxStaticText(scr_win, wxID_ANY, "This panel with buttons is supposed to scroll\n"
                     "away from the screen to leave more space for\n"
                     "the content of the wxHtmlWindow\n"));
     scr_sizer->Add(hor_one_szr, 0, wxALL|wxEXPAND);
     scr_sizer->Add(hor_sec_szr, 0, wxALL);
     scr_sizer->AddSpacer(5);
     scr_sizer->Add(html_win, 1, wxALL|wxEXPAND);
     scr_sizer->Add(new wxButton(scr_win, wxID_ANY, "Another button"));
     
     
     
     scr_win->SetSizerAndFit(scr_sizer);
     wxBoxSizer *main_sizer=new wxBoxSizer(wxVERTICAL);
     main_sizer->Add(scr_win, 1, wxEXPAND|wxALL);
     scr_win->SetScrollRate(5, 5);
     SetSizerAndFit(main_sizer);
     
     this->SetSize(wxSize(800,500));
     scr_sizer->FitInside(this);
     scr_sizer->RecalcSizes();
     html_win->SetMinSize(wxSize(-1,
                  html_win->GetInternalRepresentation()->GetHeight()));
     html_win->SetSize(wxSize(-1,
                  html_win->GetInternalRepresentation()->GetHeight()));
      
     this->GetSizer()->RecalcSizes();
     scr_win->Fit();
     scr_win->Refresh();
     scr_win->GetSizer()->Layout();

     this->Layout();
     this->Refresh();
     scr_win->Scroll(0,0);
     scr_win->SetFocus();
    }   
};

/**** MyApp ****/
class MyApp : public wxApp {
public:   
    bool OnInit()
    {
        MyFrame* newframe = new MyFrame();               
        newframe->Show();
        return true;
    }
};

IMPLEMENT_APP(MyApp)
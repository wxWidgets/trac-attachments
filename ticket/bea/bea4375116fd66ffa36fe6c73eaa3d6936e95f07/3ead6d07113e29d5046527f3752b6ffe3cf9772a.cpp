#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
    #include "wx/regex.h"
    #include "wx/stc/stc.h"
#endif

//////////////////////////////////////////////////
// MyApp class declaration
//////////////////////////////////////////////////
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

//////////////////////////////////////////////////
// MyFrame class declaration
//////////////////////////////////////////////////
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

private:
    void Select1(wxCommandEvent &ev);
    void Select2(wxCommandEvent &ev);
	
    wxStyledTextCtrl  *stc;

    DECLARE_EVENT_TABLE()
};

//////////////////////////////////////////////////
// MyApp class implementation
//////////////////////////////////////////////////
IMPLEMENT_APP(MyApp)

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    MyFrame *window = new MyFrame(_T("wxStyledTextCtrl test app"));
    window->Show(true);
    return true;
}

//////////////////////////////////////////////////
// MyFrame class implementation
//////////////////////////////////////////////////
const int ID_STC = 101;
const int ID_SELECT1 = 102;
const int ID_SELECT2 = 103;

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON(ID_SELECT1, MyFrame::Select1)
    EVT_BUTTON(ID_SELECT2, MyFrame::Select2)
END_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title) 
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~ (wxRESIZE_BORDER | wxRESIZE_BOX | wxMAXIMIZE_BOX))
{
    wxPanel *pnl = new wxPanel(this);
    new wxButton(pnl, ID_SELECT1, _T("Select 'Hello'"), wxPoint(5, 5), wxSize(150, 25));
    new wxButton(pnl, ID_SELECT2, _T("Select 'Goodbye'"), wxPoint(160, 5), wxSize(150, 25));
    stc = new wxStyledTextCtrl(pnl, ID_STC, wxPoint(5, 30), wxSize(790, 530));
    stc->SetText(_T("Hello\nä\nGoodbye\n"));
}

void MyFrame::Select1(wxCommandEvent &ev)
{
    size_t selStart = 0, selLen = 0;

    wxRegEx *re = new wxRegEx(_T("Hello"));
    if (re->IsValid() && re->Matches(stc->GetText()))
    {
        re->GetMatch(&selStart, &selLen);
        stc->SetSelection(selStart, selStart + selLen);
    }
}

void MyFrame::Select2(wxCommandEvent &ev)
{
    size_t selStart = 0, selLen = 0;

    wxRegEx *re = new wxRegEx(_T("Goodbye"));
    if (re->IsValid() && re->Matches(stc->GetText()))
    {
        re->GetMatch(&selStart, &selLen);
        stc->SetSelection(selStart, selStart + selLen);
    }
}

 	  	 

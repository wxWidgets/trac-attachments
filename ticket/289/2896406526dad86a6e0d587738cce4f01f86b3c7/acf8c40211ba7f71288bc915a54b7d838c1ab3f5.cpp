#include <stdio.h>

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

class MyDialog1 : public wxDialog
{
    public:
	MyDialog1 (wxWindow *parent);
	
    private:
	wxButton * m_button3;
	
	void OnButton (wxCommandEvent& event);
	
	enum
        {
            ID_BUTTON
        };

        DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(MyDialog1, wxDialog)
    EVT_BUTTON (ID_BUTTON, MyDialog1::OnButton)
END_EVENT_TABLE()

MyDialog1::MyDialog1 (wxWindow *parent)
	: wxDialog(parent, wxID_ANY, wxString (L""), wxPoint(0, 0), wxSize(240, 320), wxDEFAULT_DIALOG_STYLE, wxString(L"Dialog1"))
{
    m_button3 = new wxButton (this, ID_BUTTON, wxString(L"--->"), wxPoint(0,0));
}

void
MyDialog1::OnButton (wxCommandEvent& event)
{
   wxString wxsMsg;
   wxsMsg << L"Should I really do this!";
   
   wxMessageDialog dlgMsgYesNo (this, wxsMsg, wxString(L"Storno!"), wxYES_NO);
   if (wxID_YES == dlgMsgYesNo.ShowModal ())
   {
           wxsMsg.Clear ();
           wxsMsg << L"Not done!";
           wxMessageDialog  dlgMsg(this, wxsMsg, wxString(L"Napaka!"), wxOK);
           dlgMsg.ShowModal ();
   } 
}

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

private:
    wxButton * m_button1;
    wxButton * m_button2;
    
    void OnButton (wxCommandEvent& event);
    void OnQuit (wxCommandEvent& event);
    
    DECLARE_EVENT_TABLE()
};

enum
{
    ID_BUTTON1,
    ID_BUTTON2
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON (ID_BUTTON1, MyFrame::OnButton)
    EVT_BUTTON (ID_BUTTON2, MyFrame::OnQuit)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    FILE * fp;
    fp = fopen ("x11focus.log", "w+");
    wxLog *logger = new wxLogStderr(fp);
    wxLog::SetActiveTarget(logger);
    wxLog::AddTraceMask(_T("focus"));
    
    MyFrame *frame = new MyFrame(_T("Minimal wxWidgets App"));

    frame->Show(true);

    return true;
}

MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
    m_button1 = new wxButton (this, ID_BUTTON1, wxString(L"--->"), wxPoint(0,0));
    
    m_button2 = new wxButton (this, ID_BUTTON2, wxString(L"Quit"), wxPoint(0,50));
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MyFrame::OnButton(wxCommandEvent& WXUNUSED(event))
{
    MyDialog1 * dlg = new MyDialog1 (this);
    dlg->ShowModal ();
    dlg->Destroy ();
}


 	  	 

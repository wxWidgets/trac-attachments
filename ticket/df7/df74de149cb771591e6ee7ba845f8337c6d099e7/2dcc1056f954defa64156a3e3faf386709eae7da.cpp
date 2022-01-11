#include <wx/wx.h>
#include <wx/string.h>
#include <stdio.h>

void printfwxString(const wxString &value) {

    const char *sVal = (const char *)value.c_str();
     
    printf("Value in %p says: %s\n", &value, sVal);

    fflush(NULL);

    printf("Len of value = %i\n", strlen(sVal));

}


class MyApp: public wxApp
{
    virtual bool OnInit();
};

class MyFrame: public wxFrame
{
public:

    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    void OnQuit(wxCommandEvent& event);
   
    DECLARE_EVENT_TABLE()
};


enum
{
    ID_Quit = 1    
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Quit, MyFrame::OnQuit)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( _("Hello World"), wxPoint(50, 50),
                                  wxSize(450,340) );
    frame->Show(true);
    SetTopWindow(frame);

    
   //TEST CODE
    wxTextCtrl ctrl(frame, -1);

    wxString fullS(_T("Hello World!"));
    printfwxString(fullS);
    ctrl.WriteText(fullS);


    printf("--------------\n");

    wxString emptyS;
    printfwxString(emptyS);
    //PROBLEM IS HERE:   This crashes in 2.9.1 !!
    ctrl.WriteText(emptyS);




    return true;
} 

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame( NULL, -1, title, pos, size )
{
   
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}





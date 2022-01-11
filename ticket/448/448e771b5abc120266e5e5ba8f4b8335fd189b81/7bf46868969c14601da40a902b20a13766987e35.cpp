// list display problem
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "wx/wxprec.h"
#include "wx/listctrl.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

using namespace std;

class MyApp: public wxApp
{
    virtual bool OnInit();
};

class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    void OnQuit(wxCommandEvent& event);

private:

    wxListCtrl       *m_list;

    DECLARE_EVENT_TABLE()
};

enum
{
    ID_Selection = 1,
    ID_MYLIST,
    ID_MyQuit,
};


BEGIN_EVENT_TABLE(MyFrame, wxFrame)
      EVT_MENU(ID_MyQuit,       MyFrame::OnQuit)
END_EVENT_TABLE()


IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxLog::EnableLogging(false);

    MyFrame *frame = new MyFrame( "list problem", wxPoint(-1,-1), wxSize(600,300) );

    frame->Show( true );
    SetTopWindow( frame );
    return true;
}



MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{


    if (wxLog::IsEnabled()) {
      wxLogWindow *logWindow = new wxLogWindow(this, wxT("Log"));
      logWindow->SetVerbose(TRUE);
      wxLog::SetActiveTarget(logWindow);
    }

    wxMenu *menuFile = new wxMenu();
    menuFile->Append( ID_MyQuit, "E&xit" );

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );

    SetMenuBar( menuBar );

    //----------------------------------------------
    // create list window

    wxPanel *listPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* listSizer = new wxBoxSizer( wxVERTICAL );

    m_list = new wxListCtrl(listPanel, ID_MYLIST, wxDefaultPosition, wxDefaultSize,
                              (wxLC_LIST) );

    listSizer->Add(m_list, 1, wxALL|wxEXPAND, 5 );

    listPanel->SetSizer(listSizer);
    listPanel->Layout();
    listSizer->Fit(listPanel);

    // add some wide and some narrow children
    wxString str;
    wxListItem item;
    m_list->Hide();
    for (int i=0; i< 20; i++) {
      if (i&1)  // alternate regular width and wide with
        str.Printf(wxT("item that is wider than other children %i"), i+1);
      else
        str.Printf(wxT("item %i"), i+1);
      item.SetId(i);
      item.SetText(str);
      m_list->InsertItem(item);
    }
    m_list->Show();


}

void MyFrame::OnQuit(wxCommandEvent& event)
{
    Close( true );
}


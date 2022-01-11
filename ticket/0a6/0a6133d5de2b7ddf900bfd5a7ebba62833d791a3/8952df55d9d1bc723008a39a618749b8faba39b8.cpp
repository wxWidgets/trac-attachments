// tree scroll problem
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "wx/wxprec.h"
#include "wx/treectrl.h"

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
    void OnScrollDown(wxCommandEvent& event);
    void OnScrollUp(wxCommandEvent& event);
    void Scroll(bool down);

private:

    wxTreeCtrl       *m_tree;

    DECLARE_EVENT_TABLE()
};

enum
{
    ID_Selection = 1,
    ID_MYTREE,
    ID_MyQuit,
    ID_MyScrollDown,
    ID_MyScrollUp
};


BEGIN_EVENT_TABLE(MyFrame, wxFrame)
      EVT_MENU(ID_MyQuit,       MyFrame::OnQuit)
      EVT_MENU(ID_MyScrollDown, MyFrame::OnScrollDown)
      EVT_MENU(ID_MyScrollUp,   MyFrame::OnScrollUp)
END_EVENT_TABLE()


IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxLog::EnableLogging(true);
    MyFrame *frame = new MyFrame( "tree problem", wxPoint(-1,-1), wxSize(600,300) );

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

    wxMenu *menuEdit = new wxMenu();
    menuEdit->Append( ID_MyScrollDown, "Scroll Down" );
    menuEdit->Append( ID_MyScrollUp, "Scroll Up" );

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuEdit, "&Scroll" );

    SetMenuBar( menuBar );

    //----------------------------------------------
    // create tree window

    wxPanel *treePanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* treeSizer = new wxBoxSizer( wxVERTICAL );

    m_tree = new wxTreeCtrl(treePanel, ID_MYTREE, wxDefaultPosition, wxDefaultSize,
                              (wxTR_NO_BUTTONS | wxTR_HIDE_ROOT | wxTR_NO_LINES | wxTR_MULTIPLE) );

    treeSizer->Add(m_tree, 1, wxALL|wxEXPAND, 5 );

    treePanel->SetSizer(treeSizer);
    treePanel->Layout();
    treeSizer->Fit(treePanel);

    // initial root
    wxTreeItemId treeRoot = m_tree->AddRoot(wxT("tree root"));

    // add enough children to force a scroll bar
    wxString str;
    wxTreeItemId treeChild;
    for (int i=0; i< 20; i++) {
      str.Printf(wxT("child %i"), i+1);
      treeChild = m_tree->AppendItem(treeRoot,str);
    }


}

void MyFrame::OnQuit(wxCommandEvent& event)
{
    Close( true );
}

void MyFrame::OnScrollDown(wxCommandEvent& event)
{
  Scroll(true);
}

void MyFrame::OnScrollUp(wxCommandEvent& event)
{
  Scroll(false);
}

void MyFrame::Scroll(bool down)
{

      int xpixunit, ypixunit, xview, yview, xsize, ysize, vxsize, vysize,
          newy, maxy, totalsize, thumbsize;

      m_tree->GetScrollPixelsPerUnit(&xpixunit, &ypixunit);
      m_tree->GetViewStart(&xview, &yview);
      m_tree->GetSize(&xsize, &ysize);
      m_tree->GetVirtualSize(&vxsize, &vysize);

      thumbsize = (int)(ysize/ypixunit);
      totalsize = (int)(vysize/ypixunit);
      maxy = totalsize - thumbsize;

      if (down) newy=yview+1;
      else newy=yview-1;

      if (newy<0) newy=0;
      else if (newy>maxy) newy=maxy;

wxLogMessage(wxT("vMyFrame::Scroll GetSize(%i, %i) GetVirtualSize(%i, %i) GetScrollPixelsPerUnit(%i, %i) GetViewStart(%i, %i) newy=%i maxy=%i totalsize=%i thumbsize=%i)"), xsize, ysize, vxsize, vysize, xpixunit, ypixunit, xview, yview, newy, maxy, totalsize, thumbsize);

      m_tree->SetScrollbars(xpixunit, ypixunit, (vxsize/xpixunit), (vysize/ypixunit), xview, newy);
//    m_tree->Scroll(xview, newy);
}



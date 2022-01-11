/////////////////////////////////////////////////////////////////////////////
// Name:        samples/notebook/notebook.cpp
// Purpose:     a sample demonstrating notebook usage
// Author:      Julian Smart
// Modified by: Dimitri Schoolwerth
// Created:     26/10/98
// RCS-ID:      $Id: notebook.cpp,v 1.11.2.1 2002/11/11 13:16:15 VZ Exp $
// Copyright:   (c) 1998-2002 wxWindows team
// License:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/imaglist.h"
#include "wx/artprov.h"
#include "notebook.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    // Create the main window
    MyFrame *frame = new MyFrame( wxT("Notebook sample") );

    // Problem with generic wxNotebook implementation whereby it doesn't size
    // properly unless you set the size again
#if defined(__WIN16__) || defined(__WXMOTIF__)
    int width, height;
    frame->GetSize(& width, & height);
    frame->SetSize(-1, -1, width, height);
#endif

    frame->Show();

    return TRUE;
}

MyNotebook::MyNotebook(wxWindow *parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size, long style)
    : wxNotebook(parent, id, pos, size, style)
{
    // Empty
}


ListPage::ListPage(wxWindow *parent, wxWindowID id, wxString name)
  : wxPanel(parent, id)
{
  wxBoxSizer *szr = new wxBoxSizer(wxVERTICAL);
  m_lc = new wxListCtrl(this, -1, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
  szr->Add(m_lc, 1, wxEXPAND);
  m_lc->SetAutoLayout(true);
  SetSizer(szr);

  m_lc->InsertColumn(0, _("Col 1"), wxLIST_FORMAT_LEFT, 48);
  m_lc->InsertColumn(1, _("Col 2"), wxLIST_FORMAT_LEFT, 48);
  m_lc->InsertColumn(2, _("Col 3"), wxLIST_FORMAT_LEFT, 96);
  m_lc->InsertColumn(3, _("Col 4"), wxLIST_FORMAT_LEFT, 48);
  m_lc->InsertColumn(4, _("Col 5"), wxLIST_FORMAT_LEFT, 48);
  m_lc->InsertColumn(5, _("Col 6"), wxLIST_FORMAT_LEFT, 40);

  for (int i = 0; i < 10; i++) {
    long id = m_lc->InsertItem(i, wxEmptyString);
    m_lc->SetItem(id, 0, name + wxString::Format("C1R%d", i));
    m_lc->SetItem(id, 1, name + wxString::Format("C2R%d", i));
    m_lc->SetItem(id, 2, name + wxString::Format("C3R%d", i));
    m_lc->SetItem(id, 3, name + wxString::Format("C4R%d", i));
    m_lc->SetItem(id, 4, name + wxString::Format("C5R%d", i));
    m_lc->SetItem(id, 5, name + wxString::Format("C6R%d", i));
  }

}

void MyNotebook::CreateInitialPages()
{
    wxPanel *panel = new ListPage(this, -1, "P1");
    AddPage(panel, "Page 1", false);
    panel->Show();

    panel = new ListPage(this, -1, "P2");
    AddPage(panel, "Page 2", false);
    panel->Show();

    panel = new ListPage(this, -1, "P3");
    AddPage(panel, "Page 3", false);
    panel->Show();

    panel = new ListPage(this, -1, "P4");
    AddPage(panel, "Page 4", false);
    panel->Show();

    //SetSelection(1);
}

int MyNotebook::GetIconIndex() const
{
    if (m_imageList)
    {
       int nImages = m_imageList->GetImageCount();
       if (nImages > 0)
       {
           return GetPageCount() % nImages;
       }
    }

    return -1;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size,
                 long style)
    : wxFrame((wxWindow *) NULL, -1, title, pos, size, style)
{
    m_panel = (wxPanel *) NULL;
    m_notebook = (MyNotebook *) NULL;

    // create a dummy image list with a few icons
    wxSize imageSize(32, 32);

    m_imageList
        = new wxImageList( imageSize.GetWidth(), imageSize.GetHeight() );

    m_imageList->Add
        (
            wxArtProvider::GetIcon(wxART_INFORMATION, wxART_OTHER, imageSize)
        );

    m_imageList->Add
        (
            wxArtProvider::GetIcon(wxART_QUESTION, wxART_OTHER, imageSize)
        );

    m_imageList->Add
        (
            wxArtProvider::GetIcon(wxART_WARNING, wxART_OTHER, imageSize)
        );

    m_imageList->Add
        (
            wxArtProvider::GetIcon(wxART_ERROR, wxART_OTHER, imageSize)
        );

    m_panel = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize,
        wxTAB_TRAVERSAL | wxCLIP_CHILDREN | wxNO_BORDER);

    // Create remaining controls

    // must be in sync with Orient enum
    wxString strOrientations[] =
    {
        wxT("&Top"),
        wxT("&Bottom"),
        wxT("&Left"),
        wxT("&Right"),
    };

    wxASSERT_MSG( WXSIZEOF(strOrientations) == ORIENT_MAX,
                  wxT("Forgot to update something") );

    m_radioOrient = new wxRadioBox
        (
            m_panel, ID_RADIO_ORIENT,
            wxT("&Tab orientation"),
            wxDefaultPosition, wxDefaultSize,
            WXSIZEOF(strOrientations), strOrientations,
            1, wxRA_SPECIFY_COLS
        );

    m_chkShowImages = new wxCheckBox( m_panel, ID_CHK_SHOWIMAGES,
        wxT("&Show images") );

    m_btnAddPage = new wxButton( m_panel, ID_BTN_ADD_PAGE, wxT("&Add page") );

    m_btnInsertPage = new wxButton( m_panel, ID_BTN_INSERT_PAGE,
        wxT("&Insert page") );

    m_btnDeleteCurPage = new wxButton( m_panel, ID_BTN_DELETE_CUR_PAGE,
        wxT("&Delete current page") );

    m_btnDeleteLastPage = new wxButton( m_panel, ID_BTN_DELETE_LAST_PAGE,
        wxT("Delete las&t page") );

    m_btnNextPage = new wxButton( m_panel, ID_BTN_NEXT_PAGE,
        wxT("&Next page") );

    m_btnExit = new wxButton( m_panel, wxID_OK, wxT("&Exit") );
    m_btnExit->SetDefault();

    m_notebook = new MyNotebook(m_panel, ID_NOTEBOOK);

    m_text = new wxTextCtrl(m_panel, -1, wxEmptyString,
        wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);

    m_logTargetOld = wxLog::SetActiveTarget( new wxLogTextCtrl(m_text) );

    // Create the notebook's panels
    m_notebook->CreateInitialPages();

    // Set sizers
    m_sizerFrame = new wxBoxSizer(wxVERTICAL);

    m_sizerTop = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *sizerLeft = new wxBoxSizer(wxVERTICAL);
    {
        sizerLeft->Add(m_radioOrient, 0, wxEXPAND);
        sizerLeft->Add(m_chkShowImages, 0, wxEXPAND | wxTOP, 4);

        sizerLeft->Add(0, 0, 1); // Spacer

        sizerLeft->Add(m_btnAddPage, 0, wxEXPAND | (wxTOP | wxBOTTOM), 4);
        sizerLeft->Add(m_btnInsertPage, 0, wxEXPAND | (wxTOP | wxBOTTOM), 4);
        sizerLeft->Add(m_btnDeleteCurPage, 0, wxEXPAND | (wxTOP | wxBOTTOM), 4);
        sizerLeft->Add(m_btnDeleteLastPage, 0, wxEXPAND | (wxTOP | wxBOTTOM), 4);
        sizerLeft->Add(m_btnNextPage, 0, wxEXPAND | (wxTOP | wxBOTTOM), 4);

        sizerLeft->Add(0, 0, 1); // Spacer

        sizerLeft->Add(m_btnExit, 0, wxEXPAND);
    }

    m_sizerTop->Add(sizerLeft, 0, wxEXPAND | wxALL, 4);


    m_sizerFrame->Add(m_sizerTop, 1, wxEXPAND);
    m_sizerFrame->Add(m_text, 0, wxEXPAND);

    ReInitNotebook();

    m_panel->SetSizer(m_sizerFrame);

    m_panel->SetAutoLayout(TRUE);

    m_sizerFrame->Fit(this);

    Centre(wxBOTH);

}

MyFrame::~MyFrame()
{
    delete wxLog::SetActiveTarget(m_logTargetOld);

    if (m_imageList)
    {
        delete m_imageList;
        m_imageList = (wxImageList *) NULL;
    }

}

void MyFrame::ReInitNotebook()
{
    int flags;

    switch ( m_radioOrient->GetSelection() )
    {
        default:
            wxFAIL_MSG( wxT("unknown notebook orientation") );
            // fall through

        case ORIENT_TOP:
            flags = wxNB_TOP;
            break;

        case ORIENT_BOTTOM:
            flags = wxNB_BOTTOM;
            break;

        case ORIENT_LEFT:
            flags = wxNB_LEFT;
            break;

        case ORIENT_RIGHT:
            flags = wxNB_RIGHT;
            break;
    }

    MyNotebook *notebook = m_notebook;

    m_notebook = new MyNotebook(m_panel, ID_NOTEBOOK,
                                wxDefaultPosition, wxDefaultSize,
                                flags);

    if ( m_chkShowImages->IsChecked() )
    {
        m_notebook->SetImageList(m_imageList);
    }

    if (notebook)
    {
        int sel = notebook->GetSelection();

        if (m_sizerNotebook)
        {
            m_sizerTop->Remove(m_sizerNotebook);
        }

        m_notebook->CreateInitialPages();

        delete notebook;

        // restore selection
        if (sel != -1)
        {
            m_notebook->SetSelection(sel);
        }

    }


    m_sizerNotebook = new wxNotebookSizer(m_notebook);
    m_sizerTop->Add(m_sizerNotebook, 1, wxEXPAND | wxALL, 4);
    m_sizerTop->Layout();
}

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_RADIOBOX(ID_RADIO_ORIENT, MyFrame::OnCheckOrRadioBox)
    EVT_CHECKBOX(ID_CHK_SHOWIMAGES, MyFrame::OnCheckOrRadioBox)

    EVT_UPDATE_UI(ID_BTN_DELETE_CUR_PAGE, MyFrame::OnUpdateUIBtnDeleteCurPage)
    EVT_UPDATE_UI(ID_BTN_DELETE_LAST_PAGE, MyFrame::OnUpdateUIBtnDeleteLastPage)

    EVT_NOTEBOOK_PAGE_CHANGED(ID_NOTEBOOK, MyFrame::OnNotebook)
    EVT_NOTEBOOK_PAGE_CHANGING(ID_NOTEBOOK, MyFrame::OnNotebook)

    EVT_IDLE(MyFrame::OnIdle)
END_EVENT_TABLE()

void MyFrame::OnCheckOrRadioBox(wxCommandEvent& event)
{
        ReInitNotebook();
}

void MyFrame::OnNotebook(wxNotebookEvent& event)
{
    wxString str = wxT("Unknown notebook event");

    wxEventType eventType = event.GetEventType();

    if (eventType == wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED)
    {
        str = wxT("Notebook changed");
    }
    else if (eventType == wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING)
    {
        int idx = event.GetOldSelection();
        if ( idx != -1 && m_notebook->GetPageText(idx) == VETO_PAGE_NAME )
        {
            if
            (
                wxMessageBox(
                wxT("Are you sure you want to leave this notebook page?\n")
                wxT("(This demonstrates veto-ing)"),
                          wxT("Notebook sample"),
                          wxICON_QUESTION | wxYES_NO, this) != wxYES )
            {
                event.Veto();

                return;
            }

        }

        str = wxT("Notebook changing");
    }

    static int s_numNotebookEvents = 0;

    wxLogMessage(wxT("Notebook event #%d: %s (%d)"),
        s_numNotebookEvents++, str.c_str(), eventType);

    m_text->SetInsertionPointEnd();

    event.Skip();
}

void MyFrame::OnIdle( wxIdleEvent& WXUNUSED(event) )
{
    static int s_nPages = -1;
    static int s_nSel = -1;

    int nPages = m_notebook->GetPageCount();
    int nSel = m_notebook->GetSelection();
    if ( nPages != s_nPages || nSel != s_nSel )
    {
        s_nPages = nPages;
        s_nSel = nSel;

        wxString title;
        title.Printf(wxT("Notebook (%d pages, selection: %d)"), nPages, nSel);

        SetTitle(title);
    }
}

void MyFrame::OnUpdateUIBtnDeleteCurPage(wxUpdateUIEvent& event)
{
    event.Enable( m_notebook->GetSelection() != -1 );
}

void MyFrame::OnUpdateUIBtnDeleteLastPage(wxUpdateUIEvent& event)
{
    event.Enable( m_notebook->GetPageCount() != 0 );
}

 	  	 

/////////////////////////////////////////////////////////////////////////////
// Name:        samples/menu.cpp
// Purpose:     wxMenu/wxMenuBar sample
// Author:      Vadim Zeitlin
// Modified by:
// Created:     01.11.99
// RCS-ID:      $Id: menu.cpp,v 1.1.1.1 2007/07/18 12:57:22 builder Exp $
// Copyright:   (c) 1999 Vadim Zeitlin
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/app.h"
#include "wx/frame.h"
#include "wx/menu.h"
#include "wx/msgdlg.h"
#include "wx/log.h"
#include "wx/textctrl.h"
#include "wx/textdlg.h"
#include "wx/checklst.h"
#include "wx/window.h"
#include "wx/sizer.h"
#include "wx/button.h"
#include "wx/stattext.h"
#endif

#if !wxUSE_MENUS
// nice try...
#error "menu sample requires wxUSE_MENUS=1"
#endif // wxUSE_MENUS

// not all ports have support for EVT_CONTEXT_MENU yet, don't define
// USE_CONTEXT_MENU for those which don't
#if defined(__WXMOTIF__) || defined(__WXPM__) || defined(__WXX11__) || defined(__WXMGL__)
#define USE_CONTEXT_MENU 0
#else
#define USE_CONTEXT_MENU 1
#endif

// this sample is usefull when new port is developed
// and usually new port has majority of flags turned off
#if wxUSE_LOG && wxUSE_TEXTCTRL
#define USE_LOG_WINDOW 1
#else
#define USE_LOG_WINDOW 0
#endif

#if wxUSE_OWNER_DRAWN || defined(__WXGTK__)
#include "copy.xpm"
#endif

// ----------------------------------------------------------------------------
// classes
// ----------------------------------------------------------------------------

// Define a new application
class MyApp: public wxApp
{
public:
  bool OnInit();
};

// Define a new frame
class MyFrame: public wxFrame
{
public:
  MyFrame();

  virtual ~MyFrame();

  void LogMenuEvent(const wxCommandEvent& event);

protected:
  void OnQuit(wxCommandEvent& event);
#if USE_LOG_WINDOW
  void OnClearLog(wxCommandEvent& event);
  void OnClearLogUpdateUI(wxUpdateUIEvent& event);
#endif // USE_LOG_WINDOW

  void OnAbout(wxCommandEvent& event);

#if USE_CONTEXT_MENU
  void OnContextMenu(wxContextMenuEvent& event);
#else
  void OnRightUp(wxMouseEvent& event)
  { ShowContextMenu(event.GetPosition()); }
#endif

  void OnMenuOpen(wxMenuEvent& event)
  {
#if USE_LOG_WINDOW
    LogMenuOpenOrClose(event, _T("opened")); event.Skip();
#endif
  }
  void OnMenuClose(wxMenuEvent& event)
  {
#if USE_LOG_WINDOW
    LogMenuOpenOrClose(event, _T("closed")); event.Skip();
#endif
  }

  void OnUpdateCheckMenuItemUI(wxUpdateUIEvent& event);

  void OnSize(wxSizeEvent& event);

private:
  void LogMenuOpenOrClose(const wxMenuEvent& event, const wxChar *what);
  void ShowContextMenu(const wxPoint& pos);

  // the menu previously detached from the menubar (may be NULL)
  wxMenu *m_menu;

  // the count of dummy menus already created
  size_t m_countDummy;

#if USE_LOG_WINDOW
  // the control used for logging
  wxTextCtrl *m_textctrl;
#endif

  // the previous log target
  wxLog *m_logOld;

  DECLARE_EVENT_TABLE()
};

// A small helper class which intercepts all menu events and logs them
class MyEvtHandler : public wxEvtHandler
{
public:
  MyEvtHandler(MyFrame *frame) { m_frame = frame; }

  void OnMenuEvent(wxCommandEvent& event)
  {
    m_frame->LogMenuEvent(event);

    event.Skip();
  }

private:
  MyFrame *m_frame;

  DECLARE_EVENT_TABLE()
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

enum
{
  Menu_File_Quit = wxID_EXIT,
#if USE_LOG_WINDOW
  Menu_File_ClearLog = 100,
#endif

  Menu_Help_About = wxID_ABOUT,
  Menu_Help_About2 = 4000,
  Menu_Help_About3,
  Menu_Help_About4,
  Menu_Help_About5,

  Menu_Popup_ToBeDeleted = 2000,
  Menu_Popup_ToBeGreyed,
  Menu_Popup_ToBeChecked,
  Menu_Popup_Submenu,

  Menu_Max
};

// ----------------------------------------------------------------------------
// event tables
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(Menu_File_Quit,     MyFrame::OnQuit)
#if USE_LOG_WINDOW
EVT_MENU(Menu_File_ClearLog, MyFrame::OnClearLog)
EVT_UPDATE_UI(Menu_File_ClearLog, MyFrame::OnClearLogUpdateUI)
#endif

EVT_MENU(Menu_Help_About, MyFrame::OnAbout)


#if USE_CONTEXT_MENU
EVT_CONTEXT_MENU(MyFrame::OnContextMenu)
#else
EVT_RIGHT_UP(MyFrame::OnRightUp)
#endif

EVT_MENU_OPEN(MyFrame::OnMenuOpen)
EVT_MENU_CLOSE(MyFrame::OnMenuClose)

EVT_SIZE(MyFrame::OnSize)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(MyEvtHandler, wxEvtHandler)
EVT_MENU(wxID_ANY, MyEvtHandler::OnMenuEvent)
END_EVENT_TABLE()


// ============================================================================
// AboutDialog
// ============================================================================
class AboutDialog : public wxDialog {

public:

  AboutDialog::AboutDialog(wxWindow* parent, wxWindowID id) 
    : wxDialog(parent, id, wxT(""), wxDefaultPosition, wxSize(480, 318), wxDEFAULT_DIALOG_STYLE, wxT("dialogBox")) {

      topsizer_ = new wxBoxSizer( wxVERTICAL );
      topsizer_->Add(new wxStaticText(this, wxID_ANY, wxString(wxT("Running Version: ")) + wxVERSION_STRING));
      
      wxCheckListBox* box = new wxCheckListBox(this, wxID_ANY);
      box->Append("now the rightclick context menu is broken.");
      topsizer_->Add(box, 0, wxALIGN_CENTER);

      //ok button.
      topsizer_->Add(new wxButton(this, wxID_OK, wxT("OK")), 0, wxALIGN_CENTER);

      SetSizer( topsizer_ );
      topsizer_->Fit( this );
      topsizer_->SetSizeHints( this );

      Refresh();
  }

private:
  wxBoxSizer* topsizer_;
};






// ----------------------------------------------------------------------------
// MyApp
// ----------------------------------------------------------------------------

IMPLEMENT_APP(MyApp)

// The `main program' equivalent, creating the windows and returning the
// main frame
bool MyApp::OnInit()
{
  // Create the main frame window
  MyFrame* frame = new MyFrame;

  frame->Show(true);

#if wxUSE_STATUSBAR
  frame->SetStatusText(_T("Welcome to wxWidgets menu sample"));
#endif // wxUSE_STATUSBAR

  SetTopWindow(frame);

  return true;
}

// ----------------------------------------------------------------------------
// MyFrame
// ----------------------------------------------------------------------------

// Define my frame constructor
MyFrame::MyFrame()
: wxFrame((wxFrame *)NULL, wxID_ANY, _T("wxWidgets menu sample"))
{
#if USE_LOG_WINDOW
  m_textctrl = NULL;
#endif
  m_menu = NULL;
  m_countDummy = 0;
  m_logOld = NULL;

#if wxUSE_STATUSBAR
  CreateStatusBar();
#endif // wxUSE_STATUSBAR


  wxMenu *helpMenu = new wxMenu;
  helpMenu->Append(Menu_Help_About, _T("&About\tF1"), _T("About menu sample"));

  wxMenuBar* menuBar = new wxMenuBar( wxMB_DOCKABLE );

  menuBar->Append(helpMenu, _T("Help"));


  // associate the menu bar with the frame
  SetMenuBar(menuBar);

  // intercept all menu events and log them in this custom event handler
  PushEventHandler(new MyEvtHandler(this));

#if USE_LOG_WINDOW
  // create the log text window
  m_textctrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
    wxDefaultPosition, wxDefaultSize,
    wxTE_MULTILINE);
  m_textctrl->SetEditable(false);

  wxLog::SetTimestamp(NULL);
  m_logOld = wxLog::SetActiveTarget(new wxLogTextCtrl(m_textctrl));


  wxLogMessage(_T("Brief explanations: the commands or the \"Menu\" menu ")
    _T("append/insert/delete items to/from the last menu.\n")
    _T("The commands from \"Menubar\" menu work with the ")
    _T("menubar itself.\n\n")
    _T("Right click the band below to test popup menus.\n"));
#endif
#ifdef __POCKETPC__
  EnableContextMenu();
#endif
}

MyFrame::~MyFrame()
{
  delete m_menu;

  // delete the event handler installed in ctor
  PopEventHandler(true);

#if USE_LOG_WINDOW
  // restore old logger
  delete wxLog::SetActiveTarget(m_logOld);
#endif
}




void MyFrame::LogMenuEvent(const wxCommandEvent& event)
{
  int id = event.GetId();

  wxString msg = wxString::Format(_T("Menu command %d"), id);

  // catch all checkable menubar items and also the check item from the popup
  // menu
  wxMenuItem *item = GetMenuBar()->FindItem(id);
  if ( (item && item->IsCheckable()) || id == Menu_Popup_ToBeChecked )
  {
    msg += wxString::Format(_T(" (the item is currently %schecked)"),
      event.IsChecked() ? _T("") : _T("not "));
  }

  wxLogMessage(msg);
}

// ----------------------------------------------------------------------------
// menu callbacks
// ----------------------------------------------------------------------------

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}

#if USE_LOG_WINDOW

void MyFrame::OnClearLog(wxCommandEvent& WXUNUSED(event))
{
  m_textctrl->Clear();
}

void MyFrame::OnClearLogUpdateUI(wxUpdateUIEvent& event)
{
  // if we only enable this item when the log window is empty, we never see
  // it in the disable state as a message is logged whenever the menu is
  // opened, so we disable it if there is not "much" text in the window
  event.Enable( m_textctrl->GetNumberOfLines() > 5 );
}

#endif // USE_LOG_WINDOW

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
  AboutDialog dlg(this, wxID_ANY);
  dlg.ShowModal();
}









void MyFrame::ShowContextMenu(const wxPoint& pos)
{
  wxMenu menu;

  menu.Append(Menu_Help_About, _T("About"));
  menu.Append(Menu_Help_About2, _T("About2"));
  menu.Append(Menu_Help_About3, _T("About3"));
  menu.Append(Menu_Help_About4, _T("About4"));
  menu.Append(Menu_Help_About5, _T("About5"));
  menu.Append(Menu_Popup_ToBeDeleted, _T("To be &deleted"));
  menu.AppendCheckItem(Menu_Popup_ToBeChecked, _T("To be &checked"));
  menu.Append(Menu_Popup_ToBeGreyed, _T("To be &greyed"),
    _T("This menu item should be initially greyed out"));
  menu.AppendSeparator();
  menu.Append(Menu_File_Quit, _T("E&xit"));

  menu.Delete(Menu_Popup_ToBeDeleted);
  menu.Check(Menu_Popup_ToBeChecked, true);
  menu.Enable(Menu_Popup_ToBeGreyed, false);

  PopupMenu(&menu, pos.x, pos.y);

  // test for destroying items in popup menus
#if 0 // doesn't work in wxGTK!
  menu.Destroy(Menu_Popup_Submenu);

  PopupMenu( &menu, event.GetX(), event.GetY() );
#endif // 0
}


#if USE_LOG_WINDOW
void MyFrame::LogMenuOpenOrClose(const wxMenuEvent& event, const wxChar *what)
{
  wxString msg;
  msg << _T("A ")
    << ( event.IsPopup() ? _T("popup ") : _T("") )
    << _T("menu has been ")
    << what
    << _T(".");

  wxLogStatus(this, msg.c_str());
}
#endif


#if USE_CONTEXT_MENU
void MyFrame::OnContextMenu(wxContextMenuEvent& event)
{
  wxPoint point = event.GetPosition();
  // If from keyboard
  if (point.x == -1 && point.y == -1) {
    wxSize size = GetSize();
    point.x = size.x / 2;
    point.y = size.y / 2;
  } else {
    point = ScreenToClient(point);
  }
  ShowContextMenu(point);
}
#endif

void MyFrame::OnSize(wxSizeEvent& WXUNUSED(event))
{
#if USE_LOG_WINDOW
  if ( !m_textctrl )
    return;

  // leave a band below for popup menu testing
  wxSize size = GetClientSize();
  m_textctrl->SetSize(0, 0, size.x, (3*size.y)/4);
#endif

  // this is really ugly but we have to do it as we can't just call
  // event.Skip() because wxFrameBase would make the text control fill the
  // entire frame then
#ifdef __WXUNIVERSAL__
  PositionMenuBar();
#endif // __WXUNIVERSAL__
}


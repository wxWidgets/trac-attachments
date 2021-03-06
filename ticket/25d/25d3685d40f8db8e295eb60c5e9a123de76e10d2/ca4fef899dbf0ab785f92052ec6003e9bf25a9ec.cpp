/////////////////////////////////////////////////////////////////////////////
// Name:        wizard.cpp
// Purpose:     wxWidgets sample demonstrating wxWizard control
// Author:      Vadim Zeitlin
// Modified by: Robert Vazan (sizers)
// Created:     15.08.99
// RCS-ID:      $Id$
// Copyright:   (c) Vadim Zeitlin
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

// for all others, include the necessary headers
#ifndef WX_PRECOMP
    #include "wx/frame.h"
    #include "wx/stattext.h"
    #include "wx/log.h"
    #include "wx/app.h"
    #include "wx/checkbox.h"
    #include "wx/checklst.h"
    #include "wx/msgdlg.h"
    #include "wx/radiobox.h"
    #include "wx/menu.h"
    #include "wx/sizer.h"
#endif

#include "wx/textctrl.h"
#include "wx/wizard.h"

#include "wiztest.xpm"
#include "wiztest2.xpm"

#include "../sample.xpm"

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// ids for menu items
enum
{
    Wizard_About = wxID_ABOUT,
    Wizard_Quit = wxID_EXIT,
    Wizard_RunModal = wxID_HIGHEST,
    
    Wizard_RunNoSizer,
    Wizard_RunModeless,
    
    Wizard_LargeWizard,
    Wizard_ExpandBitmap
};

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    // override base class virtuals
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title);
    
    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnRunWizard(wxCommandEvent& event);
    void OnRunWizardNoSizer(wxCommandEvent& event);
    void OnRunWizardModeless(wxCommandEvent& event);
    void OnWizardCancel(wxWizardEvent& event);
    void OnWizardFinished(wxWizardEvent& event);
    
private:
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
};

// ----------------------------------------------------------------------------
// our wizard
// ----------------------------------------------------------------------------

class MyWizard : public wxWizard
{
public:
    MyWizard(wxFrame *frame, bool useSizer = true);
    
    wxWizardPage *GetFirstPage() const { return m_page1; }
    
private:
    wxWizardPageSimple *m_page1;
};

// ----------------------------------------------------------------------------
// some pages for our wizard
// ----------------------------------------------------------------------------

// This shows how to simply control the validity of the user input by just
// overriding TransferDataFromWindow() - of course, in a real program, the
// check wouldn't be so trivial and the data will be probably saved somewhere
// too.
//
// It also shows how to use a different bitmap for one of the pages.
class wxValidationPage : public wxWizardPageSimple
{
public:
    wxValidationPage(wxWizard *parent) : wxWizardPageSimple(parent)
    {
        m_bitmap = wxBitmap(wiztest2_xpm);
        
        m_checkbox = new wxCheckBox(this, wxID_ANY, wxT("&Check me"));
        
        wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
        mainSizer->Add(
                       new wxStaticText(this, wxID_ANY,
                                        wxT("You need to check the checkbox\n")
                                        wxT("below before going to the next page\n")),
                       0,
                       wxALL,
                       5
                       );
        
        mainSizer->Add(
                       m_checkbox,
                       0, // No stretching
                       wxALL,
                       5 // Border
                       );
        SetSizerAndFit(mainSizer);
    }
    
    virtual bool TransferDataFromWindow()
    {
        if ( !m_checkbox->GetValue() )
        {
            wxMessageBox(wxT("Check the checkbox first!"), wxT("No way"),
                         wxICON_WARNING | wxOK, this);
            
            return false;
        }
        
        return true;
    }
    
private:
    wxCheckBox *m_checkbox;
};

// This is a more complicated example of validity checking: using events we may
// allow to return to the previous page, but not to proceed. It also
// demonstrates how to intercept [Cancel] button press.

// ***COZ*** start
#include <wx/dcclient.h>
#include <wx/tipwin.h>
class Buoy  : public wxObject  {
public:
    wxPoint pos;		//device units
    wxRegion region;	//device units
    wxString name;
};
#define ID_PANEL 10004
WX_DECLARE_OBJARRAY(Buoy,BuoyArray);
#include <wx/arrimpl.cpp> // This is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(BuoyArray);
// ***COZ*** end

class wxRadioboxPage : public wxWizardPageSimple
{
public:
    // directions in which we allow the user to proceed from this page
    enum
    {
        Forward, Backward, Both, Neither
    };
    
    
    wxRadioboxPage(wxWizard *parent) : wxWizardPageSimple(parent)
    {
        // should correspond to the enum above
        //        static wxString choices[] = { "forward", "backward", "both", "neither" };
        // The above syntax can cause an internal compiler error with gcc.
        wxString choices[4];
        choices[0] = wxT("forward");
        choices[1] = wxT("backward");
        choices[2] = wxT("both");
        choices[3] = wxT("neither");
        
        m_radio = new wxRadioBox(this, wxID_ANY, wxT("Allow to proceed:"),
                                 wxDefaultPosition, wxDefaultSize,
                                 WXSIZEOF(choices), choices,
                                 1, wxRA_SPECIFY_COLS);
        m_radio->SetSelection(Both);
		wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
        
		///////////////////////// ***COZ*** start
		m_Panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize(200, 200), wxNO_BORDER|wxTAB_TRAVERSAL );
		m_Panel->SetBackgroundColour(wxColour(255, 255, 255));
        
		int x,y;
		m_BuoyArray.Alloc(200);
		for (y=0;y<10;y++) {
			for (x=0;x<10;x++) {
				wxPoint rc_pt;
				rc_pt.x = (x * 11) + 10;
				rc_pt.y = (y * 11) + 10;
				wxVector<wxPoint> points;
				points.push_back( wxPoint(rc_pt.x-4,rc_pt.y) );
				points.push_back( wxPoint(rc_pt.x,rc_pt.y-4) );
				points.push_back( wxPoint(rc_pt.x+4,rc_pt.y) );
				points.push_back( wxPoint(rc_pt.x,rc_pt.y+4) );
				Buoy b;
				b.pos = rc_pt;
				b.region = wxRegion(points.size(), &points[0],wxODDEVEN_RULE);
				b.name = "Buoy " + wxString::Format(wxT("%i"),x+1) + "," + wxString::Format(wxT("%i"),y+1);
				m_BuoyArray.Add(b);
			}
		}
		m_p_InfoPopWin = NULL;
		// Connect events and objects
		m_Panel->Connect(wxID_ANY, wxEVT_PAINT, wxPaintEventHandler(wxRadioboxPage::OnPaint), NULL, this);
		m_Panel->Connect(wxID_ANY, wxEVT_MOTION, wxMouseEventHandler(wxRadioboxPage::OnMotion), NULL, this);
		mainSizer->Add(m_Panel, 0, wxALIGN_LEFT, 0);
		// ***COZ*** end
        
        mainSizer->Add(
                       m_radio,
                       0, // No stretching
                       wxALL,
                       5 // Border
                       );
        
        SetSizerAndFit(mainSizer);
    }
    
    // wizard event handlers
    void OnWizardCancel(wxWizardEvent& event)
    {
        if ( wxMessageBox(wxT("Do you really want to cancel?"), wxT("Question"),
                          wxICON_QUESTION | wxYES_NO, this) != wxYES )
        {
            // not confirmed
            event.Veto();
        }
    }
    
    void OnWizardPageChanging(wxWizardEvent& event)
    {
        int sel = m_radio->GetSelection();
        
        if ( sel == Both )
            return;
        
        if ( event.GetDirection() && sel == Forward )
            return;
        
        if ( !event.GetDirection() && sel == Backward )
            return;
        
        wxMessageBox(wxT("You can't go there"), wxT("Not allowed"),
                     wxICON_WARNING | wxOK, this);
        
        event.Veto();
    }
    //////////////// ***COZ*** start
	void OnPaint( wxPaintEvent& event )
	{
		//wxPaintDC dc(wxDynamicCast(event.GetEventObject(), wxWindow));
		wxPaintDC dc(m_Panel);
		dc.SetUserScale(1,1);
		int idx;
        
		for (size_t i = 0; i < m_BuoyArray.GetCount() ; i++) {
			idx = i;
			dc.SetBrush(wxColor(255,255,0));
			dc.SetPen( wxPen( wxColor(0,0,0), 1 ) );
            
			wxVector<wxPoint> points;
			points.push_back( wxPoint(m_BuoyArray.Item(idx).pos.x-4,m_BuoyArray.Item(idx).pos.y) );
			points.push_back( wxPoint(m_BuoyArray.Item(idx).pos.x,m_BuoyArray.Item(idx).pos.y-4) );
			points.push_back( wxPoint(m_BuoyArray.Item(idx).pos.x+4,m_BuoyArray.Item(idx).pos.y) );
			points.push_back( wxPoint(m_BuoyArray.Item(idx).pos.x,m_BuoyArray.Item(idx).pos.y+4) );
			dc.DrawPolygon( points.size(), &points[0], 0,0);
		}
	}
    
	void OnMotion( wxMouseEvent& event )
	{
		wxPoint position = event.GetPosition();
		size_t count = m_BuoyArray.GetCount();
		for (size_t i = 0; i < count; i++) {
			if (m_BuoyArray.Item(i).region.Contains(position) == wxInRegion) {
				if (m_p_InfoPopWin == NULL) {
					// raise the tip window
					Buoy &buoy = m_BuoyArray.Item(i);
					wxRect rc = buoy.region.GetBox();
					ClientToScreen(&rc.x,&rc.y);
					m_p_InfoPopWin = new wxTipWindow(
                                                     m_Panel,
                                                     wxString::Format("*****************\n%s\n=====================",buoy.name),
                                                     200,&m_p_InfoPopWin,&rc );
				}
			}
		}
	}
private:
	wxPanel *m_Panel;
	BuoyArray m_BuoyArray;
	wxTipWindow* m_p_InfoPopWin;
    //////////////////////////////////////////////// ***COZ*** end
private:
    wxRadioBox *m_radio;
    DECLARE_EVENT_TABLE()
};

// This shows how to dynamically (i.e. during run-time) arrange the page order.
class wxCheckboxPage : public wxWizardPage
{
public:
    wxCheckboxPage(wxWizard *parent,
                   wxWizardPage *prev,
                   wxWizardPage *next)
    : wxWizardPage(parent)
    {
        m_prev = prev;
        m_next = next;
        
        wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
        
        mainSizer->Add(
                       new wxStaticText(this, wxID_ANY, wxT("Try checking the box below and\n")
                                        wxT("then going back and clearing it")),
                       0, // No vertical stretching
                       wxALL,
                       5 // Border width
                       );
        
        m_checkbox = new wxCheckBox(this, wxID_ANY, wxT("&Skip the next page"));
        mainSizer->Add(
                       m_checkbox,
                       0, // No vertical stretching
                       wxALL,
                       5 // Border width
                       );
        
#if wxUSE_CHECKLISTBOX
        static const wxChar *aszChoices[] =
        {
            wxT("Zeroth"),
            wxT("First"),
            wxT("Second"),
            wxT("Third"),
            wxT("Fourth"),
            wxT("Fifth"),
            wxT("Sixth"),
            wxT("Seventh"),
            wxT("Eighth"),
            wxT("Nineth")
        };
        
        m_checklistbox = new wxCheckListBox
        (
         this,
         wxID_ANY,
         wxDefaultPosition,
         wxSize(100,100),
         wxArrayString(WXSIZEOF(aszChoices), aszChoices)
         );
        
        mainSizer->Add(
                       m_checklistbox,
                       0, // No vertical stretching
                       wxALL,
                       5 // Border width
                       );
#endif // wxUSE_CHECKLISTBOX
        
        wxSize textSize = wxSize(150, 200);
        if (((wxFrame*) wxTheApp->GetTopWindow())->GetMenuBar()->IsChecked(Wizard_LargeWizard))
            textSize = wxSize(150, wxGetClientDisplayRect().GetHeight() - 200);
        
        
        wxTextCtrl* textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, textSize, wxTE_MULTILINE);
        mainSizer->Add(textCtrl, 0, wxALL|wxEXPAND, 5);
        
        SetSizerAndFit(mainSizer);
    }
    
    // implement wxWizardPage functions
    virtual wxWizardPage *GetPrev() const { return m_prev; }
    virtual wxWizardPage *GetNext() const
    {
        return m_checkbox->GetValue() ? m_next->GetNext() : m_next;
    }
    
private:
    wxWizardPage *m_prev,
    *m_next;
    
    wxCheckBox *m_checkbox;
#if wxUSE_CHECKLISTBOX
    wxCheckListBox *m_checklistbox;
#endif
};

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// event tables and such
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(Wizard_Quit,         MyFrame::OnQuit)
EVT_MENU(Wizard_About,        MyFrame::OnAbout)
EVT_MENU(Wizard_RunModal,     MyFrame::OnRunWizard)
EVT_MENU(Wizard_RunNoSizer,   MyFrame::OnRunWizardNoSizer)
EVT_MENU(Wizard_RunModeless,  MyFrame::OnRunWizardModeless)

EVT_WIZARD_CANCEL(wxID_ANY,   MyFrame::OnWizardCancel)
EVT_WIZARD_FINISHED(wxID_ANY, MyFrame::OnWizardFinished)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(wxRadioboxPage, wxWizardPageSimple)
EVT_WIZARD_PAGE_CHANGING(wxID_ANY, wxRadioboxPage::OnWizardPageChanging)
EVT_WIZARD_CANCEL(wxID_ANY, wxRadioboxPage::OnWizardCancel)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// `Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;
    
    MyFrame *frame = new MyFrame(wxT("wxWizard Sample"));
    
    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);
    
    // we're done
    return true;
}

// ----------------------------------------------------------------------------
// MyWizard
// ----------------------------------------------------------------------------

MyWizard::MyWizard(wxFrame *frame, bool useSizer)
{
    SetExtraStyle(wxWIZARD_EX_HELPBUTTON);
    
    Create(frame,wxID_ANY,wxT("Absolutely Useless Wizard"),
           wxBitmap(wiztest_xpm),wxDefaultPosition,
           wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
    SetIcon(wxICON(sample));
    
    // Allow the bitmap to be expanded to fit the page height
    if (frame->GetMenuBar()->IsChecked(Wizard_ExpandBitmap))
        SetBitmapPlacement(wxWIZARD_VALIGN_CENTRE);
    
    // Enable scrolling adaptation
    if (frame->GetMenuBar()->IsChecked(Wizard_LargeWizard))
        SetLayoutAdaptationMode(wxDIALOG_ADAPTATION_MODE_ENABLED);
    
    // a wizard page may be either an object of predefined class
    m_page1 = new wxWizardPageSimple(this);
    
    /* wxStaticText *text = */ new wxStaticText(m_page1, wxID_ANY,
                                                wxT("This wizard doesn't help you\nto do anything at all.\n")
                                                wxT("\n")
                                                wxT("The next pages will present you\nwith more useless controls."),
                                                wxPoint(5,5)
                                                );
    
    // ... or a derived class
    wxRadioboxPage *page3 = new wxRadioboxPage(this);
    wxValidationPage *page4 = new wxValidationPage(this);
    
    // set the page order using a convenience function - could also use
    // SetNext/Prev directly as below
    wxWizardPageSimple::Chain(page3, page4);
    
    // this page is not a wxWizardPageSimple, so we use SetNext/Prev to insert
    // it into the chain of pages
    wxCheckboxPage *page2 = new wxCheckboxPage(this, m_page1, page3);
    m_page1->SetNext(page2);
    page3->SetPrev(page2);
    
    if ( useSizer )
    {
        // allow the wizard to size itself around the pages
        GetPageAreaSizer()->Add(m_page1);
    }
}

// ----------------------------------------------------------------------------
// MyFrame
// ----------------------------------------------------------------------------

MyFrame::MyFrame(const wxString& title)
:wxFrame((wxFrame *)NULL, wxID_ANY, title,
         wxDefaultPosition, wxSize(250, 150))  // small frame
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(Wizard_RunModal, wxT("&Run wizard modal...\tCtrl-R"));
    menuFile->Append(Wizard_RunNoSizer, wxT("Run wizard &without sizer..."));
    menuFile->Append(Wizard_RunModeless, wxT("Run wizard &modeless..."));
    menuFile->AppendSeparator();
    menuFile->Append(Wizard_Quit, wxT("E&xit\tAlt-X"), wxT("Quit this program"));
    
    wxMenu *menuOptions = new wxMenu;
    menuOptions->AppendCheckItem(Wizard_LargeWizard, wxT("&Scroll Wizard Pages"));
    menuOptions->AppendCheckItem(Wizard_ExpandBitmap, wxT("Si&ze Bitmap To Page"));
    
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Wizard_About, wxT("&About...\tF1"), wxT("Show about dialog"));
    
    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, wxT("&File"));
    menuBar->Append(menuOptions, wxT("&Options"));
    menuBar->Append(helpMenu, wxT("&Help"));
    
    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
    
    // also create status bar which we use in OnWizardCancel
#if wxUSE_STATUSBAR
    CreateStatusBar();
#endif // wxUSE_STATUSBAR
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxT("Demo of wxWizard class\n")
                 wxT("(c) 1999, 2000 Vadim Zeitlin"),
                 wxT("About wxWizard sample"), wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnRunWizard(wxCommandEvent& WXUNUSED(event))
{
    MyWizard wizard(this);
    
    wizard.RunWizard(wizard.GetFirstPage());
}

void MyFrame::OnRunWizardNoSizer(wxCommandEvent& WXUNUSED(event))
{
    MyWizard wizard(this, false);
    
    wizard.RunWizard(wizard.GetFirstPage());
}

void MyFrame::OnRunWizardModeless(wxCommandEvent& WXUNUSED(event))
{
    MyWizard *wizard = new MyWizard(this);
    wizard->ShowPage(wizard->GetFirstPage());
    wizard->Show(true);
}

void MyFrame::OnWizardFinished(wxWizardEvent& WXUNUSED(event))
{
    wxMessageBox(wxT("The wizard finished successfully."), wxT("Wizard notification"));
}

void MyFrame::OnWizardCancel(wxWizardEvent& WXUNUSED(event))
{
    wxMessageBox(wxT("The wizard was cancelled."), wxT("Wizard notification"));
}

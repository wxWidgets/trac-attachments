#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/app.h>
#include <wx/frame.h>
#include <wx/listbox.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/dnd.h>
#include <wx/intl.h>
#include <wx/string.h>


class testApp : public wxApp
{
    public:
        virtual bool OnInit();
};


class testFrame: public wxFrame
{
    public:

        testFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~testFrame();

    private:

        void OnQuit(wxCommandEvent& event);

        wxListBox* lbPlain;
        wxListBox* lbStatic1;
        wxListBox* lbStatic2;

        DECLARE_EVENT_TABLE()
};


class DF : public wxFileDropTarget
{
    public:

        DF ( wxListBox * lb_target );

        virtual bool OnDropFiles ( wxCoord x, wxCoord y, const wxArrayString & files );

    protected:

        wxListBox * m_target;
};


IMPLEMENT_APP(testApp);


bool testApp::OnInit()
{
    testFrame* Frame = new testFrame(0);
    Frame->Show();
    SetTopWindow(Frame);
    
    return true;
}


//#include <wx/msgdlg.h>


BEGIN_EVENT_TABLE(testFrame,wxFrame)
END_EVENT_TABLE()


testFrame::testFrame(wxWindow* parent,wxWindowID id)
{
    wxBoxSizer* bsOuter;
    wxPanel* 	Panel1;
    wxBoxSizer* bsInner;
    wxBoxSizer* bsPlain;
    wxStaticBoxSizer* bsStaticBox1;
    wxStaticBoxSizer* bsStaticBox2;
  
    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));

    // Create the basic foundation: frame contains a standard box sizer (bsOuter)
    // which contains a panel (Panel1) which contains a standard box sizer (bsInner)

    bsOuter = new wxBoxSizer(wxHORIZONTAL);
    Panel1 = new wxPanel(this, wxID_ANY);
    bsInner = new wxBoxSizer(wxHORIZONTAL);
 
    // Create a standard sizer containing a listbox and place it in the inner sizer    

    bsPlain = new wxBoxSizer(wxHORIZONTAL);
    lbPlain = new wxListBox(Panel1, wxID_ANY);
    lbPlain->SetMinSize(wxSize(200,400));
    bsPlain->Add(lbPlain, 1, wxALL|wxEXPAND, 5);
    bsInner->Add(bsPlain, 1, wxALL|wxEXPAND, 5);

    // Create a Static Box sizer containing a listbox and place it in the inner sizer
    // (next to the "plain" sizer created above). Note that the list box it contains is
    // created according to the pre-2.9.1 rules, i.e., parent is Panel1

    bsStaticBox1 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Static Box Sizer 1"));
    lbStatic1 = new wxListBox(Panel1, wxID_ANY);
    bsStaticBox1->Add(lbStatic1, 1, wxALL|wxEXPAND, 5);
    bsInner->Add(bsStaticBox1, 1, wxALL|wxEXPAND, 5);

    // Create another Static Box sizer containing a listbox and place it next to the
    // bsStaticBox1 created above. Note that the list box this one contains is
    // created according to the 2.9.1 and above rules, i.e., parent is the wxStaticBox
    // contained within the Static Box sizer.

    bsStaticBox2 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Static Box Sizer 2"));
    lbStatic2 = new wxListBox(bsStaticBox2->GetStaticBox(), wxID_ANY);
    bsStaticBox2->Add(lbStatic2, 1, wxALL|wxEXPAND, 5);
    bsInner->Add(bsStaticBox2, 1, wxALL|wxEXPAND, 5);

    Panel1->SetSizer(bsInner);
    bsInner->Fit(Panel1);
    bsInner->SetSizeHints(Panel1);
    bsOuter->Add(Panel1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(bsOuter);
    bsOuter->Fit(this);
    bsOuter->SetSizeHints(this);

    lbPlain->SetDropTarget(new DF(lbPlain));
    lbStatic1->SetDropTarget(new DF(lbStatic2));
    lbStatic2->SetDropTarget(new DF(lbStatic2));
}


testFrame::~testFrame()
{
}


void testFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}


DF::DF ( wxListBox * lb_target )
{
    m_target = lb_target;
}


bool DF::OnDropFiles ( wxCoord x, wxCoord y, const wxArrayString & files )
{
    m_target->Append(files);

    return true;
}


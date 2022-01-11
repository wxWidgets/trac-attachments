/////////////////////////////////////////////////////////////////////////////
// Name:        minimal.cpp
// Purpose:     Minimal wxWidgets sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// Copyright:   (c) Julian Smart
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

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows it is in resources and even
// though we could still include the XPM here it would be unused)
#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "../sample.xpm"
#endif

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit() wxOVERRIDE;
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title);
    virtual ~MyFrame(){}
    // event handlers (these functions should _not_ be virtual)
    void OnClick(wxCommandEvent& event);

private:

};


wxIMPLEMENT_APP(MyApp);

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;

    // create the main application window
    MyFrame *frame = new MyFrame("Minimal wxWidgets App");

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

// Sample Dialog Test
static int count = 1;

class MyDialog: public wxDialog
{
public:
    MyDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, wxString::Format("My Dialog %d", count))
    {
        count++;
        wxSizer* pSizer = new wxBoxSizer(wxVERTICAL);
        pSizer->AddSpacer(30);
        
        wxButton* pButton = new wxButton(this, wxID_ANY, "Click Button");
        pButton->Bind(wxEVT_BUTTON, & MyDialog::OnClick, this);
        pSizer->Add(pButton);
        
        SetSizer(pSizer);
        Layout();
    }
    
    virtual ~MyDialog()
    {
        
    }

 private:
    void OnClick(wxCommandEvent& event)
    {
        MyDialog dlg(this);
        dlg.ShowModal();
        event.Skip();
    }
};

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
    wxSizer* pSizer = new wxBoxSizer(wxVERTICAL);
    pSizer->AddSpacer(30);
    
    wxButton* pButton = new wxButton(this, wxID_ANY, "Click Button");
    pButton->Bind(wxEVT_BUTTON, & MyFrame::OnClick, this);
    pSizer->Add(pButton);
    
    SetSizer(pSizer);
    Layout();
}

void MyFrame::OnClick(wxCommandEvent& event)
{
    MyDialog dlg(this);
    dlg.ShowModal();
    event.Skip();
}


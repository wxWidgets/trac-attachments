/////////////////////////////////////////////////////////////////////////////
// Name:        formtstr.h
// Purpose:     Format and validate number sample header
// Author:      Manuel Martin
// Modified by:
// Created:     mar 2003
// RCS-ID:      
// Copyright:   
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef FORSTRSAM_H
    #define FORSTRSAM_H

#ifdef __GNUG__
    #pragma interface "formtstr.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    bool OnInit();
};

/////////////////////////////////////////////////////////////////////////////
// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    ~MyFrame();

    //some utility functions
    
    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    //members

private:
    // any class wishing to process wxWindows events must use this macro
    DECLARE_EVENT_TABLE()
};

/////////////////////////////////////////////////////////////////////////////
class myPanel: public wxPanel
{
public:
    myPanel(wxWindow* parent, const wxPoint& pos, const wxSize& size);
    ~myPanel();

    // event handlers (these functions should _not_ be virtual)
    void OnButtonFPressed(wxCommandEvent& event);
    void OnButtonUPressed(wxCommandEvent& event);
    void OnButtonVPressed(wxCommandEvent& event);
    void OnButtonTTWPressed(wxCommandEvent& event);
    void OnButtonTFWPressed(wxCommandEvent& event);

    //members
    wxCheckBox* beStrict;
    wxCheckBox* leftrim0;
    wxCheckBox* rigtrim0;
    wxTextCtrl* yourstyle;
    wxTextCtrl* yournumb;
    wxTextCtrl* yourresul;
    wxTextCtrl* yourunfor;
    wxTextCtrl* yourvalsty;
    wxTextCtrl* yourvaldat;
    wxTextCtrl* yourtest;
    wxCheckBox* vOnChar;
    wxCheckBox* vOnEnTab;
    wxCheckBox* vOnKillF;
    wxCheckBox* vTransUn;

private:
    // any class wishing to process wxWindows events must use this macro
    DECLARE_EVENT_TABLE()
};

/////////////////////////////////////////////////////////////////////////////
// IDs for the controls and the menu commands
enum
{
    FSN_QUIT = 100,
    FSN_ABOUT,
    FSVN_BUTF,  //the button id
    FSVN_BUTU,
    FSVN_BSTRC, //checkbox id
    FSVN_LTRM0,
    FSVN_RTRM0,
    FSVN_VONCH, //checkboxes for validating
    FSVN_VONET,
    FSVN_VONKF,
    FSVN_VTRUN,
    FSVN_VRESET, //the validate button reset
    FSVN_VTOWIN, //transfer to window
    FSVN_VFRWIN  //transfer from window
};

#endif // FORSTRSAM_H


 	  	 

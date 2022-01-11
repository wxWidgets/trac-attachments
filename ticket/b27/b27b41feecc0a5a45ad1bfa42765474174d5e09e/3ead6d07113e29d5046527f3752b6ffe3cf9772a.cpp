//
//  10003.cpp
//  
//
//  Created by Igor Korot on 5/27/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#include "wx/wx.h"

class EventHandler : public wxEvtHandler
{
public:
    EventHandler() : wxEvtHandler()
    {
        Connect( wxID_ANY, wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( EventHandler::onComboBox ) );
    }
    
    void onComboBox(wxCommandEvent &event)
    {
        wxComboBox *cb = (wxComboBox *) event.GetEventObject();
        wxMessageBox( wxString::Format( "Combobox selected, value = %s", (const char *) cb->GetValue().c_str() ) );
    }
};

class CTestApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        wxFrame *f = new wxFrame( NULL, wxID_ANY, "Test" );
        wxSizer *s = new wxBoxSizer( wxVERTICAL );
        wxComboBox *cb = new wxComboBox( f, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
        s->Add( cb, 1, wxEXPAND | wxALL, 20 );
        f->SetSizer( s );
        s->SetSizeHints( f );
        f->PushEventHandler( new EventHandler() );
        cb->Append( "one" );
        cb->Append( "two" );
        cb->Append( "three" );
        cb->Append( "four" );
        cb->Append( "five" );
        SetTopWindow( f );
        f->Center();
        f->Show();
        return true;
    }
    
    virtual int OnExit()
    {
        GetTopWindow()->PopEventHandler();
    }
};

IMPLEMENT_APP( CTestApp )

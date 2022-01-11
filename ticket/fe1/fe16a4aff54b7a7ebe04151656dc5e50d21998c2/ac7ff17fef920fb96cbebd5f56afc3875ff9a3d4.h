/////////////////////////////////////////////////////////////////////////////
// Name:        valnum.h
// Purpose:     wxNumberValidator header
// Author:      Manuel Martin
// Modified by:
// Created:     mar 2003
// RCS-ID:      
// Copyright:   
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _VALNUM_H
#define _VALNUM_H

#ifdef __GNUG__
#pragma interface "valnum.h"
#endif

#if wxUSE_VALIDATORS

#include "wx/textctrl.h"
#include "wx/validate.h"

#include "forstrnu.h"

enum
{ wxVAL_ON_CHAR           =   16,
  wxVAL_ON_ENTER_TAB      =   32,
  wxVAL_ON_KILL_FOCUS     =   64,
  wxTRANSFER_UNFORMATTED  =  128,
  wxTRANSFER_UNFORMATTED_NO_ZEROS = wxTRANSFER_UNFORMATTED | wxTZ_BOTH,
  wxVAL_DEFAULT = wxUF_BESTRICT | wxVAL_ON_ENTER_TAB,
  wxVAL_ON_EDIT = wxUF_NOSTRICT | wxVAL_ON_CHAR | wxVAL_ON_ENTER_TAB
};

/////////////////////////////////////////////////////////////////////////////
class WXDLLEXPORT wxNumberValidator: public wxValidator
{
DECLARE_DYNAMIC_CLASS(wxNumberValidator)
public:
    wxNumberValidator(const wxString& valStyle = "-[#].'.'#E-###",
                     int behavior = wxVAL_DEFAULT,
                     wxString *val = 0);
    wxNumberValidator(const wxNumberValidator& val);

    ~wxNumberValidator();

    // Make a clone of this validator (or return NULL) - currently necessary
    // if you're passing a reference to a validator.
    // Another possibility is to always pass a pointer to a new validator
    // (so the calling code can use a copy constructor of the relevant class).
    virtual wxObject *Clone() const { return new wxNumberValidator(*this); }
    bool Copy(const wxNumberValidator& val);

    // Called when the value in the window must be validated.
    // This function can pop up an error message.
    virtual bool Validate(wxWindow *parent);

    // Called to transfer data to the window
    virtual bool TransferToWindow();

    // Called to transfer data to the window
    virtual bool TransferFromWindow();

    // ACCESSORS
    inline int GetBehavior() const { return m_validatorBehavior; }
    inline void SetBehavior(int behavior) { m_validatorBehavior = behavior; }

    wxString GetDecSep(){return m_styleWorker->GetDecSep();};
    
    wxString GetStyle() {return m_styleWorker->GetStyle();}
    int SetStyle(const wxString& valstyle)
      {return m_styleWorker->SetStyle(valstyle);}

    wxString GetLastError() {return m_styleWorker->GetLastError();}

    void OnChar(wxKeyEvent& event);
    void OnKillFocus(wxFocusEvent& event);

DECLARE_EVENT_TABLE()

protected:
    int                       m_validatorBehavior;
    wxString *                m_stringValue;
    wxFormatStringAsNumber *  m_styleWorker;
    bool                      m_LastCharWasNUMPADDEC;

    bool CheckValidator() const
    {
        wxCHECK_MSG( m_validatorWindow, FALSE,
                     _T("No window associated with validator") );
        wxCHECK_MSG( m_validatorWindow->IsKindOf(CLASSINFO(wxTextCtrl)), FALSE,
                     _T("wxNumberValidator is only for wxTextCtrl's") );
        wxCHECK_MSG( ((wxTextCtrl *)m_validatorWindow)->IsSingleLine(), FALSE,
                     _T("Multiline wxTextCtrl not allowed yet") );

        return TRUE;
    }

    void SetFormatted();
};

#endif // wxUSE_VALIDATORS

#endif //_VALNUM_H


 	  	 

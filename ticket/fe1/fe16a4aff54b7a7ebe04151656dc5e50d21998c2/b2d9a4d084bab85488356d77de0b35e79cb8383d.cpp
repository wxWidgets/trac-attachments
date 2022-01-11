/////////////////////////////////////////////////////////////////////////////
// Name:        valnum.cpp
// Purpose:     wxNumberValidator
// Author:      Manuel Martin
// Modified by:
// Created:     mar 2003
// RCS-ID:
// Copyright:
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation "valnum.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
  #pragma hdrstop
#endif

#if wxUSE_VALIDATORS

#ifndef WX_PRECOMP
  #include  "wx/string.h"
  #include  "wx/intl.h"
#endif


#include "valnum.h"

IMPLEMENT_DYNAMIC_CLASS(wxNumberValidator, wxValidator)

BEGIN_EVENT_TABLE(wxNumberValidator, wxValidator)
    EVT_CHAR(wxNumberValidator::OnChar)
    EVT_KILL_FOCUS(wxNumberValidator::OnKillFocus)
END_EVENT_TABLE()


/////////////////////////////////////////////////////////////////////////////
wxNumberValidator::wxNumberValidator(const wxString& valStyle,
                                   int behavior, wxString *val)
{
    m_validatorBehavior = behavior ;
    m_stringValue = val ;
    m_LastCharWasNUMPADDEC = FALSE;
    m_styleWorker = new wxFormatStringAsNumber;
    m_styleWorker->SetStyle(valStyle);
}

wxNumberValidator::wxNumberValidator(const wxNumberValidator& val)
    : wxValidator()
{
    m_styleWorker = new wxFormatStringAsNumber;
    Copy(val);
}

bool wxNumberValidator::Copy(const wxNumberValidator& val)
{
    wxValidator::Copy(val);

    m_validatorBehavior = val.m_validatorBehavior ;
    m_stringValue       = val.m_stringValue ;
    m_LastCharWasNUMPADDEC = val.m_LastCharWasNUMPADDEC;
    m_styleWorker->SetStyle(val.m_styleWorker->GetStyle());

    return TRUE;
}

wxNumberValidator::~wxNumberValidator()
{
}

/////////////////////////////////////////////////////////////////////////////
// Called to transfer data to the window
bool wxNumberValidator::TransferToWindow(void)
{
    if( !CheckValidator() )
        return FALSE;
    wxCHECK_MSG( m_stringValue, FALSE,
                 _T("No variable storage for validator") );

    wxTextCtrl *control = (wxTextCtrl *) m_validatorWindow ;
    if (m_validatorBehavior & wxTRANSFER_UNFORMATTED)
    {   wxString formatted;
        m_styleWorker->FormatStr(* m_stringValue, formatted);
        control->SetValue(formatted) ;
        //return TRUE even if value can't be formatted
    }
    else
        control->SetValue(* m_stringValue) ;

    return TRUE;
}

// Called to transfer data to the window
bool wxNumberValidator::TransferFromWindow(void)
{
    if( !CheckValidator() )
        return FALSE;
    wxCHECK_MSG( m_stringValue, FALSE,
                 _T("No variable storage for validator") );

    wxTextCtrl *control = (wxTextCtrl *) m_validatorWindow ;
    wxString inControl(control->GetValue()) ;

    if (m_validatorBehavior & wxTRANSFER_UNFORMATTED)
    {   wxString unformatted;
        int beStrict = wxUF_BESTRICT, trimz = 0;
        if (m_validatorBehavior & wxUF_NOSTRICT)
            beStrict = wxUF_NOSTRICT ;
        m_styleWorker->UnFormatStr(inControl, unformatted, beStrict);
        trimz = m_validatorBehavior & (wxTZ_LEFT | wxTZ_RIGHT) ;
        m_styleWorker->TrimZeros(unformatted, trimz);
        * m_stringValue = unformatted ;
        //return TRUE even if value can't be unformatted
    }
    else
        * m_stringValue = inControl ;

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
void wxNumberValidator::OnKillFocus(wxFocusEvent& event)
{
    if ( m_validatorBehavior & wxVAL_ON_KILL_FOCUS)
        if ( Validate(m_validatorWindow->GetParent()) )
        {   //let's format it
            SetFormatted();
            event.Skip();
        }
    return;
}

/////////////////////////////////////////////////////////////////////////////
void wxNumberValidator::OnChar(wxKeyEvent& event)
{
    //wxevent system post two char-event for keys at numpad
    //All keycodes except the decimal are skipped at first event
    //and used at second event
    //(i.e. NUMPAD4 (1st event.KeyCode) traslates to '4' (2nd)
    //But with decimal key we must process just the first event
    if ( m_LastCharWasNUMPADDEC )
    {   m_LastCharWasNUMPADDEC = FALSE;
        return; //eat message
    }
    m_LastCharWasNUMPADDEC = FALSE;

    if ( !m_validatorWindow )
    {   event.Skip();
        return;
    }

    int keyCode = (int)event.KeyCode();

    wxTextCtrl *control = (wxTextCtrl *) m_validatorWindow ;

    switch ( keyCode )
    {
        case WXK_ESCAPE:
        case WXK_CANCEL:
            //Back to the variable stored value
            TransferToWindow();
            break;
        case WXK_BACK:
        case WXK_DELETE:
        case WXK_NUMPAD_DELETE:
            break;
        case WXK_TAB:
        case WXK_NUMPAD_TAB:
        case WXK_RETURN:
        case WXK_NUMPAD_ENTER:
            if (m_validatorBehavior & wxVAL_ON_ENTER_TAB)
            {   if ( !Validate(m_validatorWindow->GetParent()) )
                    return;
                SetFormatted();
            }
            break;

        default:
        {   if ( (m_validatorBehavior & wxVAL_ON_CHAR)
                && ((keyCode > 0 && keyCode < 256)
                   || keyCode == WXK_NUMPAD_DECIMAL ))
            {   //Add/insert char, unformat, and format again
                wxString inControl(control->GetValue()) ;
                wxString theChar, formatted, unformatted;
                int res;
                int beStrict = wxUF_BESTRICT; //Risky
                if (m_validatorBehavior & wxUF_NOSTRICT)
                    beStrict = wxUF_NOSTRICT ;//Better for ON_CHAR

                //To avoid flickering, we insert char on our own
                size_t pos = (size_t) control->GetInsertionPoint() ;
                size_t rcount = inControl.Len();
                rcount = (pos < rcount) ? (rcount-pos) : 0 ;

                if (keyCode == WXK_NUMPAD_DECIMAL)
                {   //As a help, we write the decimal separator
                    m_LastCharWasNUMPADDEC = TRUE;
                    theChar = m_styleWorker->GetDecSep();
                }
                else if (keyCode > 0 && keyCode < 256)
                    theChar.Printf("%c", (unsigned char)keyCode);

                formatted = inControl.Left(pos);
                formatted += theChar;
                if (rcount > 0)
                    formatted += inControl.Right(rcount);

                //Check to see if this is valid
                res = m_styleWorker->UnFormatStr(formatted,
                            unformatted, beStrict);
                if (res != -1)
                {   control->SetInsertionPoint((long)res);
                    if ( !wxValidator::IsSilent() )
                        wxBell();
                    wxMessageBox(m_styleWorker->GetLastError(),
                            _("Validation conflict"));
                    m_validatorWindow->SetFocus();
                    return; //eat char
                }

                //No errors, format and show it
                m_styleWorker->FormatStr(unformatted, formatted);
                if (inControl != formatted)
                {   control->SetValue(formatted) ;
                    pos = formatted.Len() - rcount;
                    control->SetInsertionPoint((long)pos);
                }
                return; //eat char message to control
            }
        }
    }
    event.Skip(); //process in other event handler
}

/////////////////////////////////////////////////////////////////////////////
// Called when the value in the window must be validated.
// This function can pop up an error message.
bool wxNumberValidator::Validate(wxWindow *parent)
{
    if( !CheckValidator() )
        return FALSE;

    wxTextCtrl *control = (wxTextCtrl *) m_validatorWindow ;

    // If window is disabled, simply return
    if ( !control->IsEnabled() )
        return TRUE;

    wxString inControl(control->GetValue()) ;
    wxString unformatted;
    int res;
    int beStrict = wxUF_BESTRICT;

    if (m_validatorBehavior & wxUF_NOSTRICT)
        beStrict = wxUF_NOSTRICT ;
    res = m_styleWorker->UnFormatStr(inControl, unformatted, beStrict);

    if (res != -1)
    {   control->SetInsertionPoint((long)res);
        wxMessageBox(m_styleWorker->GetLastError(), _("Validation conflict"));
        m_validatorWindow->SetFocus();
        return FALSE;
    }
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//Set the formatted value of the control's value
//Use it when you know there's no error
void wxNumberValidator::SetFormatted()
{
    wxTextCtrl *control = (wxTextCtrl *) m_validatorWindow ;
    wxString inControl(control->GetValue()) ;
    wxString formatted, unformatted;
    int beStrict = wxUF_BESTRICT;

    if (m_validatorBehavior & wxUF_NOSTRICT)
        beStrict = wxUF_NOSTRICT ;
    m_styleWorker->UnFormatStr(inControl, unformatted, beStrict);
    m_styleWorker->FormatStr(unformatted, formatted);
    control->SetValue(formatted) ;
    return;
}

#endif // wxUSE_VALIDATORS


 	  	 

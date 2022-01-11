/************************************************************************
 *                                                                      *
 *                        Copyright (c) 2005							*
 *                Electronics for Imaging, Inc., Foster City, CA        *
 *                           All rights reserved.                       *
 *                                                                      *
 *   This software is furnished under a license and may be used and     *
 *   copied  only  in accordance with the terms of such license and     *
 *   with the  inclusion  of  the  above  copyright  notice.   This     *
 *   software  or  any  other copies thereof may not be provided or     *
 *   otherwise made available to any other person except as allowed     *
 *   under  license.  No  title to and ownership of the software is     *
 *   hereby transferred.                                                *
 *                                                                      *
 *   This software is proprietary Electronics for Imaging, Inc., and    *
 *   is not to be disclosed without written permission from Electronics *
 *   for Imaging, Inc.                                                  *
 *                                                                      *
 *                                                                      *
 *	 Filename	:	CNTextCtrl.cpp                                      *
 *	 Created By :	Wei Zou	                                            *
 *   Date       :   Oct., 7th, 2005                                     *
 *                                                                      *
 *                                                                      *
 *                                                                      *
 *                                                                      *
 ************************************************************************
 *	Edit History:														*
 *	Name		:		Change											*
 *                                                                      *
 ************************************************************************/
/*
	This class is an UI for text control. It is mainly used on Mac. J system to
	simulate the input of J char.
 *  
 */

#include "Prefix.h"

#include "uibase/UILanguageManager.h"
#include "uibase/UIResourceManager.h"

#include "CNTextCtrl.h"

#ifdef _WIN32
#include "wx/clipbrd.h"
#endif

BEGIN_EVENT_TABLE(CNTextCtrl, wxTextCtrl)
    EVT_CHAR(CNTextCtrl::OnChar)
	EVT_KILL_FOCUS(CNTextCtrl::OnKillFocus)
	EVT_TEXT(wxID_ANY, CNTextCtrl::OnTextChange)

#ifdef _WIN32
	EVT_TEXT_PASTE(wxID_ANY, CNTextCtrl::OnPaste)
#endif

#ifdef __WXMAC__
	EVT_KEY_UP(CNTextCtrl::OnKey)
	EVT_KEY_DOWN(CNTextCtrl::OnKey)
#endif

END_EVENT_TABLE()

#define MAX_LENGTH 512


CNTextCtrl::CNTextCtrl(wxWindow *parent, int idUI, wxPoint pos, wxSize size, long lStyle)
:m_bNewLine(false), m_bRetKey(false), m_lFilter(wxFILTER_NONE),  m_bNoUIEvent(false), m_strValue(_T("")),
m_bAllowSpace(false),
#ifdef __WXMAC__
m_lSavedFilter(wxFILTER_NONE), m_dMaxLength(MAX_LENGTH),
#endif
wxTextCtrl(parent, idUI, wxEmptyString, pos, size, lStyle)
{
}

void CNTextCtrl::SetNumValidator(wxControl *pcontrol, const wxArrayString &strList)
{
    wxTextValidator txtValidator = wxTextValidator( wxFILTER_INCLUDE_CHAR_LIST );
 
	wxArrayString strNumList = strList;
	strNumList.Add(wxT("0")); 
	strNumList.Add(wxT("1"));
	strNumList.Add(wxT("2"));
	strNumList.Add(wxT("3"));
	strNumList.Add(wxT("4"));
	strNumList.Add(wxT("5"));
	strNumList.Add(wxT("6"));
	strNumList.Add(wxT("7"));
	strNumList.Add(wxT("8"));
	strNumList.Add(wxT("9"));

    txtValidator.SetIncludes(strNumList);

    pcontrol->SetValidator(txtValidator);
}

wxString CNTextCtrl::GetCharAllowedTip(int iMaxLen , long iFilter )
{
	wxString strTips = wxString::Format(_T("%d"), iMaxLen);
	if(wxFILTER_NUMERIC == iFilter)
	{
		strTips += _T(" ") + wxLT(kLocal_String_Numeric_Allowed);
	}
	else
	{
        // Russian translation requires a different format (#1-1EWHH1)
        wxLocale* pLocale = wxGetLocale();
        if (pLocale != NULL)
        {
            String strCanonicalName = pLocale->GetCanonicalName();
			String strLocale = strCanonicalName.SubString(0,1);
            if (strLocale.CmpNoCase(LOCALE_RUSSIA) == 0)
            {
                strTips = wxLT(kLocal_String_Char_Allowed) + _T(" ") + strTips;
                return strTips;
            }
        }

	strTips += _T(" ") + wxLT(kLocal_String_Char_Allowed);
	}

	return strTips;
}

void CNTextCtrl::OnKillFocus(wxFocusEvent& event)
{
#ifdef __WXMAC__
	
	wxString text;
	int numberOfLines = GetNumberOfLines();
	
	for (int i = 0; i < numberOfLines; i++)
	{
		text = text + GetLineText(i);
	}
	
	int length = text.Len();
	
	if (length > 0)
	{
		if (IsWrongFormat(text))
		{
			m_bNoUIEvent = true;
			long from = 0, to = 0;
			GetSelection(&from, &to);
			SetValue(m_strValue);
			SetSelection(from, to);
			m_bNoUIEvent = false;
		}
		
		else
		{
			int position = m_dMaxLength;
			if (position < 0)
				position = MAX_LENGTH;
			
			if (m_lFilter != wxFILTER_NONE)
			{
				for (int i = 0; (i < m_dMaxLength) && (position == m_dMaxLength); i++)
				{
                    if ((m_lFilter & wxFILTER_ALPHA) && !StrUtl::IsAlpha(text[i]))
					{
						position = i;
					}
					
					if ((m_lFilter & wxFILTER_NUMERIC) && !StrUtl::IsDigit(text[i]))
					{
						position = i;
					}
					
                    if ((m_lFilter & wxFILTER_ALPHANUMERIC) && !StrUtl::Isalnum(text[i]))
					{
						position = i;
					}
				}
			}
			
			if (length > m_dMaxLength || position < m_dMaxLength)
			{
				m_strValue = text.Left(position);
				SetValue(m_strValue);
			}		
		}
	}
	
#else
	GetParent()->GetEventHandler()->AddPendingEvent(event);
#endif
	
	event.Skip();
}

#ifdef __WXMAC__
void CNTextCtrl::SetMaxLength(unsigned long length)
{
	m_dMaxLength = length;
	wxTextCtrl::SetMaxLength(length);
	wxTextEntry::SetMaxLength(length);
}
#endif

#ifdef	__WXOSX_COCOA__
void CNTextCtrl::SetValue(const wxString& strValue)
{
	// 1-1EBFR9 : On Mac Cocoa, wxTextCtrl::SetValue(), which eventually becomes [NSTextField insertText], throw exceptions.
	try
	{
		wxTextCtrl::SetValue(strValue);
	}
	catch (...)
	{
	}
}
#endif

#ifdef __WXMAC__
void CNTextCtrl::OnKey(wxKeyEvent& event)
{
    event.Skip();
	
    wxTextValidator *pVal = (wxTextValidator *) GetValidator();
    if(pVal && m_lSavedFilter == wxFILTER_NONE)
    {
        m_lSavedFilter = pVal->GetStyle();
    }
    if(event.MetaDown())
    {
        if(pVal)
        {
            pVal->SetStyle(wxFILTER_NONE);
        }
        wxTextCtrl::SetMaxLength(0);
    }
    else
    {
        if(pVal)
        {
            pVal->SetStyle(m_lSavedFilter);
        }
        wxTextCtrl::SetMaxLength(m_dMaxLength);
    }
}

bool CNTextCtrl::IsValidLength(const wxString &strValue)
{
	int length = strValue.Len();
	
	if (length <= m_dMaxLength)
	{
		return true;
	}
	else
	{
		return false;
	}
}
#endif

/*
void CNTextCtrl::OnLeftDown(wxMouseEvent& event)
{	
	wxEventType evtType = wxEVT_COMMAND_CONTROL_HAS_FOCUS;
	wxCommandEvent evt(evtType);
	GetParent()->GetEventHandler()->ProcessEvent(evt);
	
	event.Skip();
}
*/

void CNTextCtrl::OnChar(wxKeyEvent& event)
{
	int keyCode = event.GetKeyCode();
	wxChar keyUnicodeChar = event.GetUnicodeKey();
	m_bRetKey = keyCode == WXK_RETURN;
	if(!m_bNewLine)
	{
		if(m_bRetKey)
		{
			return;
		}
	}
#ifdef __WXMAC__
    if(event.MetaDown())
    {
		event.Skip();
		return;
    }
	wxCommandEvent event1(wxEVT_COMMAND_TEXT_UPDATED, GetId());
	GetParent()->GetEventHandler()->AddPendingEvent(event1);
#endif
	if(m_lFilter == wxFILTER_NONE || (m_lFilter == wxFILTER_INCLUDE_CHAR_LIST) ||
        keyCode < WXK_SPACE || keyCode == WXK_DELETE || keyCode > WXK_START)
	{
/* For two byte characters, event.GetKeyCode() returns 0, so the validation fails in wxWidgets as it also uses GetKeyCode() to validate.
For Windows, OnChar is called for each two byte characters but on Mac its called only once and GetKeyCode() >  WXK_START*/ 
#ifdef	__WXMSW__		
		if(keyCode != WXK_NONE)
		{
			event.Skip();
			return;
		}
#else
		event.Skip();
		return;
#endif

	}
    if((m_lFilter & wxFILTER_ALPHA) && !StrUtl::IsAlpha(keyUnicodeChar))
	{
		return;
	}
	if((m_lFilter & wxFILTER_NUMERIC) && !StrUtl::IsDigit(keyUnicodeChar))
	{
		return;
	}
	if((m_lFilter & wxFILTER_ALPHANUMERIC) && !StrUtl::Isalnum(keyUnicodeChar))
	{
		return;
	}
    event.Skip();
}

bool CNTextCtrl::IsWrongFormat(const wxString &strValue)
{
	int len = strValue.Len();
	for(int i = 0; i < len; i++)
	{
		if(((m_lFilter != wxFILTER_NONE && (int) strValue[i] == WXK_SPACE && !m_bAllowSpace) || 
			(int) strValue[i] == WXK_RETURN || strValue[i] == '\n')&& !m_bNewLine)
		{
			return true;
		}
	}
	return false;
}

void CNTextCtrl::OnTextChange(wxCommandEvent& event)
{
	if (m_bNoUIEvent)
	{
		event.Skip();
		return;
	}

#ifdef __WXMAC__
	
	if (IsWrongFormat(event.GetString()))
	{
		m_bNoUIEvent = true;
		long from = 0, to = 0;
		GetSelection(&from, &to);
		SetValue(m_strValue);
 		SetSelection(from, to);
		m_bNoUIEvent = false;
		
		return;
	}
	
#ifdef __WXOSX_COCOA__ // 1-1EZO7N
	
	if (ContainsInvalidChars(event.GetString()) != -1)
	{
		m_bNoUIEvent = true;
		long from = 0, to = 0;
		GetSelection(&from, &to);
		m_strValue = GetValidChars(event.GetString());
		SetValue(m_strValue);
		SetSelection(from, to);
		m_bNoUIEvent = false;
		
		return;
	}
	
#endif
	
	if (!IsValidLength(event.GetString()))
	{
		m_bNoUIEvent = true;
		long from = 0, to = 0;
		GetSelection(&from, &to);
		if (from > m_dMaxLength)
			from = m_dMaxLength;
		if (to > m_dMaxLength)
			to = m_dMaxLength;
		
		if (m_strValue.Len() == 0)
		{
			m_strValue = event.GetString().Left(m_dMaxLength);
		}
		else
		{
			m_strValue = m_strValue.Left(m_dMaxLength);
		}
		
		SetValue(m_strValue);
		SetSelection(from, to);
		m_bNoUIEvent = false;
		
		return;
	}	
	
	m_strValue = event.GetString();
	event.Skip();
	
#else // Windows
	
	if (IsWrongFormat(event.GetString()))
	{
		m_bNoUIEvent = true;
		long from = 0, to = 0;
		GetSelection(&from, &to);
		SetValue(m_strValue);
		SetSelection(from, to);
		m_bNoUIEvent = false;
	}
	else
	{
		m_strValue = event.GetString();
		event.Skip();
	}
	
#endif

}

int CNTextCtrl::ContainsInvalidChars(const wxString &strValue)
{
	int length = std::min((int) strValue.Len(), MAX_LENGTH);
	
	if ((m_lFilter & wxFILTER_INCLUDE_CHAR_LIST))
	{
		wxArrayString validChars = ((wxTextValidator *) GetValidator())->GetIncludes();
		int validCharsLength = validChars.size();

		bool invalid;

		for (int i = 0; i < length; i++)
		{
			invalid = true;

			for (int j = 0; j < validCharsLength; j++)
			{
				if (strValue[i].GetValue() == validChars[j][0].GetValue())
				{
					invalid = false;
				}
			}

			if (invalid == true)
			{
				return i;
			}
		}
	}

	else
	{
		for (int i = 0; i < length; i++)
		{
            if ((m_lFilter & wxFILTER_ALPHA) && !StrUtl::IsAlpha(strValue[i]))
			{
				return i;
			}
			if ((m_lFilter & wxFILTER_NUMERIC) && !StrUtl::IsDigit(strValue[i]))
			{
				return i;
			}
			if ((m_lFilter & wxFILTER_ALPHANUMERIC) && !StrUtl::Isalnum(strValue[i]))
			{
				return i;
			}
		}
	}

	return -1;
}

#ifdef _WIN32
void CNTextCtrl::OnPaste(wxClipboardTextEvent &event)
{
	wxTextDataObject data;
	wxString str = _("");

	if (wxTheClipboard->Open())
	{
		wxTheClipboard->GetData(data);
		wxTheClipboard->Close();
	}

	str = data.GetText(); // str contains the contents of the clipboard

	if (m_lFilter && (ContainsInvalidChars(str) != -1))
	{
		// Don't allow default event processing to take place.
	}
	else
	{
		event.Skip();
	}
}
#endif

wxString CNTextCtrl::GetValidChars(const wxString &strValue)
{
	wxString strValidChars;
	int length = std::min((int) strValue.Len(), MAX_LENGTH);
	
	if ((m_lFilter & wxFILTER_INCLUDE_CHAR_LIST))
	{
		wxArrayString validChars = ((wxTextValidator *) GetValidator())->GetIncludes();
		int validCharsLength = validChars.size();

		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < validCharsLength; j++)
			{
				if (strValue[i].GetValue() == validChars[j][0].GetValue())
				{
					strValidChars += strValue[i];
				}
			}
		}
	}

	else
	{
		for (int i = 0; i < length; i++)
		{
            if ((m_lFilter & wxFILTER_ALPHA) && StrUtl::IsAlpha(strValue[i])
			|| (m_lFilter & wxFILTER_NUMERIC) && StrUtl::IsDigit(strValue[i])
			|| (m_lFilter & wxFILTER_ALPHANUMERIC) && StrUtl::Isalnum(strValue[i]))
			{
				strValidChars += strValue[i];
			}
		}
	}
	return strValidChars;
}
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
 *	 Filename	:	CNTextCtrl.h                                        *
 *	 Created By :	Wei Zou	                                            *
 *   Date       :   Oct., 7th, 2005                                     *
 *   Description:														*
 *                                                                      *
 *                                                                      *
 *                                                                      *
 *                                                                      *
 ************************************************************************
 *	Edit History:														*
 *	Name		:		Change											*
 *                                                                      *
 *                                                                      *
 ************************************************************************/
/*
 *  
 */

#ifndef _CNTEXTCTRL_H_
#define _CNTEXTCTRL_H_

class CNTextCtrl : public wxTextCtrl
{
	DECLARE_EVENT_TABLE()
public:
	CNTextCtrl(wxWindow *parent, int idUI = wxID_ANY,
					wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize,
					long lStyle = wxTE_LEFT);
	~CNTextCtrl(void) {;}

	void SetNewLine(bool bSet) { m_bNewLine = bSet; }
	void SetFilter(long lFilter) { m_lFilter = lFilter; }
	long GetFilter ()const { return m_lFilter; }

#ifdef __WXMAC__
	void SetMaxLength(unsigned long length);
#endif
	
#ifdef	__WXOSX_COCOA__
	void SetValue(const wxString& strValue);
#endif	
	
	static void	SetNumValidator(wxControl *pcontrol, const wxArrayString &strList);
	static wxString GetCharAllowedTip(int iMaxLen, long iFilter = wxFILTER_NONE );

	bool GetReturnKey(void) { return m_bRetKey; }
	void SetReturnKey(bool bSet) { m_bRetKey = bSet; }
	void SetAllowSpace(bool bSet) { m_bAllowSpace = bSet; }

private:
	void OnChar(wxKeyEvent& event);
	void OnKillFocus(wxFocusEvent& event);
	void OnTextChange(wxCommandEvent& event);
	bool IsWrongFormat(const wxString &strValue);
	
	int ContainsInvalidChars(const wxString &strValue);
	wxString GetValidChars(const wxString &strValue);

#ifdef _WIN32
	void OnPaste(wxClipboardTextEvent &event);
#endif

#ifdef __WXMAC__
	void OnKey(wxKeyEvent& event);
	bool IsValidLength(const wxString &strValue);	
	
	long            m_lSavedFilter;
	unsigned long   m_dMaxLength;
    unsigned long   m_dSavedMaxLength;
#endif

	bool        m_bNoUIEvent;
	wxString	m_strValue;
	long		m_lFilter;
	bool		m_bNewLine;
	bool		m_bRetKey;
	bool		m_bAllowSpace;
};

#endif// _CNTEXTCTRL_H_

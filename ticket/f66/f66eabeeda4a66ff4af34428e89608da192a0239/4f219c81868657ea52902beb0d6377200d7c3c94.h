/************************************************************************
 *                                                                      *
 *                        Copyright (c) 2004							*
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
 *	 Filename	:	JPUIEditText.h                                      *
 *	 Created By :	Wei Zou	                                            *
 *   Date       :   Aug., 27th, 2004                                    *
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

#ifndef _JPUIEDITTEXT_H_
#define _JPUIEDITTEXT_H_

#define JP_TEXT_MAXWIDTH			180 //wxMax(180, (kGroupPanelMaxColWidth-kGroupPanelColGap))
#define JP_TEXT_MULTILINE_MAXHEIGHT	(GetUICharHeight(this) * 6)

#include "JPUIBaseControl.h"

class JPUIEditText : public JPUIBaseControl
{
public:
	JPUIEditText(long nDataSetID, wxWindow *parent, const String &controlKey, 
					int iStyle = JP_CONTROL_UISTYLE_EDITTEXT_DEFAULT);
	JPUIEditText(long nDataSetID, wxWindow *parent, const String &controlKey, 
					const String &displayString, int iStyle = JP_CONTROL_UISTYLE_EDITTEXT_DEFAULT);
	virtual ~JPUIEditText(void) {;}

	int			GetUIType(void) { return UI_EDITTEXT; }

	void		SetMaxLength(int iMaxLen);

private:
	void		CreateUI(long nDataSetID, int iStyle);

	void		GetUISelection(wxString &strSetting);
	void		SetUISelection(const wxString &strSetting);

	bool		ValidateSetting(wxControl **pControl);

	long		GetFilter(long nDataSetID);

    void        GetConsecutiveListOfChars(wxArrayString *strCharList, wxChar start, wxChar end);
    wxArrayString  GetLCDChars(bool bNoComma);

	bool		OpenFileBrowse(String &strInitPath);

#ifdef __WXMSW__
	bool		IsNetworkPath(const String &strPath);
	void		GetNetworkPaths(wxArrayString &szPaths);
	bool		ConvertToNetworkPath(String &strPath);
#endif

	void		OnButton(wxCommandEvent& event);
};

#endif// _JPUIEDITTEXT_H_

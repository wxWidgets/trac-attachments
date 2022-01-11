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
 *	 Filename	:	JPUIEditText.cpp						            *
 *	 Created By :	Wei Zou	                                            *
 *   Date       :   Aug., 27th, 2004                                    *
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
 *  
 */

#include "Prefix.h"

#include "wx/filename.h"
#include "wx/dir.h"

#ifdef __WXMSW__
#include "wx/volume.h"
#endif

#include "uibase/UILanguageManager.h"
#include "uibase/controls/CNTextCtrl.h"

#include "JPUIEditText.h"

#if defined(DEBUG_NEW)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

JPUIEditText::JPUIEditText( long nDataSetID, wxWindow *parent, const String &strKey, int iStyle)
:JPUIBaseControl(nDataSetID, parent, strKey, iStyle)
{
	CreateUI(nDataSetID, iStyle);
}

JPUIEditText::JPUIEditText( long nDataSetID, wxWindow *parent, const String &strKey, 
						   const String &strName, int iStyle)
:JPUIBaseControl(nDataSetID, parent, strKey, strName, iStyle)
{
	CreateUI(nDataSetID, iStyle);
}

void JPUIEditText::CreateUI(long nDataSetID, int iStyle)
{
	CNTextCtrl *text = NULL;
    CtrlData* mgr = GetControlData(nDataSetID);
	int iMaxLen = mgr->GetTextControlMaxLength(GetUIKeyword());
	int txtStyle = 0;
	wxSize size(JP_TEXT_MAXWIDTH, -1);
	if(mgr->ControlHasFlag(GetUIKeyword(), EF_PPD_FLAGS_PASSWORD))
	{
		txtStyle = wxTE_PASSWORD;
		if(iMaxLen > 31)
		{
			size.x = iMaxLen * GetUICharWidth(this);
		}
	}
	else if((iStyle & JP_CONTROL_UISTYLE_EDITTEXT_MULTILINE) || iMaxLen > 31)
	{
		if( iStyle & JP_CONTROL_UISTYLE_EDITTEXT_FORCE_SINGLELINE )
		{
			size.x = iMaxLen * GetUICharWidth(this);
		}
		else
		{
			txtStyle |= wxTE_MULTILINE;
			size.x += wxSystemSettings::GetMetric(wxSYS_VSCROLL_X);
			size.y = JP_TEXT_MULTILINE_MAXHEIGHT;
		}
	}

	long lFilter = GetFilter(nDataSetID);
	text = new CNTextCtrl(this, GetUIId(), wxDefaultPosition, size, txtStyle);

	if(lFilter != wxFILTER_NONE)
	{
		text->SetFilter(lFilter);
#ifdef __WXMAC__
		wxLanguage wxLang = GetGlobalData().GetUILanguage();
		if(!(wxLang == wxLANGUAGE_JAPANESE || wxLang == wxLANGUAGE_CHINESE || wxLANGUAGE_CHINESE_SIMPLIFIED || wxLANGUAGE_CHINESE_TRADITIONAL)
			|| (lFilter & wxFILTER_INCLUDE_CHAR_LIST))
#endif
		{
			wxTextValidator txtValidator = wxTextValidator( lFilter );
			if(lFilter & wxFILTER_INCLUDE_CHAR_LIST 
#ifdef WIN32
               || lFilter & wxFILTER_ALPHANUMERIC
#endif
            )
			{
				// The list being taken here is as required for LCD flag
				wxArrayString strCharList = GetLCDChars(mgr->ControlHasFlag(GetUIKeyword(), EF_PPD_FLAGS_NOCOMMA));
                if(lFilter & wxFILTER_ALPHANUMERIC)
                {
                    strCharList.Remove(_T("."));
                    strCharList.Remove(_T("-"));
                    strCharList.Remove(_T("_")); 
                    strCharList.Remove(_T(","));
                }
				//SPACE Flag
				if(lFilter & wxFILTER_INCLUDE_CHAR_LIST && mgr->ControlHasFlag(GetUIKeyword(), EF_PPD_FLAGS_SPACE))
				{
					strCharList.Add(' ');
					text->SetAllowSpace(true);
				}
				txtValidator.SetIncludes(strCharList);
			}
			text->SetValidator(txtValidator);
		}
	}

	if(iMaxLen > 0)
	{
		text->SetMaxLength(iMaxLen);
		text->SetToolTip(CNTextCtrl::GetCharAllowedTip(iMaxLen,text->GetFilter()));
	}
	wxSizer *sizer = GetCurrentSizer();
    int iSizer = wxRIGHT | wxBOTTOM;
#ifdef __WXMAC__
    if(iStyle & JP_CONTROL_UISTYLE_SIDENAME)
    {
        iSizer =  wxALL & ~wxLEFT;
    }
    else if(iStyle & JP_CONTROL_UISTYLE_NONAME)
    {
        iSizer = wxALL & ~wxTOP;
    }
#endif
    sizer->Add(text, 0, iSizer, 2);
	//GetSizer()->Fit(this);
	//AddControl(text);
}

long JPUIEditText::GetFilter(long nDataSetID)
{
    CtrlData* mgr = GetControlData(nDataSetID);
	bool bNumeric = mgr->ControlHasFlag(GetUIKeyword(), EF_PPD_FLAGS_NUMERIC);
	bool bAlpha = mgr->ControlHasFlag(GetUIKeyword(), EF_PPD_FLAGS_ALPHA);
	bool bLCDFilter = mgr->ControlHasFlag(GetUIKeyword(), EF_PPD_FLAGS_LCD);
	long lFilter = wxFILTER_NONE;
	if(bNumeric || bAlpha)
	{
		lFilter = wxFILTER_ALPHANUMERIC;
		if(!bNumeric)
		{
			lFilter = wxFILTER_ALPHA;
		}
		else if(!bAlpha)
		{
			lFilter = wxFILTER_NUMERIC;
		}
	}
	if(bLCDFilter)
	{
		lFilter = wxFILTER_INCLUDE_CHAR_LIST;
	}

	return lFilter;
}

void JPUIEditText::GetUISelection(wxString &strSetting)
{
	wxTextCtrl *xedit = (wxTextCtrl *) GetUIHandle();
	strSetting = xedit->GetValue();
}

void JPUIEditText::SetUISelection(const wxString &strSetting)
{
	wxTextCtrl *xedit = (wxTextCtrl *) GetUIHandle();
	xedit->SetValue(strSetting);
}

void JPUIEditText::SetMaxLength(int iMaxLen)
{
	CNTextCtrl *xedit = (CNTextCtrl *) GetUIHandle();
	xedit->SetMaxLength(iMaxLen);
}

bool JPUIEditText::ValidateSetting(wxControl **pControl)
{
	CtrlData* mgr = GetControlData(GetDataSetID());
	String strFlag = mgr->GetMinLengthPPDFlag(GetUIKeyword());
	if(!strFlag.IsEmpty())
	{
		int iSize = 0;
		int index = (int) strFlag.GetLength() - 1;
		while(index >= 0 && wxIsdigit(strFlag[index]))
		{
			index--;
			iSize++;
		}
		int minLen = 0;
		StrFmt::GetNumber(strFlag.substr(index+1, iSize), minLen);
		int iJobs = mgr->GetNumberJobs();
		for(int i = 0; i < iJobs; i++)
		{
			KeyValue keyValue(GetUIKeyword(), GetUnknownSetting());
			KeyValue defKeyValue = keyValue;
			mgr->GetJobControlDefaultSetting(i, defKeyValue);
			mgr->GetJobControlSetting(i, keyValue);
			if(!IsUnknownSetting(keyValue.mValue) && keyValue.mValue.GetLength() != defKeyValue.mValue.GetLength())
			{
				*pControl = GetUIHandle();
				
				int len = (int) keyValue.mValue.GetLength();
				int maxLen = mgr->GetTextControlMaxLength(GetUIKeyword());
				
				if( len > 0 && len < minLen || len > maxLen)
				{
					wxString strMessage = wxString::Format(wxLT(kLocal_String_Password_Numbers), minLen, maxLen);
					wxMessageBox( strMessage, wxLT(kLocal_String_Error) + _T(": ") + GetUIName(), 
							wxOK | wxICON_ERROR, this);
					return false;
				}
			}
		}
	}
	return true;
}

void JPUIEditText::GetConsecutiveListOfChars(wxArrayString *strCharList, wxChar start, wxChar end)
{
	for(wxChar chr = start; chr <= end; chr++)
	{
		strCharList->Add(wxString(chr));
	}
}

wxArrayString JPUIEditText::GetLCDChars(bool bNoComma)
{
	wxArrayString strCharList;
	strCharList.Add(wxT("_")); 
	strCharList.Add(wxT("-"));
    if(!bNoComma)
    {
	    strCharList.Add(wxT(","));
    }
	strCharList.Add(wxT("."));
	GetConsecutiveListOfChars(&strCharList, 'a', 'z');
	GetConsecutiveListOfChars(&strCharList, 'A', 'Z');
	GetConsecutiveListOfChars(&strCharList, '0', '9');
	return strCharList;
}


#ifdef __WXMSW__
void JPUIEditText::GetNetworkPaths(wxArrayString &szPaths)
{
	szPaths = wxFSVolume::GetVolumes();
	LOOP_SET2(szPaths)
	{
		wxFSVolume vol(szPaths[LOOP_PARA2]);
		if(vol.GetKind() != wxFS_VOL_NETWORK)
		{
			szPaths.erase(szPaths.begin() + LOOP_PARA2);
		}
	}
}

bool JPUIEditText::IsNetworkPath(const String &strPath)
{
	wxArrayString szVolums;
	GetNetworkPaths(szVolums);
	LOOP_SET(szVolums)
	{
		wxFSVolume vol(szVolums[LOOP_PARA]);
		String strName = String(vol.GetName());
		if(strPath.find_first_of(strName) == 0)
		{
			return true;
		}
	}
	return false;
}

 bool JPUIEditText::ConvertToNetworkPath(String &strPath)
 {
	String strSeps = String(wxFileName::GetVolumeSeparator());
	strSeps += wxFileName::GetPathSeparator();
	size_t iPos = strPath.Find(strSeps);
	if(iPos == -1)
	{												// already network path
		return true;
	}
	iPos += strSeps.GetLength();
	String strSubPath = strPath.substr(iPos, strPath.GetLength() - iPos);
	wxArrayString szVolums;
	GetNetworkPaths(szVolums);
	LOOP_SET(szVolums)
	{
		String strVolum = String(szVolums[LOOP_PARA]);
		if(strVolum.Find(strSeps) != -1)
		{
			continue;
		}
		strVolum += strSubPath;
		wxArrayString szFileNames, szFileNames1;
		if(wxDir::Exists(strVolum))
		{
			wxDir::GetAllFiles(strPath, &szFileNames, wxEmptyString, wxDIR_DEFAULT & ~wxDIR_DIRS);
			wxDir::GetAllFiles(strVolum, &szFileNames1, wxEmptyString, wxDIR_DEFAULT & ~wxDIR_DIRS);
			if(szFileNames.size() == szFileNames1.size())
			{
				bool bSame = true;
				LOOP_SET(szFileNames)
				{
					wxFileName fName(szFileNames[LOOP_PARA]);
					wxFileName fName1(szFileNames1[LOOP_PARA]);
					if(fName.GetName() != fName1.GetName())
					{
						bSame = false;
						break;
					}
				}
				if(bSame)
				{
					strPath = strVolum;
					return true;
				}
			}
		}
	}

	return false;
}
#endif

bool JPUIEditText::OpenFileBrowse(String &strInitPath)
{
	wxString strDirHome = _T("");
	if(strInitPath.IsEmpty())
	{
		wxGetHomeDir(&strDirHome);
	}
	else
	{
		strDirHome = strInitPath;
	}

	wxDirDialog dialog(this, GetUIName(), strDirHome, 
									wxDD_DEFAULT_STYLE & ~wxDD_NEW_DIR_BUTTON);
						//wxDefaultPosition,  wxSize(300, 200));
	SetDialogOn(true);
	if(dialog.ShowModal() == wxID_OK)
	{
		SetDialogOn(false);
		wxString strPath = dialog.GetPath();
	    if (!strPath.IsEmpty() && wxDir::Exists(strPath) )
		{
			strInitPath = String(strPath);
#ifdef __WXMSW__
			if(!GetControlData(GetDataSetID())->IsLocalHost())
			{
				bool bRet = IsNetworkPath(strInitPath);
				if(bRet)
				{
					bRet = ConvertToNetworkPath(strInitPath);
				}
		
				if(!bRet)
				{
					wxString strMessage = wxString::Format(wxLT(kLocal_String_Network_path), strInitPath.c_str());
					wxMessageBox(strMessage, wxLT(kLocal_String_Error), wxOK | wxICON_ERROR, this);
					return false;
				}
			}
#endif
			return true;
		}
	}
	else
	{
		SetDialogOn(false);
	}
	return false;
}

void JPUIEditText::OnButton(wxCommandEvent& event)
{
	if(IsLockedUI(event.GetEventObject()))
	{
		JPUIBase::OnButton(event);
		return;
	}
	wxString strOption = _T("");
	GetUISelection(strOption);
	String strSetting = strOption;
	if(OpenFileBrowse(strSetting))
	{
		SetUISelection(strSetting);
		SetControlFromUI();
	}
}

//bool JPUIEditText::ValidatePlanSetting(wxControl **pControl)
//{
//	return true;
//}

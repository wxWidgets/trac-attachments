/////////////////////////////////////////////////////////////////////////////
// Name:        forstrnu.h
// Purpose:     wxFormatStringAsNumber header
// Author:      Manuel Martin
// Modified by:
// Created:     mar 2003
// RCS-ID:      
// Copyright:   
// Licence:     wxWindows license
// Uses from wxwindows:
//     'wxString' 'wxChar' 'wxArrayInt' 'wxT()' '_()'
//     'wxEmptyString' 'wxFAIL_MSG()' 'wxNOT_FOUND'
/////////////////////////////////////////////////////////////////////////////

#ifndef _FORSTRNU_H
#define _FORSTRNU_H

#ifdef __GNUG__
#pragma interface "forstrnu.h"
#endif

enum
{
    wxTZ_LEFT  = 4,                       //trim zeros at left
    wxTZ_RIGHT = 8,                       //trim zeros at right
    wxTZ_BOTH  = wxTZ_LEFT | wxTZ_RIGHT   //trim zeros both sides
};

enum
{   wxUF_BESTRICT = 1,       //be strict when unformatting
    wxUF_NOSTRICT            //be tolerant
};

struct stFSNData
{ wxString sty;     //sub-style
  size_t ig_sty;    //position of group's init
  size_t fg_sty;    //position of group's finish
  wxString decsep;  //string for decimal separator
  size_t idecse;    //decimal separator position
  size_t iexpse;    //exponential position
  wxArrayInt Asty;  //types of char in sub-style
  wxArrayInt AminD; //min number or required digits
  size_t isuffix;   //position of suffix, len of sub-style if no suffix
};

/////////////////////////////////////////////////////////////////////////////
class WXDLLEXPORT wxFormatStringAsNumber
{
public:
  wxFormatStringAsNumber();
  wxFormatStringAsNumber(const wxString& formatStyle);
  ~wxFormatStringAsNumber();

  //Analyze the style, formed with at most three substyles
  //if the style/s are OK, current stored style is replaced
  //Returns '-1' if no errors
  // or the position (0-based) where first error
  int SetStyle(const wxString& formatStyle);

  //Returns the current stored style
  wxString GetStyle(){return m_formatStyle;};

  //Returns the string used as decimal separator in first substyle
  wxString GetDecSep(){return m_Sstypos.decsep;};

  //Returns the last error message, wxEmptyString if none
  wxString GetLastError(){return m_lasterror;};

  //Analize strNum to be a computer-style number
  //Because there´s no format, it is quick
  //Before using it, be sure strNum has no tabs, blanks, etc.
  //Returns '-1' if no errors
  // or the position (0-based) where first error
  int QCheck(const wxString& strNum);

  //Formats strNumIn into strNumOut
  //Returns '-1' if no errors
  // or the position (0-based) where first error
  int FormatStr(const wxString& strNumIn,
                wxString& strNumOut);

  //Unformats strIn into strOut
  //strIn is supposed to be formatted with current style
  //beStrict == wxUF_BESTRICT will return error if strIn is not
  //exactly well style-formatted
  //beStrict == wxUF_NOSTRICT is tolerant, stripping anything but
  //digits, signs, decimal char and exponential char. Because
  //of this, num's sign may be not clear. beStrict == wxUF_NOSTRICT
  //only uses the first (or better, the only) substyle. So be sure
  //this substyle includes the sign
  //Produces a string to use in a 'string-to-number' function
  //Returns '-1' if no errors
  // or the position (0-based) where first error
  int UnFormatStr(const wxString& strIn,
                  wxString& strOut,
                  int beStrict = wxUF_BESTRICT);

  //Trim zeros, by default at left
  void TrimZeros(wxString& strNum, int atside = wxTZ_LEFT);

private:
  wxString m_formatStyle;
  stFSNData m_Sstypos, m_Sstyneg, m_Sstyzer;

  enum {cIsDigit=1, cIsForced, cIsBL, cIsSignp, cIsSignn, cIsSignpE,
        cIsSignnE, cIsChar, cIsDecSep, cIsExpU, cIsExpL};

  wxString m_lasterror;
  //the format routine
  int StrFor(int usesty, const wxString& srIn, wxString& srOut);
  //the unformat routine
  int StrUnf(int usesty, const wxString& srIn, wxString& srOut, int beStc);
  //a function used to know 'minimum digits' (see implementation)
  void FillArrayMinDig(wxArrayInt *arrMinDig, wxArrayInt *pArray,
             wxString *psty, size_t ig_sty, size_t fg_sty, size_t *suffixpos);
  //a function used several times in StrUnf()
  int WhatToDoWithThisChar(
         int numDigSty, int* numDigIn,
         const wxChar* cI, const wxChar* cS, int stychartype, int beStc,
         bool *signIn, bool *signExIn, bool *gotN, bool *gotS, int ana );
};

#endif //_FORSTRNU_H


 	  	 

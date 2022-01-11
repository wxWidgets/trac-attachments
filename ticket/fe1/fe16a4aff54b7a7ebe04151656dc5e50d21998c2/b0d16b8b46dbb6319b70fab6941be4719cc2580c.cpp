/////////////////////////////////////////////////////////////////////////////
// Name:        forstrnu.cpp
// Purpose:     wxFormatStringAsNumber
// Author:      Manuel Martin
// Modified by:
// Created:     mar 2003
// RCS-ID:
// Copyright:
// Licence:     wxWindows license
// Uses from wxwindows:
//     'wxString' 'wxChar' 'wxArrayInt' 'wxT()' '_()'
//     'wxEmptyString' 'wxFAIL_MSG()' 'wxNOT_FOUND' 'TRUE' 'FALSE'
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation "forstrnu.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
  #pragma hdrstop
#endif


#ifndef WX_PRECOMP
  #include  "wx/string.h"
  #include  "wx/dynarray.h"
  #include  "wx/intl.h"
#endif


#include "forstrnu.h"


/////////////////////////////////////////////////////////////////////////////
//I have had problems with the compiler's lib about isdigit()
//It returned non-zero on some chars between 128 and 255
static bool wxIs_Digit(const wxChar c){return (c >= wxT('0') && c <= wxT('9'));};

/////////////////////////////////////////////////////////////////////////////
//Style chars:
//   0   : Sets '0' (zero) if no digit, or the digit if any
//   #   : Sets the digit if any; if decimal digit,
//          show all existing digits
//   b   : Sets next char in style (tipically blank ' ') if no digit
//   .   : Next char marks the beginning of the decimal
//          separator. The same char marks end of this separator
//          Tipically this char would be "'"
//   []  : Repeat this group. Only one group is allowed
//          No digits (#0b) are allowed before group
//   +   : Set always the sign
//   -   : Set the sign if the number is negative
//   @   : Next char is literal; usefull for showing
//          a command-character, such as '#'
//   E   : Exponential
//   e   : Same. Use lowletter 'e' instead of 'E'
//          One digit needed at least before exponential
//          Groups not allowed after exponential
//          Exponential is ONLY used if both number and
//          style have it
//   ;   : Styles separator. May be styles for positive,
//          negative and zero values (in this order)
//          If only one style is provided, it is used for
//          all numbers. If two styles, the first is used
//          for positive and zero, the second for negative.
//
//If style has two signs, after 'E' or 'e', first sign is
//   intended for exponential and second for number
//
//Nasty things as thousandSeparator=decimalSeparator  or
//  decimalSeparator="33" surely leads to bad unformatting
//
wxFormatStringAsNumber::wxFormatStringAsNumber()
{
}

wxFormatStringAsNumber::wxFormatStringAsNumber(
                                   const wxString& formatStyle)
{
    SetStyle(formatStyle);
}

wxFormatStringAsNumber::~wxFormatStringAsNumber()
{
}

/////////////////////////////////////////////////////////////////////////////
//Analize the style
//return -1 if everything is OK, or the error's position
int wxFormatStringAsNumber::SetStyle(const wxString& formatStyle)
{
    size_t stylen = formatStyle.Len();
    if(stylen == 0)
    {   m_lasterror = _("\nNo style");
        wxFAIL_MSG(m_lasterror);
        return 0;
    }

    if(m_formatStyle.Cmp(formatStyle)==0)
        return -1; //we already have it

    stFSNData Stypos, Styneg, Styzer;
    int pindex = -1; //used for positions

    wxString *pTsty   = &(Stypos.sty);    //the sub-style
    wxArrayInt *pasty = &(Stypos.Asty);   //types of char in style
    size_t *pigroup   = &(Stypos.ig_sty); //position of group's init
    size_t *pfgroup   = &(Stypos.fg_sty); //position +1 of group's finish
    wxString *pdecsep = &(Stypos.decsep); //decimal separator
    size_t *pidecsep  = &(Stypos.idecse); //decimal separator position
    size_t *pexp      = &(Stypos.iexpse); //exponential position
    *pigroup = 0;
    *pfgroup = 0;
    *pidecsep = 0;
    *pexp = 0;

    size_t i;
    bool binsep = FALSE; //are we inside a separator?
    bool bdecAlready = FALSE; //is decimal separator defined already?
    bool bExpAlready = FALSE;
    bool bgroAlready = FALSE; //group has begun
    bool bfgrAlready = FALSE; //finished group
    bool bdigit      = FALSE; //any digit
    bool bnumInGroup = FALSE; //is there any number inside group, decimal or exp?
    bool bsgnAlready = FALSE; //number's sign
    bool bsgEAlready = FALSE; //exponential's sign
    bool bdigAlready = FALSE; //any # between decimal separator and exponential
    wxChar c;
    wxChar s; //separator delimiter
    s = '\0'; //to avoid compiler warning

    for (i=0; i<stylen; i++)
    {
        c = formatStyle.GetChar(i);
        if (binsep) //inside decimal separator, all chars are literal
        {   if (c==s) //separator finishes here
            {   if (pdecsep->Len()==0)
                {   m_lasterror = _("\nBad style: decimal separator");
                    wxFAIL_MSG(m_lasterror);
                    return i;
                }
                binsep = FALSE;
                bdigAlready = FALSE;
            }
            else
            {   *pTsty << c; //store the style's char and then its type
                pindex++;
                pasty->Add(cIsDecSep);
                *pdecsep << c;
            }
            continue;
        }
        if (c == wxT('@')) //next char is literal
        {   i++;
            if (i<stylen)
            {   c = formatStyle.GetChar(i);
                *pTsty << c; //store the style's char and then its type
                pindex++;
                pasty->Add(cIsChar);
                continue;
            }
            else
            {   m_lasterror = _("\nBad style: unexpected '@' at end");
                wxFAIL_MSG(m_lasterror);
                return i;
            }
        }
        if (c == wxT('[')) //group's init
            if (bdigit || bgroAlready || bdecAlready || bExpAlready)
            {   m_lasterror = _("\nBad style: 'group'");
                wxFAIL_MSG(m_lasterror);
                return i;
            }
            else
            {   *pigroup = (size_t)(pindex + 1);
                bgroAlready = TRUE;
                bnumInGroup = FALSE;
                continue;
            }
        if (c == wxT(']')) //group's finish
            if (!bgroAlready || bdecAlready || bExpAlready || bfgrAlready
                || !bnumInGroup)
            {   m_lasterror = _("\nBad style: 'group'");
                wxFAIL_MSG(m_lasterror);
                return i;
            }
            else
            {   *pfgroup = (size_t)(pindex + 1); //position + 1
                bfgrAlready = TRUE;
                bnumInGroup = FALSE;
                continue;
            }
        if (c == wxT('.'))
        {   if (bdecAlready || bExpAlready || (bgroAlready && !bfgrAlready) )
            {   m_lasterror = _("\nBad style: 'decimal separator'");
                wxFAIL_MSG(m_lasterror);
                return i;
            }
            i++;
            if (i<stylen)
            {   s = formatStyle.GetChar(i);
                binsep = TRUE;
                bdecAlready = TRUE;
                bnumInGroup = FALSE;
                *pidecsep = (size_t)(pindex+1);
                continue;
            }
            else
            {   m_lasterror = _("\nBad style: unexpected '.' at end");
                wxFAIL_MSG(m_lasterror);
                return i;
            }
        }
        if (c == wxT('+') || c == wxT('-'))
        {   if (bExpAlready)
            {   if (bsgEAlready)
                    if (bsgnAlready)
                    {   m_lasterror = _("\nBad style: 'many signs'");
                        wxFAIL_MSG(m_lasterror);
                        return i;
                    }
                    else
                    {   *pTsty << c;
                        bsgnAlready = TRUE;
                        pindex++;
                        if (c == wxT('+'))
                            pasty->Add(cIsSignp);
                        else
                            pasty->Add(cIsSignn);
                        continue;
                    }
                else
                {   *pTsty << c;
                    bsgEAlready = TRUE;
                    pindex++;
                    if (c == wxT('+'))
                        pasty->Add(cIsSignpE);
                    else
                        pasty->Add(cIsSignnE);
                    continue;
                }
            }
            if (bsgnAlready)
            {   m_lasterror = _("\nBad style: 'sign'");
                wxFAIL_MSG(m_lasterror);
                return i;
            }
            else if (bgroAlready && !bfgrAlready)
            {   m_lasterror = _("\nBad style: 'sign inside group'");
                wxFAIL_MSG(m_lasterror);
                return i;
            }
            else
            {   *pTsty << c;
                bsgnAlready = TRUE;
                pindex++;
                if (c == wxT('+'))
                    pasty->Add(cIsSignp);
                else
                    pasty->Add(cIsSignn);
                continue;
            }
        }
        if (c == wxT('E') || c == wxT('e'))
            if (!bdigit || bExpAlready || (bgroAlready && !bfgrAlready) )
            {   m_lasterror = _("\nBad style: 'exponential'");
                wxFAIL_MSG(m_lasterror);
                return i;
            }
            else
            {   *pTsty << c;
                bExpAlready = TRUE;
                bnumInGroup = FALSE;
                bdigAlready = FALSE;
                pindex++;
                *pexp = (size_t)pindex;
                if (c == wxT('E'))
                    pasty->Add(cIsExpU);
                else
                    pasty->Add(cIsExpL);
                continue;
            }
        if (c == wxT('b')) //next char is literal to use when no digit
        {   if (bdecAlready && bdigAlready)
            {   m_lasterror = _("\nBad style: '# 0 b after # in decimal part'");
                wxFAIL_MSG(m_lasterror);
                return i;
            }
            i++;
            if (i<stylen)
            {   c = formatStyle.GetChar(i);
                *pTsty << c; //store the style's char and then its type
                pindex++;
                bdigit = TRUE;
                pasty->Add(cIsBL);
                if (bExpAlready || (bgroAlready && !bfgrAlready))
                    bnumInGroup = TRUE;
                else
                    bnumInGroup = FALSE;
                continue;
            }
            else
            {   m_lasterror = _("\nBad style: unexpected 'b' at end");
                wxFAIL_MSG(m_lasterror);
                return i;
            }
        }
        if (c == wxT('0') || c == wxT('#'))
        {   if (bdecAlready && bdigAlready)
            {   m_lasterror = _("\nBad style: '# 0 b after # in decimal part'");
                wxFAIL_MSG(m_lasterror);
                return i;
            }
            *pTsty << c;
            pindex++;
            bdigit = TRUE;
            if (c == wxT('0'))
                pasty->Add(cIsForced);
            else if (c == wxT('#'))
            {   pasty->Add(cIsDigit);
                if(bdecAlready && !bExpAlready) bdigAlready = TRUE;
            }
            if (bExpAlready || (bgroAlready && !bfgrAlready))
                bnumInGroup = TRUE;
            else
                bnumInGroup = FALSE;
            continue;
        }
        if (c == wxT(';')) //styles separator
        {   if (pTsty->Len()==0 || binsep || (bgroAlready && !bfgrAlready)
                || (bExpAlready && !bnumInGroup))
            {   m_lasterror = _("\nBad style: 'styles separator'");
                wxFAIL_MSG(m_lasterror);
                return i;
            }
            if (!bdigit && pTsty != &(Styzer.sty))
            {   m_lasterror = _("\nBad style: 'no digit before styles separator'");
                wxFAIL_MSG(m_lasterror);
                return i;
            }
            binsep = FALSE;
            bdecAlready = FALSE;
            bExpAlready = FALSE;
            bgroAlready = FALSE;
            bfgrAlready = FALSE;
            bdigit      = FALSE;
            bnumInGroup = FALSE;
            bsgnAlready = FALSE;
            bsgEAlready = FALSE;
            bdigAlready = FALSE;
            //let's point to next style
            pindex = -1;
            if (pTsty == &(Stypos.sty) )
            {   pTsty    = &(Styneg.sty);
                pasty    = &(Styneg.Asty);
                pigroup  = &(Styneg.ig_sty);
                pfgroup  = &(Styneg.fg_sty);
                pdecsep  = &(Styneg.decsep);
                pidecsep = &(Styneg.idecse);
                pexp     = &(Styneg.iexpse);
            }
            else if (pTsty == &(Styneg.sty) )
            {   pTsty    = &(Styzer.sty);
                pasty    = &(Styzer.Asty);
                pigroup  = &(Styzer.ig_sty);
                pfgroup  = &(Styzer.fg_sty);
                pdecsep  = &(Styzer.decsep);
                pidecsep = &(Styzer.idecse);
                pexp     = &(Styzer.iexpse);
            }
            else
            {   m_lasterror = _("\nBad style: 'too many styles separators");
                wxFAIL_MSG(m_lasterror);
                return i;
            }
            *pigroup = 0;
            *pfgroup = 0;
            *pidecsep = 0;
            *pexp = 0;

            continue;
        }
        *pTsty << c;
        pindex++;
        pasty->Add(cIsChar);
    }
    //perhaps the style doesn't finish properly
    if (binsep || (bgroAlready && !bfgrAlready) || (bExpAlready && !bnumInGroup))
    {   m_lasterror = _("\nBad style: 'unexpected style's end'");
        wxFAIL_MSG(m_lasterror);
        return i;
    }
    if (!bdigit && pTsty != &(Styzer.sty))
    {   m_lasterror = _("\nBad style: 'no digit in [sub]style'");
        wxFAIL_MSG(m_lasterror);
        return i;
    }

    //Style is OK, let's store it
    m_formatStyle = formatStyle;

    m_Sstypos.sty    = Stypos.sty;
    m_Sstyneg.sty    = Styneg.sty;
    m_Sstyzer.sty    = Styzer.sty;
    m_Sstypos.Asty   = Stypos.Asty;
    m_Sstyneg.Asty   = Styneg.Asty;
    m_Sstyzer.Asty   = Styzer.Asty;
    m_Sstypos.ig_sty = Stypos.ig_sty;
    m_Sstyneg.ig_sty = Styneg.ig_sty;
    m_Sstyzer.ig_sty = Styzer.ig_sty;
    m_Sstypos.fg_sty = Stypos.fg_sty;
    m_Sstyneg.fg_sty = Styneg.fg_sty;
    m_Sstyzer.fg_sty = Styzer.fg_sty;
    m_Sstypos.decsep = Stypos.decsep;
    m_Sstyneg.decsep = Styneg.decsep;
    m_Sstyzer.decsep = Styzer.decsep;
    m_Sstypos.idecse = Stypos.idecse;
    m_Sstyneg.idecse = Styneg.idecse;
    m_Sstyzer.idecse = Styzer.idecse;
    m_Sstypos.iexpse = Stypos.iexpse;
    m_Sstyneg.iexpse = Styneg.iexpse;
    m_Sstyzer.iexpse = Styzer.iexpse;

    //Fill arrays with data about minimun digits in style. Also set suffix position
    FillArrayMinDig( &(m_Sstypos.AminD), &(m_Sstypos.Asty), &(m_Sstypos.sty),
                     m_Sstypos.ig_sty, m_Sstypos.fg_sty, &(m_Sstypos.isuffix) );
    if (m_Sstyneg.sty.Len() >0 )
        FillArrayMinDig( &(m_Sstyneg.AminD), &(m_Sstyneg.Asty), &(m_Sstyneg.sty),
                         m_Sstyneg.ig_sty, m_Sstyneg.fg_sty, &(m_Sstyneg.isuffix) );
    if (m_Sstyzer.sty.Len() >0 )
        FillArrayMinDig( &(m_Sstyzer.AminD), &(m_Sstyzer.Asty), &(m_Sstyzer.sty),
                         m_Sstyzer.ig_sty, m_Sstyzer.fg_sty, &(m_Sstyzer.isuffix) );

    //Clear error message
    m_lasterror = wxEmptyString;

    return -1; //everything was OK
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
int wxFormatStringAsNumber::FormatStr(const wxString& strNumIn,
                                      wxString& strNumOut)
{   strNumOut = wxEmptyString;
    //let's test strNumIn to be a 'number'
    if ( strNumIn.IsEmpty() ) //nothing to format
        return -1;

    if(m_formatStyle.Len() == 0)
    {   m_lasterror = _("No style. No format done");
        return (int)(strNumIn.Len());
    }

    wxString strNup(strNumIn);
    wxChar c;
    int firstNonSpc;
    int posIn = 0;

    strNup.Trim(FALSE); //remove spaces ('\t' '\v' '\f' '\r' '\n' ' ') from the left
    strNup.Trim(); //remove spaces from the right
    int lenNup = (int) strNup.Len();
    if (lenNup == 0)
        return -1; //everything skipped
    firstNonSpc = strNumIn.Find(strNup.GetChar(0));

    //check strNup
    posIn = QCheck(strNup);
    if (posIn >= 0)
    {   m_lasterror = _("Error: not a number");
        return (posIn + firstNonSpc);
    }

    size_t nusty=1, seemsty=3, usesty;
    //how many substyles we have?
    if (m_Sstyneg.sty.Len() > 0)
        nusty=2;
    if (m_Sstyzer.sty.Len() > 0)
        nusty=3;
    
    //analyze what substyle to use
    for (posIn=0; posIn < lenNup; posIn++) //check to use m_styzer style
    {   c = strNup.GetChar((size_t) posIn);
        if ( !(c==wxT('0') || c==wxT('.') ||
               c==wxT('-') || c==wxT('+') ||
               c==wxT('e') || c==wxT('E') ) )
        {   seemsty = 1; //it's not really zero
            break;
        }
    }

    if (nusty == 3 && seemsty == 3)
        usesty = 3;
    else if (nusty > 1 && seemsty < 3 && strNup.GetChar(0) == wxT('-') )
        usesty = 2;
    else
        usesty = 1;

    posIn = StrFor(usesty, strNup, strNumOut);
    if (posIn != -1)
        return (posIn + firstNonSpc);

    m_lasterror = wxEmptyString;
    return -1;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
int wxFormatStringAsNumber::UnFormatStr(const wxString& strIn,
                                        wxString& strOut,
                                        int beStrict)
{   strOut = wxEmptyString;
    if ( strIn.IsEmpty() ) //nothing to unformat
        return -1;

    if(m_formatStyle.Len() == 0)
    {   m_lasterror = _("No style. No unformat done");
        return (int)(strIn.Len());
    }

    //how many substyles we have?
    size_t nusty=1;
    if (m_Sstyzer.sty.Len() > 0)
        nusty=3;
    else if (m_Sstyneg.sty.Len() > 0)
        nusty=2;

    //beStrict == wxUF_NOSTRICT only uses first substyle
    //beStrict == wxUF_BESTRICT uses all substyles. The one that
    //has no errors is the right

    int result1=0, result2=0, result3=0;
    wxString out1, out2, out3;

    result1 = StrUnf(1, strIn, out1, beStrict);
    if (beStrict && nusty > 1)
        result2 = StrUnf(2, strIn, out2, beStrict);
    if (beStrict && nusty == 3)
        result3 = StrUnf(3, strIn, out3, beStrict);

    if ( !beStrict || nusty == 1 )
    {   strOut = out1;
        return result1;
    }
    if ( nusty == 3 && result3 == -1) //first test to be 0
    {   strOut = out3;
        return result3;
    }
    if (result1 == -1)
    {   strOut = out1;
        return result1;
    }
    if (nusty > 1 && result2 == -1)
    {   strOut = out2;
        return result2;
    }
    //none was good, return the first error
    if (result1 <= result2 && 
        ((nusty ==3 && result1 <= result3) || nusty ==2))
    {   strOut = out1;
        return result1;
    }
    if (result2 <= result1 && 
        ((nusty ==3 && result2 <= result3) || nusty ==2))
    {   strOut = out2;
        return result2;
    }
    strOut = out3;
    return result3;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//A quick check to know if strNum is computer-style
int wxFormatStringAsNumber::QCheck(const wxString& strNum)
{
    bool signAlready = FALSE;
    bool decAlready  = FALSE;
    bool expAlready  = FALSE;
    bool sigEAlready = FALSE;
    bool digAlready  = FALSE; //a digit
    wxChar c;
    size_t lenNum = strNum.Len();
    size_t posIn = 0;

    while (posIn < lenNum)
    {   c = strNum.GetChar(posIn);
        if (c == wxT('-') || c == wxT('+'))
            if (expAlready)
                if (sigEAlready || digAlready)
                    return (int) posIn;
                else
                    sigEAlready = TRUE;
            else
                if (signAlready || digAlready || decAlready)
                    return (int) posIn;
                else
                    signAlready = TRUE;
        else if (c == wxT('E') || c == wxT('e'))
            if ( !digAlready || expAlready)
                return (int) posIn;
            else
            {   digAlready = FALSE;
                expAlready = TRUE;
            }
        else if ( c == wxT('.') )
            if (decAlready || expAlready)
                return (int) posIn;
            else
                decAlready = TRUE;
        else if ( wxIs_Digit(c) )
            digAlready = TRUE;
        else
            return (int) posIn;
        posIn++;
    }
    return -1;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//Here is where really formatting is done, given 'usesty'.
//'srIn' must be a no-formatted string (i.e. -1234567.89e90)
// with no blanks, tabs, etc.
int wxFormatStringAsNumber::StrFor(int usesty,
                                   const wxString& srIn,
                                   wxString& srOut)
{
    wxString sto, stex;
    wxString *psty = (wxString*) NULL;
    wxArrayInt *pArray = (wxArrayInt*) NULL;
    size_t ig_sty =0;
    size_t fg_sty =0;
    wxChar pdecsep = wxT('.');

    //NOTE: we use negative values, so better 'int' instead of 'size_t'
    int posdec, posStydec=0, posexp, posStyexp=0;
    int stychartype;
    bool signIn, signExIn, signEIs;
    int posSty, posrIn, pos1sDigitIn, poser, posStyPart; //positions
    int pos1sReq, pos1sDig;
    int lenStrIn = (int) srIn.Len();
    int lenSty;
    wxChar c;

    stFSNData *stData;
    //data and decimal and exponential positions in sub-style
    if (usesty == 1)
        stData = &m_Sstypos;
    else if (usesty == 2)
        stData = &m_Sstyneg;
    else
        stData = &m_Sstyzer;

    psty    = &((*stData).sty);
    pArray  = &((*stData).Asty);
    ig_sty  =   (*stData).ig_sty;
    fg_sty  =   (*stData).fg_sty;
    posStydec = (int) (*stData).idecse;
    posStyexp = (int) (*stData).iexpse;

    lenSty = (int) pArray->GetCount();

    if(posStydec == 0 && pArray->Item(0) != cIsDecSep)
        posStydec = -1; //there is not decimal separator
    stychartype = pArray->Item((size_t) posStyexp);
    if(posStyexp == 0 && !(stychartype == cIsExpU || stychartype == cIsExpL))
        posStyexp = -1; //there is not exponential

    //get sign
    c = srIn.GetChar(0); // 1st char is sign or no-sign is sign = +
    if ( c == wxT('-') )
        signIn = FALSE;
    else
        signIn = TRUE;

    //Some basic positions - - - - - - - - - - - - - - - - - - - - - -
    posexp = srIn.Find(wxT('E'), TRUE);
    if (posexp == wxNOT_FOUND)
        posexp = srIn.Find(wxT('e'), TRUE);

    posdec = srIn.Find(pdecsep);

    if (posdec != wxNOT_FOUND && posexp != wxNOT_FOUND && posdec >= posexp)
    {   m_lasterror = _("Error: decimal separator after exponential");
        return posdec;
    }

    //search first digit before decimal separator
    pos1sDigitIn = 0;
    while (pos1sDigitIn < lenStrIn)
    {   c = srIn.GetChar((size_t) pos1sDigitIn);
        if ( c == pdecsep )
        {   pos1sDigitIn = -1; //no digits
            break;
        }
        if ( wxIs_Digit(c) )
             break;
        if ( posexp != wxNOT_FOUND && pos1sDigitIn == posexp ) // c is exponential
        {   m_lasterror = _("Error: no digits before exponential");
            return pos1sDigitIn;
        }
        pos1sDigitIn++;
    }


    //Method: get from style the next char
    //to match (if digit) or insert (rest of chars)

    //1. All given digits before decimal separator, exponential or
    //   srIn's end, the first we get

    if (posdec == wxNOT_FOUND)
    {   if (posexp != wxNOT_FOUND)
            posrIn = posexp - 1;
        else
            posrIn = lenStrIn - 1;
    }
    else
        posrIn = posdec - 1;

    poser = posrIn;

    //check control: posStyPart == 0 means decimal and exponential parts not done
    posStyPart = 0;
    //where do we start at style to format?
    if (posStydec == -1)
        if (posStyexp == -1)
        {   posSty = lenSty - 1;
            posStyPart = lenSty;
        }
        else
            posSty = posStyexp - 1;
    else
        posSty = posStydec - 1;

    //backwards filling the digits
    while ( posSty >= 0 && posrIn >= 0 && pos1sDigitIn >= 0 && posrIn >= pos1sDigitIn )
    {   c = srIn.GetChar((size_t) posrIn);

        while (posSty >= 0)
        {   stychartype = pArray->Item((size_t) posSty);
            if (stychartype == cIsDigit || stychartype == cIsForced
                || stychartype == cIsBL)
            {   sto = c + sto; //get the digit
                //remember fg_sty is position + 1 of right-most char inside group
                if (fg_sty>0 && ig_sty == (size_t) posSty //reached beguining of group
                    && posrIn > pos1sDigitIn) //and more digits may be formatted
                    posSty = (int)fg_sty - 1; //go to group's finish (at right)
                else
                    posSty--;
                break;
            }
            else //insert all [no-digit] chars till next digit in style
            {   if (stychartype == cIsSignp)
                    if (signIn)
                        sto = wxT('+') + sto;
                    else
                        sto = wxT('-') + sto;
                else if (stychartype == cIsSignn)
                {   if (!signIn)
                        sto = wxT('-') + sto;
                }
                else if (stychartype == cIsChar)
                    sto = psty->GetChar((size_t) posSty) + sto;
            }
            if (fg_sty>0 && ig_sty == (size_t) posSty //reached beguining of group
                && posrIn >= pos1sDigitIn) //and this or more digits may be formatted
                posSty = (int)fg_sty - 1; //go to group's finish
            else
                posSty--;
        }

        posrIn--;
    }

    //2. Rest of required digits ('b' or '0') before decimal separator - - -
    for (pos1sDigitIn = 0; pos1sDigitIn <= posSty; pos1sDigitIn++)
    {   stychartype = pArray->Item((size_t) pos1sDigitIn);
        if(stychartype == cIsForced || stychartype == cIsBL)
            break;
    }
    while ( posSty >= pos1sDigitIn)
    {   stychartype = pArray->Item((size_t) posSty);
        if (stychartype == cIsForced )
            sto = wxT('0') + sto;
        else if (stychartype == cIsBL || stychartype == cIsChar)
            sto = psty->GetChar((size_t) posSty) + sto;
        else if (!signIn && (stychartype == cIsSignp || stychartype == cIsSignn) )
            sto = wxT('-') + sto;
        else if (signIn && stychartype == cIsSignp)
            sto = wxT('+') + sto;
        posSty--;
    }

    //3. Rest before group - - - - -
    if (fg_sty>0 && ig_sty <= (size_t) posSty) //still inside of group
        posSty = (int)ig_sty - 1; //go to group's init -1
    //we must skip all chars, except those at left (prefix)
    //  i.e. ab#+#cd### will skip all '#' and 'cd' but not 'ab' neither '+'
    //locate first from left no-char no-sign
    pos1sDigitIn = 0;
    while (pos1sDigitIn < posSty)
    {   stychartype = pArray->Item((size_t) pos1sDigitIn);
        if (stychartype != cIsSignp && stychartype != cIsSignn && stychartype != cIsChar)
            break;
        pos1sDigitIn++;
    }
    //get the sign if it is between the skipped chars
    while (posSty > pos1sDigitIn)
    {   stychartype = pArray->Item((size_t) posSty);
        if (!signIn && (stychartype == cIsSignp || stychartype == cIsSignn) )
            sto = wxT('-') + sto;
        else if (signIn && stychartype == cIsSignp)
            sto = wxT('+') + sto;
        posSty--;
    }
    if (posSty > pos1sDigitIn && pos1sDigitIn >=0 )
        posSty = pos1sDigitIn;
    //get the chars from pos1sDigitIn to 0
    while (posSty >= 0)
    {   stychartype = pArray->Item((size_t) posSty);
        if (!signIn && (stychartype == cIsSignp || stychartype == cIsSignn) )
            sto = wxT('-') + sto;
        else if (signIn && stychartype == cIsSignp)
            sto = wxT('+') + sto;
        else if (stychartype == cIsChar)
            sto = psty->GetChar((size_t) posSty) + sto ;
        posSty--;
    }


    //4. The decimal part - - - - - - - - - - - - - - - -

    //if no decimal separator, TRUNCATE the number and jump to 6.
    if (posStydec >= 0 && posdec != wxNOT_FOUND)
    {   //Both srIn and style have decimal separator, let's put it
        posSty = posStydec;
        while (posSty >= 0 && pArray->Item((size_t) posSty) == cIsDecSep)
            posSty--; //make sure we are at decsep's init
        posSty++;
        while (posSty < lenSty && pArray->Item((size_t) posSty) == cIsDecSep)
        {   sto = sto + psty->GetChar((size_t) posSty);
            posSty++;
        }

        //is there any decimal digit to get formatted?
        posrIn = posdec + 1;
        //pos1sDigitIn-1 will be the last to format
        if (posexp != wxNOT_FOUND)
            pos1sDigitIn = posexp;
        else
            pos1sDigitIn = lenStrIn; //no exponential

        if (posSty < lenSty)
            stychartype = pArray->Item((size_t) posSty);

        //5. After decimal separator and before exponential- - - - - - - -
        while (posSty < lenSty && stychartype != cIsExpU && stychartype != cIsExpL)
        {   if (stychartype == cIsDigit)// '#' means 'all decimal digits'
            {   while (posrIn < pos1sDigitIn)
                {   sto = sto + srIn.GetChar((size_t) posrIn);
                    posrIn++;
                }
            }
            else if (stychartype == cIsForced || stychartype == cIsBL)
            {   if (posrIn < pos1sDigitIn)
                {   sto = sto + srIn.GetChar((size_t) posrIn);
                    posrIn++;
                }
                else //no more digits in number before exponential
                {   if (stychartype == cIsForced )
                        sto = sto + wxT('0');
                    else //is BL
                        sto = sto + psty->GetChar((size_t) posSty);
                }
            }
            else if (!signIn && (stychartype==cIsSignp || stychartype==cIsSignn))
                sto = sto + wxT('-');
            else if (signIn && stychartype == cIsSignp)
                sto = sto + wxT('+');
            else if (stychartype == cIsChar)
                sto = sto + psty->GetChar((size_t) posSty);

            posSty++;
            if (posSty < lenSty)
                stychartype = pArray->Item((size_t) posSty);
        }
        posStyPart = posSty;
    }

    //6. Exponential- - - - - - - - - - - - - - - - -
    //Get only from exponential, so may truncate some number's decimal digits
    if ( posexp != wxNOT_FOUND && posStyexp != -1 )
    {   //Is 'e' in both number and style? If so, write it
        stychartype = pArray->Item((size_t) posStyexp);
        if ( stychartype == cIsExpU )
            sto = sto + wxT('E');
        else
            sto = sto + wxT('e');

        //Is there a sign for exponential in srIn?
        signEIs = FALSE; //perphaps sign is not typed yet (i.e. '1.23E')
        //The exponential sign
        signExIn = TRUE; //presumed to be + even if signEIs==FALSE
        pos1sDigitIn = posexp + 1;
        if (posexp < lenStrIn-1) //posexp is not the last char, so next may be sign
        {   c = srIn.GetChar((size_t) pos1sDigitIn);
            if ( c == wxT('-') || c == wxT('+') )
            {   signEIs=TRUE;
                pos1sDigitIn++; //avance to first exponential digit, if any
                if ( c == wxT('-') ) signExIn = FALSE;
            }
        }

        //We use 'pos1sReq' to store the first required digit in sytle
        for (pos1sReq = posStyexp + 1; pos1sReq < lenSty; pos1sReq++)
        {   stychartype = pArray->Item((size_t) pos1sReq);
            if (stychartype == cIsForced || stychartype == cIsBL)
                break;
        }
        //We use 'pos1sDig' to store the first [required] digit in sytle
        for (pos1sDig = posStyexp + 1; pos1sDig < lenSty; pos1sDig++)
        {   stychartype = pArray->Item((size_t) pos1sDig);
            if (stychartype == cIsDigit || stychartype == cIsForced
                || stychartype == cIsBL)
                break;
        }

        posrIn = lenStrIn - 1; //we'll read backwards until pos1sDigitIn
        posSty = lenSty - 1;
        posStyPart = lenSty;
        poser = posrIn;

        //backwards filling the digits
        while ( posrIn >= pos1sDigitIn || posSty > posStyexp )
        {   if (posrIn >= pos1sDigitIn)
                c = srIn.GetChar((size_t) posrIn);
            if (posSty <= posStyexp) //not enough style-size for the number
            {   m_lasterror = _("Error: too many digits in exponential");
                return poser;
            }
            stychartype = pArray->Item((size_t) posSty);
            if (stychartype == cIsDigit || stychartype == cIsForced
                || stychartype == cIsBL)
            {   if (posrIn >= pos1sDigitIn) //srIn has a new digit to write
                    stex = c + stex; //get the digit
                else if (stychartype == cIsForced)
                    stex = wxT('0') + stex;
                else if (stychartype == cIsBL)
                    stex = psty->GetChar((size_t) posSty) + stex;
                posrIn--;
            }
            //Only put the exponential sign if required or srIn has it
            else if (stychartype == cIsSignpE || (stychartype == cIsSignnE && signEIs))
            {   if ( signExIn )
                    stex = wxT('+') + stex;
                else
                    stex = wxT('-') + stex;
            }
            //the number's sign
            else if (!signIn && (stychartype == cIsSignp || stychartype == cIsSignn) )
                stex = wxT('-') + stex;
            else if (signIn && stychartype == cIsSignp)
                stex = wxT('+') + stex;
            //style requires a char
            else if (stychartype == cIsChar && (posSty >= pos1sReq //pos1sReq is first required
                     || posrIn >= pos1sDigitIn || posSty < pos1sDig))
                stex = psty->GetChar((size_t) posSty) + stex ;

            posSty--;
        }

        sto = sto + stex;
    }

    //7. Last part: style may require chars and numb's sign
    //we know this because posStyPart < lenSty
    if (posStyPart < lenSty)
    {   posSty = lenSty - 1;
        stychartype = pArray->Item((size_t) posSty);
        while ( stychartype == cIsChar
                || stychartype == cIsSignp || stychartype == cIsSignn )
            stychartype = pArray->Item((size_t) --posSty);
        posSty++;
        //now the rest of chars
        while (posSty < lenSty)
        {   stychartype = pArray->Item((size_t) posSty);
            if (!signIn && (stychartype == cIsSignp || stychartype == cIsSignn) )
                sto += wxT('-');
            else if (signIn && stychartype == cIsSignp)
                sto += wxT('+');
            else if (stychartype == cIsChar)
                sto += psty->GetChar((size_t) posSty);

            posSty++;
        }
    }

    srOut = sto;
    m_lasterror = wxEmptyString;
    return -1; //input is OK, format done
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//The unformat function. If beStc == wxUF_BESTRICT returns when first error
//is found, this is, srIn is not formatted with the sub-style
int wxFormatStringAsNumber::StrUnf(int usesty,
                                   const wxString& srIn,
                                   wxString& srOut,
                                   int beStc)
{
    wxString sto, stex;
    wxString *psty = (wxString*) NULL;
    wxArrayInt *pArray = (wxArrayInt*) NULL;
    size_t ig_sty =0;
    size_t fg_sty =0;
    wxString *p_sdec = (wxString*) NULL;
    int suffixpos;

    //NOTE: we use negative values, so better 'int' instead of 'size_t'
    int posdec=0, posStydec=0, posexp, posStyexp=0;
    int stychartype;
    bool signIn, signExIn, gotN, gotS, suffix;
    int posSty, posrIn, pos1sDigitIn, posgroup, poser; //positions
    int numDigSty=0, numDigIn=0; //number of digits
    int wtdwtc; //response
    int lenStrIn = (int) srIn.Len();
    int lenSty;
    wxChar cI, cS;
    wxArrayInt* arrMinDig = (wxArrayInt*) NULL;

    stFSNData *stData;
    //data and decimal/exponential/suffix positions in sub-style
    if (usesty == 1)
        stData = &m_Sstypos;
    else if (usesty == 2)
        stData = &m_Sstyneg;
    else
        stData = &m_Sstyzer;

    psty    = &((*stData).sty);
    pArray  = &((*stData).Asty);
    ig_sty  =   (*stData).ig_sty;
    fg_sty  =   (*stData).fg_sty;
    posStydec = (int) (*stData).idecse;
    posStyexp = (int) (*stData).iexpse;
    suffixpos = (int) (*stData).isuffix;
    p_sdec  =   &((*stData).decsep);
    arrMinDig = &((*stData).AminD);

    lenSty = (int) pArray->GetCount();

    if(posStydec == 0 && pArray->Item(0) != cIsDecSep)
        posStydec = -1; //there is not decimal separator
    //Check exponential position to be >0 or there is not exponential
    stychartype = pArray->Item((size_t) posStyexp);
    if(posStyexp == 0 && !(stychartype == cIsExpU || stychartype == cIsExpL))
        posStyexp = -1; //there is not exponential


    //Some basic positions - - - - - - - - - - - - - - - - - - - - - -
    //If we have not decimal separator and/or exponential in sub-style
    //we don't search for them. If they exist in srIn, we'll push an error.
    //Other case, we must know where decimal separator and exponential are.
    //Because srIn may have several 'e', which one is exponential?
    //I have not a better idea than getting the first 'e' at left of the
    //first digit, searching finish to beguinning (right to left)
    //If in not strict mode, just get the first 'e' from the right
    //To find decimal separator (in strict & !strict modes) we just
    //get the first ocurrence (from left to right) in srIn.
    //If !strict mode we'll search the first ocurrence of any of the
    //decimal separator chars
    //I know this can't cope with all cases, but 90% (100% of 'normal')
    //TODO: an infallible way

    m_lasterror = _("Error in input string"); //prepare message (generic)

    if ( p_sdec->Len() >0 ) //have we decimal separator to search for?
    {   if (beStc == wxUF_BESTRICT) //stric mode, search the whole decimal separator
            posdec = srIn.Find(*p_sdec);
        else //tolerant: search first ocurrence of any *p_sdec's char
        {   for (posSty = 0 ; posSty < (int)p_sdec->Len() ; posSty++)
            {   posdec = srIn.Find(p_sdec->GetChar(posSty));
                if (posdec != wxNOT_FOUND)
                    break;
            }
        }
    }
    else
        posdec = wxNOT_FOUND;

    //go to *p_sdec's end for searching exponential
    //if *p_sdec contains a 'e' this may trick to !strict mode
    if (posdec != wxNOT_FOUND && beStc == wxUF_BESTRICT)
        posdec += (int) p_sdec->Len() - 1;

    posexp = -1; //looking for exponential in srIn
    posrIn = lenStrIn - 1;
    gotN = FALSE;
    while (posrIn > posdec)
    {   cI = srIn.GetChar((size_t) posrIn);
        if((cI == wxT('E') || cI == wxT('e'))
           && (beStc == wxUF_NOSTRICT || (beStc == wxUF_BESTRICT && gotN)))
        {   posexp = posrIn;
            break;
        }
        if (!gotN && wxIs_Digit(cI)) gotN = TRUE;
        posrIn--;
    }
    if (posdec != wxNOT_FOUND && beStc == wxUF_BESTRICT)
        posdec -= (int) p_sdec->Len() - 1;

    //Despite of an 'e' has been found, if style hasn't exponential, let's presume
    //nor number either. Otherwise an error will be returned.
    if (posexp != wxNOT_FOUND && posStyexp == -1)
        posexp = wxNOT_FOUND;

    signIn = TRUE; //assume number to be positive

    //Before unformatting we'll strip out suffix.
    //wxUF_BESTRICT analize suffix exactly char by char.
    //wxUF_NOSTRICT will stop at first digit
    suffix = (suffixpos < lenSty) ? TRUE : FALSE;
    if (suffix == TRUE)
    {   posSty = lenSty - 1;
        posrIn = lenStrIn - 1;
        numDigSty = numDigIn = 0;
        while (posSty >= suffixpos)
        {   gotN = gotS = FALSE;
            if (posrIn >= 0 )
                cI = srIn.GetChar((size_t) posrIn);
            else
                break;
            if (posSty >= 0 )
            {   cS = psty->GetChar((size_t) posSty);
                stychartype = pArray->Item((size_t) posSty);
            }
            if (wxIs_Digit(cI))
                if(beStc == wxUF_BESTRICT)
                {   if (cI == cS)
                        gotN = gotS = TRUE;
                    else
                    {   m_lasterror = _("char required");
                        return posrIn; //error
                    }
                }
                else
                    break;
            else
            {   wtdwtc = WhatToDoWithThisChar(numDigSty, &numDigIn,
                           &cI, &cS, stychartype, beStc,
                           &signIn, &signExIn, &gotN, &gotS, 1);
                if (wtdwtc == 0)
                    return posrIn; //error
            }
            if (gotN) posrIn--;
            if (gotS) posSty--;
        }
        lenStrIn = posrIn + 1;
        lenSty = posSty + 1;
        if (lenStrIn <= 0 && lenSty <= 0) //everything is suffix, number is zero
        {   srOut = wxT('0');
            m_lasterror = wxEmptyString;
            return -1;
        }
    }


    //1. All given digits before decimal separator - - - - - - - -
    //position in srIn to init unformatting
    if (posdec == wxNOT_FOUND)
    {   if (posexp != wxNOT_FOUND)
            posrIn = posexp - 1;
        else
            posrIn = lenStrIn - 1;
    }
    else
        posrIn = posdec - 1;

    //number of [possible] digits in srIn before decimal separator
    for (poser = 0; poser <= posrIn; poser++)
    {   cI = srIn.GetChar((size_t) poser);
        if (wxIs_Digit(cI))
            numDigIn++;
    }

    //Position in style to init unformatting
    if (posStydec == -1)
        posSty = (posStyexp == -1) ? (lenSty - 1) : (posStyexp - 1);
    else
        posSty = posStydec - 1;

    poser = posrIn; //position of possible error
    if (poser < 0)
        poser = (int) srIn.Len();
    posgroup = -1; //means: no group

    //posrIn < 0 may be, let's check if it is allowed
    if (posSty < (int) arrMinDig->GetCount()) //no minimun digits, may be third style
        numDigSty = arrMinDig->Item((size_t) posSty);
    else
        numDigSty = 0;
    if (posrIn < 0 && abs(numDigSty) > 0)
    {   m_lasterror = _("digits needed");
        return poser; //error, digits needed
    }

    //backwards extracting the digits
    if (posrIn >=0 )
        cI = srIn.GetChar((size_t) posrIn);
    if (posSty >=0 )
    {   cS = psty->GetChar((size_t) posSty);
        stychartype = pArray->Item((size_t) posSty);
    }

    while (posrIn >= 0 || posSty >= 0)
    {   gotN = gotS = FALSE;
        if (posSty < 0 && posrIn >= 0) //not enough style-size for the number
        {   if (beStc == wxUF_NOSTRICT && numDigIn == 0) //rest in srIn are chars
                break;
            m_lasterror = _("Error: too many digits or chars");
            return poser;
        }
        if (posSty < (int) arrMinDig->GetCount()) //no minimun digits, may be third style
            numDigSty = arrMinDig->Item((size_t) posSty);
        else
            numDigSty = 0;

        if (posSty >= 0 && posrIn < 0 //no more to unformat
            && numDigSty != 0)//but style requires more
        {   m_lasterror = _("digits needed");
            return poser;
        }

        //The function analize cases for cI/cS combinations:
        wtdwtc = WhatToDoWithThisChar(numDigSty, &numDigIn,
                       &cI, &cS, stychartype, beStc,
                       &signIn, &signExIn, &gotN, &gotS, 1);
        if (wtdwtc == 0)
            return posrIn; //error
        if (wtdwtc == 1)
        {   sto = cI + sto; //get the digit
            numDigIn--;
        }

        //now move positions
        if (gotN) //move number position
        {   posrIn--;
            if (posrIn >= 0)
                cI = srIn.GetChar((size_t) posrIn);
        }
        if (posrIn < 0) //let's check if we can leave out
        {   while (--posSty >= 0)
            {   if (posSty < (int) arrMinDig->GetCount())
                    numDigSty = arrMinDig->Item((size_t) posSty);
                else
                    numDigSty = 0;
                stychartype = pArray->Item((size_t) posSty);
                if (stychartype == cIsForced || stychartype == cIsBL
                    || stychartype == cIsSignp)
                {   m_lasterror = _("something more is required");
                    return 0; //something more is required
                }
                if (beStc == wxUF_BESTRICT
                     && ( numDigSty < 0
                        || (fg_sty > 0 && ig_sty > (size_t) posSty && stychartype != cIsSignn) ))
                    return 0; //more chars are required
            }
        }
        if (gotS && posSty >= 0) //move style position
        {   // posgroup = -1 means there's no group or we're not inside the group
            //remember fg_sty is position + 1 of right-most char inside group
            if (fg_sty > 0) //there's group
            {   if (ig_sty == (size_t) posSty) //reached beguining (at left) of group
                    posgroup = 0;
                else if (ig_sty < (size_t) posSty && fg_sty > (size_t) posSty)
                    posgroup = 1; //still inside of group
                else
                    posgroup = -1; //outside of group, not reached yet
            }

            if (posgroup == 0 //reached beguining of group
                && numDigIn > 0) //and more digits may be unformatted
            {   if (ig_sty > 0  //may be prefix
                    && arrMinDig->GetCount() > 0
                    && numDigIn == abs(arrMinDig->Item(ig_sty - 1))) //digits in prefix
                    posSty--;
                else
                    posSty = (int)fg_sty - 1; //go to group's finish (at right) for a new loop
            }
            else if (posgroup == 1
                     && ((ig_sty > 0
                         && arrMinDig->GetCount() > 0
                         && numDigIn == abs(arrMinDig->Item(ig_sty - 1)))
                         || (ig_sty == 0 && numDigIn == 0))) //must we leave the group?
            {   for (posgroup = posSty - 1; posgroup >= (int)ig_sty; posgroup--)
                {   stychartype = pArray->Item((size_t) posgroup);
                    if (stychartype == cIsForced || stychartype == cIsBL)
                        break;
                }
                if (posgroup < (int)ig_sty) //we can leave
                    posSty = (int)ig_sty -1;
                else
                    posSty--; //an error will raise soon
            }
            else
                posSty--;
            if (posSty >= 0)
            {   cS = psty->GetChar((size_t) posSty);
                stychartype = pArray->Item((size_t) posSty);
            }
        }
    }

    //2. Decimal digits before exponential - - - - - - - - - - - - - -
    if (posdec != wxNOT_FOUND && posStydec == -1) //srIn has decimal part, style hasn't 
        return posdec; //srIn was not formatted with this sub-style
    if (posdec != wxNOT_FOUND && posStydec != -1)
    {   sto += wxT('.');

        if (beStc == wxUF_BESTRICT)
            posrIn = posdec + (int) p_sdec->Len();
        else
            posrIn = posdec + 1; //the rest of *p_sdec's chars will be skipped

        //pos1sDigitIn-1 will be the last to unformat in this decimal part
        if (posexp != wxNOT_FOUND)
            pos1sDigitIn = posexp;
        else
            pos1sDigitIn = lenStrIn; //no exponential

        //number of [possible] digits in srIn after decimal separator before exponential
        numDigIn = 0;
        for (poser = posrIn; poser < pos1sDigitIn; poser++)
        {   cI = srIn.GetChar((size_t) poser);
            if (wxIs_Digit(cI))
                numDigIn++;
        }
        //store min number of digits required by style
        posSty = (posStyexp != -1) ? (posStyexp - 1) : (lenSty - 1);
        if (posSty < (int) arrMinDig->GetCount() )
            posgroup = arrMinDig->Item((size_t) posSty);
        else
            posgroup = 0;

        posSty = posStydec + (int) p_sdec->Len();

        if (posrIn < pos1sDigitIn)
            cI = srIn.GetChar((size_t) posrIn);
        if (posSty < lenSty )
        {   cS = psty->GetChar((size_t) posSty);
            stychartype = pArray->Item((size_t) posSty);
        }
        while (posrIn < pos1sDigitIn && posSty < lenSty &&
               stychartype != cIsExpU && stychartype != cIsExpL)
        {   gotN = gotS = FALSE;
            //arrMinDig was stored for backwards-mode use, not left to right
            if (posSty < (int) arrMinDig->GetCount() )
                numDigSty = arrMinDig->Item((size_t) posSty);
            else
                numDigSty = 0;
            if (numDigSty < 0)
                numDigSty = -abs(posgroup) - numDigSty - 1;
            else
                numDigSty = abs(posgroup) - numDigSty;

            //cases for cI/cS:
            wtdwtc = WhatToDoWithThisChar(numDigSty, &numDigIn,
                       &cI, &cS, stychartype, beStc,
                       &signIn, &signExIn, &gotN, &gotS, 2);//'2' means decimal case
            if (wtdwtc == 0)
                return posrIn; //error
            if (wtdwtc == 1)
            {   sto = sto + cI; //get the digit
                numDigIn--;
            }
            //move positions
            if (gotN)
            {   posrIn++;
                if (posrIn < pos1sDigitIn)
                    cI = srIn.GetChar((size_t) posrIn);
            }
            if (gotS)
            {   posSty++;
                if (posSty < lenSty)
                {   cS = psty->GetChar((size_t) posSty);
                    stychartype = pArray->Item((size_t) posSty);
                }
            }
        }
    }

    //3. exponential - same method as for integer part - - - -
    if ( posexp != wxNOT_FOUND && posStyexp != -1 )
    {   sto += wxT('E');
        stex = "";
        posrIn = lenStrIn - 1;
        numDigIn = 0;
        //number of [possible] digits in srIn's exponential part
        for (poser = posexp + 1; poser <= posrIn; poser++)
        {   cI = srIn.GetChar((size_t) poser);
            if (wxIs_Digit(cI))
                numDigIn++;
        }

        posSty = lenSty - 1;

        //backwards extracting the digits
        if (posrIn >=0 )
            cI = srIn.GetChar((size_t) posrIn);
        if (posSty >=0 )
        {   cS = psty->GetChar((size_t) posSty);
            stychartype = pArray->Item((size_t) posSty);
        }
        while (posrIn > posexp || posSty > posStyexp)
        {   gotN = gotS = FALSE;
            if (posSty <= posStyexp && posrIn > posexp) //not enough style-size for the number
            {   if (beStc == wxUF_NOSTRICT && numDigIn == 0) //rest in srIn are chars
                    break;
                m_lasterror = _("Error: too many digits or chars");
                return poser;
            }
            if (posSty >= posStyexp && posrIn < posexp //no more to unformat
                && beStc == wxUF_BESTRICT)//but style requires more
                    return poser;

            if (posSty < (int) arrMinDig->GetCount()) //no minimun digits, may be third style
                numDigSty = arrMinDig->Item((size_t) posSty);
            else
                numDigSty = 0;

            //The function analize cases for cI/cS combinations:
            wtdwtc = WhatToDoWithThisChar(numDigSty, &numDigIn,
                           &cI, &cS, stychartype, beStc,
                           &signIn, &signExIn, &gotN, &gotS, 3);
            if (wtdwtc == 0)
                return posrIn; //error
            if (wtdwtc == 1)
            {   stex = cI + stex; //get the digit
                numDigIn--;
            }

            //now move positions
            if (gotN) //move number position
            {   posrIn--;
                if (posrIn >= 0)
                    cI = srIn.GetChar((size_t) posrIn);
            }
            if (posrIn <= posexp) //let's check if we can leave out
            {   while (--posSty > posStyexp)
                {   if (posSty < (int) arrMinDig->GetCount())
                        numDigSty = arrMinDig->Item((size_t) posSty);
                    else
                        numDigSty = 0;
                    stychartype = pArray->Item((size_t) posSty);
                    if (stychartype == cIsForced || stychartype == cIsBL
                        || stychartype == cIsSignp || stychartype == cIsSignpE)
                        return posexp; //something more is required
                    if (beStc == wxUF_BESTRICT && numDigSty < 0)
                        return posexp; //more chars are required
                }
            }
            if (gotS) //move style position
            {   posSty--;
                if (posSty >= 0)
                {   cS = psty->GetChar((size_t) posSty);
                    stychartype = pArray->Item((size_t) posSty);
                }
            }
        }
        if (!signExIn)
            sto += wxT('-');
        sto += stex;
    }

    if (!signIn || usesty == 2)
        sto = wxT('-') + sto;
    srOut = sto;
    m_lasterror = wxEmptyString;
    return -1;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//This function, used when Unformatting, fills an array whose elements means:
//  "minimum number of digits to get if this position is used'.
//Explanation: suppose style is 'xx1x[203##]4##' where 1234 are chars.
//  Formatting '5' becomes into 'xx1x0345'.
//  Unformatting position by position, '5' corresponds to right-most '#'
//  but '4' doesn't correspond to next '#', because it was needed to form the
//  the formatted string.
//We deal with this knowing how many _minimum_ digits were written when formatting.
//I.e. the '#' (7th position) at left needs at least 3 digits (1 0 3).
//
//A second information we store in this array is if digit-char is treated as a 
//'minimum to get'. If it is true, we store a negative value, else a positive one.
//
//So:    char  position    arrMinDig->Item(position)
//         x       0              0
//         x       1              0
//         1       2             -1                 It is prefix, so required.
//         x       3              1
//         2       4              1                 Positive because perhaps it is not used.
//         0       5             -2                 A '0' is always used.
//         3       6             -3                 Must be used to reach to '0' at left.
//         #       7              3
//         #       8              3
//         4       9             -4                 Must be used to reach to '0' at left.
//         #      10              4
//         #      11              4
//The function also set suffix position
void wxFormatStringAsNumber::FillArrayMinDig(wxArrayInt *arrMinDig,
        wxArrayInt *pArray, wxString *psty, size_t ig_sty, size_t fg_sty, size_t *suffixpos)
{
    size_t posSty=0;
    int stychartype;
    size_t lenSty;
    wxChar cS;
    bool forcedYet = FALSE, digYet = FALSE;
    bool insidegroup = FALSE, decpart= FALSE;
    int numToAdd=0;

    arrMinDig->Clear();
    lenSty = pArray->GetCount();

    //is there a suffix?
    *suffixpos = lenSty;
    for (posSty = lenSty - 1; posSty >= 0 && posSty < lenSty; posSty--)
    {   stychartype = pArray->Item(posSty);
        if (stychartype == cIsSignp || stychartype == cIsSignn || stychartype == cIsChar)
            *suffixpos = posSty;
        else
            break;
    }

    //analize
    for (posSty = 0; posSty < *suffixpos; posSty++)
    {   cS = psty->GetChar(posSty);
        stychartype = pArray->Item(posSty);
        //remember fg_sty is position + 1 of right-most char inside group
        if (fg_sty > 0 && posSty >= ig_sty && posSty < fg_sty) //inside group
            insidegroup = TRUE;
        else
            insidegroup = FALSE;

        if (stychartype == cIsExpU || stychartype == cIsExpL || stychartype == cIsDecSep)
        {   numToAdd = 0;
            digYet = forcedYet = FALSE;
            decpart = (stychartype == cIsDecSep) ? TRUE : FALSE;
        }
        else if (stychartype == cIsForced
                 || (wxIs_Digit(cS)
                     && (stychartype == cIsBL || !digYet || forcedYet || decpart
                         || posSty >= *suffixpos) ) )
        {   if (posSty > 0)
                numToAdd = -(abs(arrMinDig->Item(posSty-1)) + 1);
            else
                numToAdd = -1;
            if (stychartype == cIsChar && !forcedYet && insidegroup)
                numToAdd = -(++numToAdd);
        }
        else
        {   if (posSty > 0)
                numToAdd = abs(arrMinDig->Item(posSty-1));
            else
                numToAdd = 0;
        }
        if (stychartype == cIsForced || stychartype == cIsBL || stychartype == cIsDigit)
        {   digYet = TRUE;
            if (stychartype != cIsDigit)
                forcedYet = TRUE;
        }

        arrMinDig->Add(numToAdd);
    }
    return;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//A helper for Unformatting.
// ana=1 means integer part. ana=2 decimal  ana=3 exponential
int wxFormatStringAsNumber::WhatToDoWithThisChar(
         int numDigSty, int* numDigIn,
         const wxChar* cI, const wxChar* cS, int stychartype, int beStc,
         bool *signIn, bool *signExIn, bool *gotN, bool *gotS, int ana )
{   //check if at this point style requires more digits than srIn has
    if (*numDigIn < abs(numDigSty))
        return 0; //error
    //analize four cases for cI/cS combination:
    if (wxIs_Digit(*cI))
    {   if (stychartype == cIsForced || stychartype == cIsBL) //digit is required
        {   *gotN = TRUE; //means: 'need posrIn++ or posrIn--'
            *gotS = TRUE; //means: 'need posSty++ or posSty--'
            return 1; //get the digit
        }
        else if (stychartype == cIsDigit) //cIsDigit is a '#' in style
        {   if (ana != 2)
            {   if (abs(numDigSty) < *numDigIn) //srIn has _more_ digits than minimum required
                {   *gotN = TRUE;
                    *gotS = TRUE;
                    return 1; //get the digit
                }
                else //this digit belongs to other char in style
                {   *gotS = TRUE; //let's skip this '#'
                    return -1; //just move pointers and loop again
                }
            }
            else //decimal part, usually move pointer in srIn, but not in style
            {   if (*numDigIn - abs(numDigSty) == 1)
                {   *gotN = *gotS = TRUE; //rest ot digits are required, so avance style
                    return 1; //get the digit and avance pointers
                }
                else if (*numDigIn - abs(numDigSty) == 0)
                {   *gotS = TRUE; //reserve the digit for later on
                    return -1; //don't get the digit
                }
                *gotN = TRUE; //normal case
                return 1;
            }
        }
        else if (stychartype == cIsSignp)
            return 0; //error, a sign is required
        else if (stychartype == cIsSignn || stychartype == cIsSignnE) //the sign is optional
            *gotS = TRUE;
        else
        {   if (ana != 2)
            {   if (abs(numDigSty) < *numDigIn) //srIn has _more_ digits than minimum required
                {   if (*cI == *cS) //this 'digit' was really a char
                    {   (*numDigIn)--;
                        *gotN = *gotS = TRUE;
                    }
                    else
                    {   if (beStc == wxUF_BESTRICT)
                            return 0; //error
                        else
                            *gotS = TRUE; //skip this char in style
                    }
                }
                else //we must tell if this digit must be used
                {   if (numDigSty < 0)
                    {   if (*cI == *cS) //this 'digit' was really a char
                        {   (*numDigIn)--;
                            *gotN = *gotS = TRUE;
                        }
                        else
                        {   if (beStc == wxUF_BESTRICT)
                                return 0; //error
                            else
                                *gotS = TRUE; //skip this char in style
                        }
                    }
                    else
                    {   *gotS = TRUE; //let's skip this char
                        return -1; //just move pointers and loop again
                    }
                }
            }
            else //decimal part
            {   if (*cI == *cS) //this 'digit' was really a char
                {   (*numDigIn)--;
                    *gotN = *gotS = TRUE;
                }
                else
                {   if (beStc == wxUF_BESTRICT)
                        return 0; //error
                    else
                        *gotS = TRUE; //skip this char in style
                }
            }
        }
    }
    else if (stychartype == cIsDigit //cI isn't a digit and cS is '#'
             && abs(numDigSty) == *numDigIn) //test to see if this '#' must be used
    {   *gotS = TRUE; //let's skip this '#'
        return -1; //just move pointers and loop again
    }

    else if (*cI == wxT('+'))
    {   if(stychartype == cIsDigit || stychartype == cIsForced || stychartype == cIsBL)
        {   if (beStc == wxUF_BESTRICT)
                return 0; //error
            else
                *gotN = TRUE; //presume cI to be a typo
        }
        else if (stychartype == cIsSignp || stychartype == cIsSignpE)
            *gotN = *gotS = TRUE; //we have yet assumed signIn==signExIn==TRUE
        else if (beStc == wxUF_BESTRICT)
        {   if (*cI == *cS)
                *gotN = *gotS = TRUE;
            else
                return 0; //error
        }
        else //cS is '-' or a char, but we are tolerant so...
            *gotN = *gotS = TRUE;
    }
    else if (*cI == wxT('-'))
    {   if(stychartype == cIsDigit || stychartype == cIsForced || stychartype == cIsBL)
        {   if (beStc == wxUF_BESTRICT)
                return 0; //error
            else
                *gotN = TRUE; //this '-' is a typo. Skip it.
        }
        else if (stychartype == cIsSignp || stychartype == cIsSignn)
        {   *signIn = FALSE;            
            *gotN = *gotS = TRUE;
        }
        else if (stychartype == cIsSignpE || stychartype == cIsSignnE)
        {   *signExIn = FALSE;            
            *gotN = *gotS = TRUE;
        }
        else if (beStc == wxUF_BESTRICT)
        {   if (*cI == *cS)
                *gotN = *gotS = TRUE;
            else
                return 0; //error
        }
        else
            *gotS = TRUE; //let's skip the char, keep '-' at cI
    }
    else //any char. No digit or sign
    {   if (beStc == wxUF_BESTRICT)
        {   if (stychartype == cIsSignn || stychartype == cIsSignnE)
            {   *gotS = TRUE;
                return -1;
            }
            if (*cI == *cS)
                *gotN = *gotS = TRUE;
            else
                return 0; //error
        }
        else
        {   *gotN = TRUE;
            if (stychartype == cIsChar)
                *gotS = TRUE;
        }
    }
    return -1;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//The trim zeros function
//Notes: 
// - we want at least one '0' before decimal
// - Trim zeros on integer and decimal parts, not exponential
// - If integer and decimal parts are zero (i.e. -0.00E+25) we return '0'
//   no matter sign or exponential
void wxFormatStringAsNumber::TrimZeros(wxString& strNum, int atside)
{
    wxString stmp;
    wxChar cI;
    size_t posNi, posNf, posNe;
    size_t lenN = strNum.Len();
    bool nozero = FALSE;
    if (lenN == 0 || ((atside & wxTZ_LEFT) == 0 && (atside & wxTZ_RIGHT) == 0) )
        return;

    //obtain positions
    posNi = 0;
    //at left
    if (atside & wxTZ_LEFT)
    {   cI = strNum.GetChar(posNi);
        if ( cI == wxT('+') || cI == wxT('-') )
        {   stmp = cI;
            posNi++;
        }
        while (posNi < lenN)
        {   cI = strNum.GetChar(posNi);
            if ( cI != wxT('0'))
                break;
            else
                posNi++;
        }
        //we want at least one '0' before decimal
        if (cI == wxT('.'))
            stmp += wxT('0');
    }
    posNe = lenN;
    posNf = lenN - 1;
    //at right, only if decimal part exist
    if ( (atside & wxTZ_RIGHT) && (strNum.Find(wxT('.'), TRUE) != wxNOT_FOUND) )
    {   posNf = strNum.Find(wxT('E'), TRUE);
        if (posNf == wxNOT_FOUND)
            posNf = strNum.Find(wxT('e'), TRUE);
        if (posNf == wxNOT_FOUND)
            posNf = lenN;
        posNe = posNf;
        posNf--;
        while (posNf >= 0)
        {   if (strNum.GetChar(posNf) != wxT('0'))
                break;
            else
                posNf--;
        }
    }
    //Get the chars
    while (posNi <= posNf)
    {   cI = strNum.GetChar(posNi++);
        if ( wxIs_Digit(cI) && cI != wxT('0') )
            nozero = TRUE;
        stmp += cI;
    }
    //Before adding exponential, let's see if number is really zero
    if ( !nozero ) //no digit before exponential or all digit was '0'
    {   strNum = wxT('0');
        return;
    }
    //add exponential part
    while (posNe < lenN)
        stmp += strNum.GetChar(posNe++);

    strNum = stmp;
}


 	  	 

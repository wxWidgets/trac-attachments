/*
	NAME:		StartsWithProblem_Console.cpp
	DATE:		28Jun2007
	AUTHOR:		Scott Furry
	PURPOSE:	Demonstration of how wxString::StartsWith fails
	
	NOTE:   Initial problem was that the first call to StartsWith would work
	        but subsequent calls would fail. I believe this to be a situation
			where the test for last declared const wxChar would pass but ALL
	        other calls to wxString::StartsWith using the address of a wxChar
	        would fail.

	LINK: https://sourceforge.net/tracker/?func=detail&atid=109863&aid=1744597&group_id=9863
			As suggested in the thread to sourceforge wxWindows bug report #1744597
			this situation could be related to wxChar not be null terminated

	NOTE: 	C++ compiler settings
			-D__WXMSW__
			-D__GNUWIN32__
			-D__WIN95__
			-D_UNICODE
*/
#include <cstdlib>
#include <iostream>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/string.h>

void DemoBugWithwxChar(wxString& strToBeSearch);

const wxChar C_TEST_COND_ONE(wxT('@'));
const wxChar C_TEST_COND_TWO(wxT('#'));
const wxChar C_TEST_COND_THREE(wxT('$'));

using namespace std;

int main(int argc, char *argv[])
{

	cout << "Using wxString::StartsWith to search three strings for characters:"
		 << "\nCondition One  : " << (char)C_TEST_COND_ONE
		 << "\nCondition Two  : " << (char)C_TEST_COND_TWO
		 << "\nCondition Three: " << (char)C_TEST_COND_THREE << endl << endl;

	wxString firstStr(wxT("@abcdefg"));     //should pass first test;
	wxString secondStr(wxT("#abcdefg"));    //should pass second test;
	wxString thirdStr(wxT("$abcdefg"));     //should pass third test;
	wxString fourthStr(wxT("abcdefg"));     //should fail all tests

	DemoBugWithwxChar(firstStr);
	DemoBugWithwxChar(secondStr);
	DemoBugWithwxChar(thirdStr);
	DemoBugWithwxChar(fourthStr);
	
    system("PAUSE");
    return EXIT_SUCCESS;
}

void DemoBugWithwxChar(wxString& strToBeSearch)
{
	bool bCondOne	= false;
	bool bCondTwo	= false;
	bool bCondThree = false;
	wxString sTrimmed(wxEmptyString);

	bCondThree	= strToBeSearch.StartsWith(&C_TEST_COND_THREE, &sTrimmed);
	bCondTwo	= strToBeSearch.StartsWith(&C_TEST_COND_TWO, &sTrimmed);
	bCondOne	= strToBeSearch.StartsWith(&C_TEST_COND_ONE);

	std::cout << "Tests Results (wxChar): " << bCondOne << "  " << bCondTwo << "  " << bCondThree << std::endl;
	std::cout << "Input String: " << strToBeSearch.mb_str(wxConvUTF8) << std::endl;
	std::cout << "Trimmed Str: " << sTrimmed.mb_str(wxConvUTF8) << std::endl;
}

 	  	 

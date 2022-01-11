#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include "wx/dynarray.h"

WX_DECLARE_OBJARRAY(wxString, ArrayOfString);
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ArrayOfString);

WX_DEFINE_ARRAY(int, ArrayOfInt);

static void theTest()
{
	wxArrayString a;
	wxArrayString::const_iterator m;
	wxString contents;

	a.SetCount(2);
	a[0] = "0";
	a[1] = "1";
	for (m = a.begin(), contents.Empty(); m != a.end(); contents += *m++){};wxSafeShowMessage("", contents);
	a.SetCount(3);
	for (m = a.begin(), contents.Empty(); m != a.end(); contents += *m++){};wxSafeShowMessage("", contents);
	a[2] = "2";
	for (m = a.begin(), contents.Empty(); m != a.end(); contents += *m++){};wxSafeShowMessage("", contents);

/** QQQ this doesn't compile (msw, vc6, among others because "...error C2247: 'SetCount' not accessible because 'wxArrayPtrVoid' uses 'public' to inherit from 'wxBaseArrayPtrVoid'"
	ArrayOfString a2;
	ArrayOfString::const_iterator m2;
	a2.SetCount(2);
	a2[0] = "0";
	a2[1] = "1";
	for (m2 = a2.begin(), contents.Empty(); m2 != a2.end(); contents += *m2++){};wxSafeShowMessage("", contents);
	a2.SetCount(3);
	a2[2] = "2";
**/
	ArrayOfInt a3;
	ArrayOfInt::const_iterator m3;
	char buf[33];
	a3.SetCount(2);
	a3[0] = 0;
	a3[1] = 1;
	for (m3 = a3.begin(), contents.Empty(); m3 != a3.end(); contents += itoa(*m3++, buf, 10)){};wxSafeShowMessage("", contents);
	a3.SetCount(3);
	for (m3 = a3.begin(), contents.Empty(); m3 != a3.end(); contents += itoa(*m3++, buf, 10)){};wxSafeShowMessage("", contents);
	a3[2] = 2;
	for (m3 = a3.begin(), contents.Empty(); m3 != a3.end(); contents += itoa(*m3++, buf, 10)){};wxSafeShowMessage("", contents);
}

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	theTest();
	return false;
}

 	  	 

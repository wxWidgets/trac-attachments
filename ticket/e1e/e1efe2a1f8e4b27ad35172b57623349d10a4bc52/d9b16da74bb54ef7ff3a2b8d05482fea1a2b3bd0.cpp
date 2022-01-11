#include <stdio.h>
#include <wchar.h>

#define INC_WX 0

#if INC_WX
#include "wx/init.h"
#include "wx/string.h"
#if wxCHECK_VERSION(2, 9, 0)
#include "wx/wxcrt.h"
#endif
#endif

int main(int argc, char** argv)
{
#if INC_WX
	wxInitializer init;
	if (!init.IsOk())
	{
		printf("Init FAIL!\n");
		return 1;
	}
#if wxUSE_UNICODE
	wxPuts(wxT("unicode - yes"));
#else
	wxPuts(wxT("unicode - no"));
#endif
#if wxUSE_UNICODE_UTF8
	wxPuts(wxT("unicode-utf8 - yes"));
#else
	wxPuts(wxT("unicode-utf8 - no"));
#endif

	wxPuts(wxString::Format(wxT("sizeof wxChar: %d"), sizeof(wxChar)));

	wxPuts(wxString::Format(wxT("wxString::Format: %%s %%s: %s %s"), wxT("arg1"), wxT("arg2")));
	wxPuts(wxString::Format(wxT("wxString::Format: %%2$s %%1$s : %2$s %1$s"), wxT("arg1"), wxT("arg2")));
#endif
	printf("printf %%2$s %%1$s : %2$s %1$s\n", "arg1", "arg2");
	wprintf(L"printf %%2$ls %%1$ls : %2$s %1$s\n", L"arg1", L"arg2");

	return 0;
}

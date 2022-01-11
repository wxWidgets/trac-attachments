#include <wx/app.h>

wxString myVsPrintf(const wxString &format, va_list ap) {
    wxString s;
    s.PrintfV(format, ap);
    return s;
}


void myPrintf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    wxString s = myVsPrintf(wxString(fmt, wxConvUTF8), ap);
    va_end(ap);
    puts(s.mb_str(wxConvUTF8));
}


class StringTest: public wxApp {
    bool OnInit(void) {
        if (!wxApp::OnInit()) {
            return false;
        }
        wxString s;
        int i;
        for (i = 0x177e; i < 0x178f; ++i) {
            myPrintf("test: %d: \"%c\"", i, i);
        }
        return false;
    }
};

wxIMPLEMENT_APP(StringTest);


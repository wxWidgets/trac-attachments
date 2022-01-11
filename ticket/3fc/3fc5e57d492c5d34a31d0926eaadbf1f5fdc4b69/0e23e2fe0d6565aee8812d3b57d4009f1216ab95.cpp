
#include <wx/dir.h>
#include <wx/string.h>
#include <wx/filefn.h>
#include <wx/app.h>

#include <iostream>

#ifndef wxUSE_UNICODE
#error not using unicode!
#endif

class TestApp : public wxAppConsole
{
  public:
    virtual int OnRun(void);
};

int TestApp::OnRun(void)
{
  wxDir d(L".");
  wxString output;

  if (d.GetFirst(&output))
    do {
      std::cout << "\"" << output.utf8_str() << "\" (original lenth=" <<
        output.size() << ", wxFileExists()=" <<
        (wxFileExists(output)?"true":"false") << ")\n";
    } while (d.GetNext(&output));
    
  return 0;
}

IMPLEMENT_APP(TestApp)


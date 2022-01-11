
#include <wx/dir.h>
#include <wx/string.h>

#include <iostream>

int main(void)
{
  wxDir d(L".");
  wxString output;

  if (d.GetFirst(&output))
    do {
      std::cout << "\"" << output.utf8_str() << "\" (original lenth=" <<
        output.size() << ")\n";
    } while (d.GetNext(&output));
    
}


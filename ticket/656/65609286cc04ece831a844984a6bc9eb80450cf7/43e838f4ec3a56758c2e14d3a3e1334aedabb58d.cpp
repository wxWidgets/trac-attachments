#include <wx/wx.h>
#include <wx/dir.h>

int main (int argc, char* argv[])
{
  wxDir* pDir = new wxDir(_T("D:\\not_existing"));

  if (pDir->IsOpened())
    printf(_("OK"));
  else
    printf(_("FAILED"));

  return 0;
}

 	  	 

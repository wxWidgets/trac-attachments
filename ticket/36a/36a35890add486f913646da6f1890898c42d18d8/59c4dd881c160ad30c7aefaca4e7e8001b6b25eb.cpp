#include <wx/wx.h>
#include <wx/socket.h>
#include <iostream>

int main () {
  wxInitialize();
  wxSocketClient * sockConn = new wxSocketClient(wxSOCKET_WAITALL);
  wxString url = wxT("lobby.springrts.com");
  wxIPV4address addr;
  addr.Hostname(url);
  addr.Service(8200);
  if(!sockConn->Connect(addr, true)) {
    std::cout << "Connect failed\n";
    return 1;
  }
  wxString test = wxT("testing\n");
  sockConn->Write(test.mb_str(), wxStrlen(test));

  bool error = sockConn->Error();
  if (error)
    std::cout << "Write failed\n";
   else
    std::cout << "Success!\n";

  sockConn->Close();
  delete sockConn;
  wxUninitialize();
  return error;
}
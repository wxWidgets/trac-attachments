#include <wx/wx.h>
#include <string>

struct MyTrackableClass : wxEvtHandler
{
    MyTrackableClass(std::string m) : message(m) {}
    std::string message;
};


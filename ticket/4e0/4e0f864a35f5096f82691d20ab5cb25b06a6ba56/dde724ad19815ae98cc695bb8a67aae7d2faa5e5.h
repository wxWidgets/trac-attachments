#include <wx/wx.h>

struct MyTrackableClass;

struct Foo
{
    wxWeakRef<MyTrackableClass> ref;
    int a;
    void sayHello();
};


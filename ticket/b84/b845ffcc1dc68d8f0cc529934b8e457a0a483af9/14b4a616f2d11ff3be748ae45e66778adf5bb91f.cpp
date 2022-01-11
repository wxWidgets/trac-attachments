/* Build commands
 *    Linux:
 *        g++ b.cpp -Wall -std=c++11 $(wx-config --cxxflags --libs base) # A compile-time error!
 *        g++ b.cpp -Wall -std=c++11 -DUSE_STD_SORT $(wx-config --cxxflags --libs base) # Good. If we use std::sort instead to do the sorting.
 *    Windows:
 *        g++ b.cpp -Wall -std=gnu++11 $(wx-config --cxxflags --libs base) # A compile-time error!
 *        g++ b.cpp -Wall -std=gnu++11 -DUSE_STD_SORT $(wx-config --cxxflags --libs base) # Good.
 */
#include <wx/wx.h>
#ifdef USE_STD_SORT
    #include <algorithm>
#endif

struct SApp : public wxApp
{
    int OnRun() {
        // Populate some items into the array.
        const wxChar * rgsz[] = {
            wxT("Cherry"), wxT("Eggplant"), wxT("banana"), wxT("Apple"), wxT("durian")
        };
        wxArrayString arr(sizeof(rgsz)/sizeof(*rgsz), rgsz);
        // Try to sort the array with method Sort or function template std::sort.
        size_t n = 0u;
#ifndef USE_STD_SORT
        arr.Sort([&n](const wxString & a, const wxString & b)->int{ // The lambda here will incur a compile-time error both on Linux and Windows.
            ++n;
            return a.CmpNoCase(b);
        });
#else
        std::sort(arr.begin(), arr.end(), [&n](const wxString & a, const wxString & b)->bool{ // This works as expected.
            ++n;
            return a.CmpNoCase(b) < 0;
        });
#endif
        ::wxPrintf(wxT("Having done the comparison for %u times.\n"), n);
        // Display the result on terminal.
        for (const wxString & s : arr) wxPrintf(wxT("%s\n"), s.c_str());

        return 0;
    }
};
DECLARE_APP(SApp)
IMPLEMENT_APP(SApp)

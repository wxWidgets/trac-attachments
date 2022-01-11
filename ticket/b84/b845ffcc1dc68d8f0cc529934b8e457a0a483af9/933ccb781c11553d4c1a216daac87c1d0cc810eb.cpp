/* Build commands
 *    Linux:
 *        g++ a.cpp -Wall -std=c++11 $(wx-config --cxxflags --libs base) # This will cause a compile-time error.
 *        g++ a.cpp -Wall -std=c++11 -DUSE_STD_SORT $(wx-config --cxxflags --libs base) # Good. This time we ask std::sort instead to use lambda to do the sorting.
 *    Windows:
 *        g++ a.cpp -Wall -std=gnu++11 $(wx-config --cxxflags --libs base) # Good.
 *        g++ a.cpp -Wall -std=gnu++11 -DUSE_STD_SORT $(wx-config --cxxflags --libs base) # Good.
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
#ifndef USE_STD_SORT
        arr.Sort([](const wxString & a, const wxString & b)->int{ // The lambda here will incur a compile-time error on Linux.
            return a.CmpNoCase(b);
        });
#else
        std::sort(arr.begin(), arr.end(), [](const wxString & a, const wxString & b)->bool{ // This works as expected.
            return a.CmpNoCase(b) < 0;
        });
#endif
        // Display the result on terminal.
        for (const wxString & s : arr) wxPrintf(wxT("%s\n"), s.c_str());

        return 0;
    }
};
DECLARE_APP(SApp)
IMPLEMENT_APP(SApp)

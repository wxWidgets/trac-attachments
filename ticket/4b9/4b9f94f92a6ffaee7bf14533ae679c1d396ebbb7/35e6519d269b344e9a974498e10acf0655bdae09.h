#ifndef _WX_DISPLAY_H_
#define _WX_DISPLAY_H_

#ifdef __DARWIN__
    #include <Carbon/Carbon.h>
#else
    #include <Displays.h>
    #include <Quickdraw.h>
#endif

class wxRect;
class wxString;
class wxPoint;

class wxDisplay
{

public:
    // return the number of available displays, valid parameters to
    // wxDisplay ctor are from 0 up to this number
    static size_t GetCount();

    // find the display where the given point lies, return (size_t)-1 if
    // it doesn't belong to any display
    static int GetFromPoint(const wxPoint &p);

    // initialize the object containing all information about the given
    // display
    wxDisplay(size_t index);

    // accessors

    wxRect GetGeometry() const;
    int GetDepth() const;
    int IsColour() const { return GetDepth() != 1; }

    // some people never learn to spell ;-)
    int IsColor() const { return IsColour(); }

    // name may be empty
    wxString GetName() const;

    // no IsPrimary(): let display 0 always be the primary display

private:
    GDHandle m_hndl;
};



#endif /* _WX_DISPLAY_H_ */

 	  	 

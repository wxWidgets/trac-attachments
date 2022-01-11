/* Mac implementation of wxDisplay class */
/* Brian Victor: June 21, 2002 */

/*for iterating the displays use

DMGetFirstScreenDevice  and DMGetNextScreenDevice and use the returned
GDHandle for getting the GDevice's gdRect
*/

#include "wx/display.h"
#include "wx/gdicmn.h"
#include "wx/string.h"

size_t wxDisplay::GetCount()
{
    GDHandle hndl;
    size_t num = 0;
    hndl = DMGetFirstScreenDevice(true);
    while(hndl)
    {
	num++;
	hndl = DMGetNextScreenDevice(hndl, true);
    }
    return num;
}

int wxDisplay::GetFromPoint(const wxPoint &p)
{
    GDHandle hndl;
    size_t num = 0;
    hndl = DMGetFirstScreenDevice(true);
    while(hndl)
    {
        Rect screenrect = (*hndl)->gdRect;
        if (p.x >= screenrect.left &&
            p.x <= screenrect.right &&
            p.y >= screenrect.top &&
            p.y <= screenrect.bottom)
        {
            return num;
        }
        num++;
	hndl = DMGetNextScreenDevice(hndl, true);
    }
    return -1;
}

wxDisplay::wxDisplay(size_t index)
{
    GDHandle hndl;
    hndl = DMGetFirstScreenDevice(true);
    m_hndl = NULL;
    while(hndl)
    {
	if (index == 0)
	{
	    m_hndl = hndl;
	}
	index--;
	hndl = DMGetNextScreenDevice(hndl, true);
    }
}

wxRect wxDisplay::GetGeometry() const
{
    if (!m_hndl) return wxRect(0, 0, 0, 0);
    Rect screenrect = (*m_hndl)->gdRect;
    return wxRect( screenrect.left, screenrect.top, 
                   screenrect.right - screenrect.left, screenrect.bottom - screenrect.top);
}

int wxDisplay::GetDepth() const
{
  if (!m_hndl) return 0;

  // This cryptic looking code is based on Apple's sample code:
  // http://developer.apple.com/samplecode/Sample_Code/Graphics_2D/GDevVideo/Gen.cp.htm
  return ((*(*m_hndl)->gdPMap)->pixelSize) & 0x0000FFFF;
}

wxString wxDisplay::GetName() const
{
    // Macs don't name their displays...
    return "";
}

 	  	 

#ifndef MYPANEL_H
#define MYPANEL_H

#include <wx/panel.h>

#include "textlayout.h"

enum ShapeType { RECT, ELLIPSE, DIAMOND, TRIANGLE, ROUNDED_RECT, PARALLELOGRAM };

class myPanel : public wxPanel
{
public:
    myPanel (wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, 
                long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    ~myPanel();

    void Paint (wxPaintEvent& evt);
    void SetShapeType (ShapeType type);
	void AlignUpdate (int alignFlags);
    void GeometryUpdate (int width, int height, int roundedRectRadius, int parallelogramSlope);
    void MarginsUpdate (int lmargin, int rmargin, int tmargin, int bmargin, int pinch);
    void TextUpdate (const wxString& text);
    void SetDebugOptions (int debugFlags);
    
private:
    wxSize m_ShapeSize;
    int m_RoundedRectRadius;
    int m_ParallelogramSlope;
    wxString m_ShapeText;
    int m_DebugFlags;
    
    ShapeType m_ShapeType;
    wxTextLayout* m_pTextLayout;

    wxClientDC* m_pDC;
};

#endif // MYPANEL_H

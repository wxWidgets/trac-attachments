#include "myPanel.h"

#include <wx/dcclient.h>
#include <wx/log.h>


myPanel::myPanel (wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, 
                long style, const wxString &name) : wxPanel (parent, id, pos, size, style, name)
{
    m_pDC = new wxClientDC (this);

    m_ShapeText = "";
    m_RoundedRectRadius = 50;
    m_ParallelogramSlope = 50;
    m_ShapeSize = wxSize (100, 100);
    m_ShapeType = RECT;
    m_DebugFlags = wxTEXTLAYOUT_DEBUG_OFF;
}

myPanel::~myPanel()
{
    delete m_pDC;
}

void myPanel::Paint (wxPaintEvent& evt)
{
    wxPaintDC dc (this);
	
	wxPoint diamond[] = {   wxPoint (m_ShapeSize.GetWidth() / 2, 0), 
							wxPoint (m_ShapeSize.GetWidth(), m_ShapeSize.GetHeight() / 2), 
							wxPoint (m_ShapeSize.GetWidth() / 2, m_ShapeSize.GetHeight()), 
							wxPoint (0, m_ShapeSize.GetHeight() / 2) 
                            };
                            
    wxPoint parallelogram[] = { wxPoint (m_ParallelogramSlope, 0),
                                wxPoint (m_ShapeSize.GetWidth() + m_ParallelogramSlope, 0),
                                wxPoint (m_ShapeSize.GetWidth(), m_ShapeSize.GetHeight()),
                                wxPoint (0, m_ShapeSize.GetHeight()) 
                                };
    
    int width, height;
    GetClientSize (&width, &height);
    
    int x = width / 2 - m_ShapeSize.GetWidth() / 2;
    int y = height / 2 - m_ShapeSize.GetHeight() / 2;
    
    switch (m_ShapeType)
    {
        case ELLIPSE:
            dc.DrawEllipse (wxRect (wxPoint(x, y), m_ShapeSize));
            break;
            
        case DIAMOND:
            dc.DrawPolygon (4, diamond, x, y);
            break;
            
        case ROUNDED_RECT:
            dc.DrawRoundedRectangle (wxRect (wxPoint(x, y), m_ShapeSize), m_RoundedRectRadius);
            break;
            
        case PARALLELOGRAM:
            dc.DrawPolygon (4, parallelogram, x, y);
            break;
        
        case RECT:
        default:
            dc.DrawRectangle (wxRect (wxPoint(x, y), m_ShapeSize));
            break;
    }
  
    if (m_pTextLayout)
        m_pTextLayout->Render(&dc, wxPoint (x, y), m_DebugFlags);
}

void myPanel::AlignUpdate (int alignFlags)
{
	m_pTextLayout->SetFlags (alignFlags);

    this->Refresh();
}

void myPanel::GeometryUpdate (int width, int height, 
								int roundedRectRadius, int parallelogramSlope)
{
    m_ShapeSize.Set(width, height);
    m_RoundedRectRadius = roundedRectRadius;
    m_ParallelogramSlope = parallelogramSlope;

    if (m_ShapeType == ROUNDED_RECT)
        ((wxRoundedRectTextLayout*)m_pTextLayout)->SetGeometry (m_ShapeSize, m_RoundedRectRadius);
    else if (m_ShapeType == PARALLELOGRAM)
        ((wxParallelogramTextLayout*)m_pTextLayout)->SetGeometry (m_ShapeSize, m_ParallelogramSlope);
    else
        m_pTextLayout->SetGeometry (m_ShapeSize);

    this->Refresh();
}

void myPanel::MarginsUpdate(int lmargin, int rmargin, int tmargin, int bmargin, int pinch)
{
    m_pTextLayout->SetMargins(lmargin, rmargin, tmargin, bmargin, pinch);

    this->Refresh();
}

void myPanel::SetShapeType(ShapeType type)
{
    m_ShapeType = type;

    if (m_pTextLayout)
        delete m_pTextLayout;

    switch (m_ShapeType)
    {
        case RECT:
            m_pTextLayout = new wxTextLayout (m_pDC, m_ShapeText, m_ShapeSize);
            break;

        case ELLIPSE:
            m_pTextLayout = new wxEllipseTextLayout (m_pDC, m_ShapeText, m_ShapeSize);
            break;
            
        case DIAMOND:
            m_pTextLayout = new wxDiamondTextLayout (m_pDC, m_ShapeText, m_ShapeSize);
            break;
            
        case ROUNDED_RECT:
            m_pTextLayout = new wxRoundedRectTextLayout (m_pDC, m_ShapeText, m_ShapeSize);
            break;
            
        case PARALLELOGRAM:
            m_pTextLayout = new wxParallelogramTextLayout (m_pDC, m_ShapeText, m_ShapeSize);
            break;

        default:
            m_pTextLayout = new wxTextLayout (m_pDC, m_ShapeText, m_ShapeSize);
            break;
    }
}

void myPanel::TextUpdate(const wxString& text)
{
    m_ShapeText = text;
    m_pTextLayout->SetText (m_ShapeText);
    
    this->Refresh();
}

void myPanel::SetDebugOptions(int debugFlags)
{
    m_DebugFlags = debugFlags;
    
    this->Refresh();
}

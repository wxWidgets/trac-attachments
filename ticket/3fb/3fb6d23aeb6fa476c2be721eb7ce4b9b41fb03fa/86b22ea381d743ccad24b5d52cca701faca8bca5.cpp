#include "textlayout.h"

#include <cmath>

#include <wx/log.h>
#include <wx/tokenzr.h>

#define MY_DEBUG

// ----------------------------------------------------------------------------
// wxRectTextShape: Class to provide geometry for a rectangular shape
// ----------------------------------------------------------------------------

class wxRectTextShape : public wxTextShape
{ 
public: 
    wxRectTextShape(const wxSize& size) { m_Size = size; }

    virtual int GetHeight () const { return m_Size.GetHeight(); } 
    virtual void GetFitAtY (int y1, int y2, int& left, int& width) const { left = 0, width = m_Size.GetWidth(); } 
    virtual void SetGeometry (const wxSize& size) { m_Size = size; }

protected:
    wxSize m_Size;
}; 

// ----------------------------------------------------------------------------
// wxEllipseTextShape: Class to provide geometry for an elliptical shape
// ----------------------------------------------------------------------------

class wxEllipseTextShape : public wxRectTextShape
{ 
public: 
    wxEllipseTextShape(const wxSize& size) : wxRectTextShape (size) { }

    virtual void GetFitAtY (int y1, int y2, int& left, int& width) const 
    { 
        double a = m_Size.GetWidth() / 2.0;
        double b = m_Size.GetHeight() / 2.0;
        
        double yy1 = fabs (y1 - b);
        double yy2 = fabs (y2 - b);

        if (yy1 <= b && yy2 <= b && b > 0) // y is inside ellipse which isn't flat (avoid div by 0)
        {
            // calculate widths using formula for an ellipse in reverse
            int w1 = round (std::sqrt((a * a) * (1 - ((yy1 * yy1) / (b * b)))) * 2); 
            int w2 = round (std::sqrt((a * a) * (1 - ((yy2 * yy2) / (b * b)))) * 2);
            
            width = w1 < w2 ? w1 : w2;
            left = (m_Size.GetWidth() / 2) - (width / 2);
        }
        else
        {
            left = 0;
            width = 0;
        }
    } 
};

// ----------------------------------------------------------------------------
// wxDiamondTextShape: Class to provide geometry for a diamond shape
// ----------------------------------------------------------------------------

class wxDiamondTextShape : public wxRectTextShape
{ 
public: 
    wxDiamondTextShape(const wxSize& size) : wxRectTextShape (size) { }

    virtual int GetHeight () const { return m_Size.GetHeight(); } 
    virtual void GetFitAtY (int y1, int y2, int& left, int& width) const 
    { 
        double a = m_Size.GetWidth();
        double b = m_Size.GetHeight() / 2.0;
        
        double yy1 = b - fabs (y1 - b); // shift origin to centre for both y1 
        double yy2 = b - fabs (y2 - b); // and y2

        int w1 = (yy1 / b) * a;
        int w2 = (yy2 / b) * a;

        width = w1 < w2 ? w1 : w2;
        left = (a / 2) - (width / 2);
    } 
};

// ----------------------------------------------------------------------------
// wxRoundedRectTextShape: Class to provide geometry for a rounded rectangle
// ----------------------------------------------------------------------------

class wxRoundedRectTextShape : public wxRectTextShape
{ 
public: 
    wxRoundedRectTextShape (const wxSize& size, int radius) : wxRectTextShape (size), m_Radius (radius) {  }

    virtual void GetFitAtY (int y1, int y2, int& left, int& width) const 
    { 
        double w1 = m_Size.GetWidth();
        if (y1 < m_Radius)
                w1 -= (m_Radius - std::sqrt ((m_Radius * m_Radius) - ((m_Radius - y1) * (m_Radius - y1)))) * 2;
        else if (y1 > m_Size.GetHeight() - m_Radius)
                w1 -= (m_Radius - (std::sqrt ((m_Radius * m_Radius) - (std::pow((y2 - (m_Size.GetHeight() - m_Radius)), 2))))) * 2;
                
        double w2 = m_Size.GetWidth();
        if (y2 < m_Radius)
                w2 -= (m_Radius - std::sqrt ((m_Radius * m_Radius) - ((m_Radius - y2) * (m_Radius - y2)))) * 2;
        else if (y2 > m_Size.GetHeight() - m_Radius)
                w2 -= (m_Radius - std::sqrt ((m_Radius * m_Radius) - (std::pow((y2 - (m_Size.GetHeight() - m_Radius)), 2)))) * 2;

        width = w1 < w2 ? w1 : w2;
        left = (m_Size.GetWidth() / 2) - (width / 2);
    } 

    virtual void SetGeometry (const wxSize& size, int radius) 
    { 
        m_Size = size;
        m_Radius = radius;
    }
        
private:
    int m_Radius;
};

// ----------------------------------------------------------------------------
// wxParallelogramTextShape: Class to provide geometry for a parallelogram
// ----------------------------------------------------------------------------

class wxParallelogramTextShape : public wxRectTextShape
{ 
public: 
    wxParallelogramTextShape (const wxSize& size, int slope) : wxRectTextShape (size), m_Slope (slope) { }
    
    virtual void GetFitAtY (int y1, int y2, int& left, int& width) const 
    { 
        // protect against divide by zero
        if (m_Size.GetHeight() <= 0)
        {
            width = left = 0;
            return;
        }
        double l1 = ((double)(m_Size.GetHeight() - y1) / m_Size.GetHeight()) * m_Slope;
        double l2 = ((double)(m_Size.GetHeight() - y2) / m_Size.GetHeight()) * m_Slope;
        
        width = m_Size.GetWidth() - fabs (l1 - l2);
        left = l1 > l2 ? l1 : l2;
    } 

    virtual void SetGeometry (const wxSize& size, int slope) 
        { 
            m_Size = size;
            m_Slope = slope;
        }
        
private:
    int m_Slope;
};

// ----------------------------------------------------------------------------
// wxTextLayoutEngine: Engine to layout text within a defined shape 
// ----------------------------------------------------------------------------

wxTextLayoutEngine::wxTextLayoutEngine(wxTextLayout* layout, const wxString& text, wxTextShape* shape)
{
    m_pLayout = layout; // the layout is used for the callback to get the shape geometry
    m_pShape = shape;

    m_TokenWidthsValid = false;
    m_LineRectsValid = false;
    
    Tokenize (text); // text must be tokenized before margins can be set

    SetMargins (0, 0, 0, 0, 0);
    m_Flags = wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT;
}

wxTextLayoutEngine::~wxTextLayoutEngine()
{
    delete m_pShape;
}

void wxTextLayoutEngine::SetMargins(int left, int right, int top, int bottom, int pinch)
{
    wxLogMessage ("SetMargins");

    m_LeftMargin = left;
    m_RightMargin = right;
    m_TopMargin = top;
    m_BottomMargin = bottom;
    m_LineSpacing = pinch;
    InvalidateRects ();
}

void wxTextLayoutEngine::Tokenize (const wxString& text)
{
    wxLogMessage ("Tokenize");

    // at the moment Tokenize() isn't lazy, this is so we don't have to store both 
    // the string *and* the tokens, instead we immediately tokenize and forget the string
    m_Tokens.clear();

    wxStringTokenizer tokenizer (text, " \t\r\n");
        
    while (tokenizer.HasMoreTokens())
        m_Tokens.push_back (tokenizer.GetNextToken());
    
    // set to false so lazy updating of token widths  and lines will occur
    m_TokenWidthsValid = false; 
    m_LinesValid = false;
}

// TODO: Handle carriage returns, tabs, double spaces

void wxTextLayoutEngine::CalcLines ()
{
    wxLogMessage ("CalcLines");

    if (m_LineRects.size() == 0)
        return;

    wxVector<wxRect> tmpRects;
    
    if ((m_Flags & 0xC00) == wxALIGN_TOP)
        DoCalcLines (&m_LineRects);
    
    else if ((m_Flags & 0xC00) == wxALIGN_CENTER_VERTICAL)
    {
        // To allow for shapes which do not have constant widths and iterative approach is taken.
        // firstly just the middle line rect is added to tmpRects, if the text fits in it then stop iterating (break).
        // If the text does not fit in just the middle line rect then add the line rect above it and try again. If the
        // text still doesn't fit add the line below the middle line rect (now there are 3 lines) and try again. Continue
        // adding lines alternatively above and below until all line rects have been filled (overflow) or the text fits.
        int start = (int)(m_LineRects.size() / 2);
        int end = start;
        do
        {
            tmpRects.clear();
            m_LinesText.clear ();
            
            for (int i = start; i <= end; i++)
                    tmpRects.push_back(m_LineRects.at(i));
            
            if (!DoCalcLines(&tmpRects))
                    break;                          // all lines of text fit completely into the temp rects
                    
            if (tmpRects.size() & 1)
                    start--;                        // odd number of lines, start one line earlier
            else
                    end++;                          // even number of lines, start one line later

        } while (tmpRects.size() < m_LineRects.size());

        // If in the end there is an odd number of lines then we need to offset it by half a line
        // this is a bit of a fudge because in shapes without vertical sides the text will no longer
        // obey the margins. Therefore only apply it to small numbers of lines where it is particularly obvious
        if (m_TextRects.size() <= 3 && m_TextRects.size() % 2 && !(m_LineRects.size() % 2))
        {
            int offset = -m_LineHeight / 2;
            for (wxVector<wxRect>::iterator r = m_TextRects.begin(); r != m_TextRects.end(); r++)
                    r->Offset(wxPoint(0, offset));
        }
    }
    
    else // wxALIGN_BOTTOM
    {
        // This uses the same approach as wxALIGN_CENTER_VERTICAL except the first rect tested is the bottom
        // line rect and further rects are added above it until there are no more rects (overflow) or the text fits.
        int start = (int)(m_LineRects.size() - 1);
        int end = start;
        do
        {
            tmpRects.clear();
            m_LinesText.clear ();
            
            for (int i = start; i <= end; i++)
                tmpRects.push_back(m_LineRects.at(i));
            
            if (!DoCalcLines(&tmpRects))
                break;                          // all lines of text fit completely into the temp rects
            else
                start--;                        // start one line earlier

        } while (tmpRects.size() < m_LineRects.size());
    }
    
    m_LinesValid = true;
}

bool wxTextLayoutEngine::DoCalcLines(wxVector<wxRect>* calcRects)
{
    int lineWidth = calcRects->at(0).GetWidth();
    wxRect textRect = calcRects->at(0);
    size_t lineNo = 0;
    int pos = 0;
    wxString line = "";

    m_LinesText.clear ();
    m_TextRects.clear ();
    m_Overflow = false;

    for (size_t tokenNo = 0; tokenNo < m_Tokens.size();)
    {
        pos += m_TokenWidths.at(tokenNo);
        
        // add tokens to the same line whilst there is still space. when there is
        // no more space then push the line and its bounding rect
        if (pos < lineWidth) 
        {
            line.append (m_Tokens.at(tokenNo++) + " ");
            pos += m_SpaceWidth;
        }
        else
        {
            // shrink the rectangle to the size of the text (removing the last token and space)
            textRect.SetWidth (pos - m_TokenWidths.at(tokenNo) - m_SpaceWidth);
            DoPushLine (lineNo, &line, &textRect, &calcRects->at (lineNo));
            
            // space for more text in the shape?
            if (++lineNo >= calcRects->size())
            {
                m_Overflow = true;
                break;
            }

            line = "";
            pos = 0;
            lineWidth = calcRects->at (lineNo).GetWidth();
            textRect = calcRects->at (lineNo);
        }
    }
    
    // push the final line if there is one and there is enough space for it
    if (pos && lineNo <  calcRects->size())
    {
        textRect.SetWidth (pos);
        DoPushLine (lineNo, &line, &textRect, &calcRects->at (lineNo));
    }
    
    return m_Overflow;
}

void wxTextLayoutEngine::DoPushLine(int lineNo, const wxString* lineText, wxRect* textRect, const wxRect* lineRect)
{
    // helper function to save a line of text and its bounding rect
    
    // offset final text rectangle as required for horizontal alignment (no offset needed for left alignment)
    if ((m_Flags & 0x300) == wxALIGN_RIGHT)
        textRect->Offset(lineRect->GetWidth() - textRect->GetWidth(), 0);
    else if ((m_Flags & 0x300) == wxALIGN_CENTER_HORIZONTAL)
        textRect->Offset ((lineRect->GetWidth() - textRect->GetWidth()) / 2, 0);
    
    m_LinesText.push_back (*lineText);   // save the text for this line
    m_TextRects.push_back (*textRect);   // and the rectangle it fits in
}

void wxTextLayoutEngine::CalcLineRects()
{
    wxLogMessage ("CalcLineRects");

    m_LineRects.clear();

    // no tokens so do nothing
    if (m_Tokens.size() == 0)
        return;
    
    // get the height of one line
    m_LineHeight = m_pLayout->GetTokenExtent(m_Tokens.at(0)).GetHeight();

    wxASSERT (m_LineHeight + m_LineSpacing > 0); // can't handle zero height lines (div by zero)

    int offset = 0;
    int textAreaHeight = (m_pShape->GetHeight() - m_TopMargin - m_BottomMargin); // height of area where text may be drawn
    int noLines =  textAreaHeight / (m_LineHeight + m_LineSpacing);
    int textHeight = noLines * (m_LineHeight + m_LineSpacing) - m_LineSpacing; // actual height needed by lines (last line is not spaced)
    
    if ((m_Flags & 0xC00) == wxALIGN_TOP)
        offset = m_TopMargin;
    else if ((m_Flags & 0xC00) == wxALIGN_CENTER_VERTICAL)
        offset = ((textAreaHeight - textHeight) / 2.0) + m_TopMargin;
    else if ((m_Flags & 0xC00) == wxALIGN_BOTTOM)
        offset = (m_pShape->GetHeight() - m_BottomMargin) - textHeight;

    int left, width, y = offset;
    
    for (int i = 0; i < noLines; i++)
    {
        m_pShape->GetFitAtY(y, y + m_LineHeight, left, width);
        // only store rects for text lines that are greater than a minimum
        // width to avoid ridiculously small rects
        if (width >= MIN_LAYOUT_RECT_WIDTH)
                m_LineRects.push_back( wxRect (left + m_LeftMargin, 
                                y, 
                                width - (m_LeftMargin + m_RightMargin), 
                                m_LineHeight));
        y += m_LineHeight + m_LineSpacing;
    }
    
    m_LineRectsValid = true;
}

void wxTextLayoutEngine::CalcTokenWidths()
{
    wxLogMessage ("CalcTokenWidths");
    
    if (m_Tokens.size() == 0) // tokens will always be valid or zero
        return;
        
    m_TokenWidths.clear();
    
    for (wxVector<wxString>::const_iterator i = m_Tokens.begin(); i != m_Tokens.end(); i++)
        m_TokenWidths.push_back(m_pLayout->GetTokenExtent(*i).GetX());
    
    m_SpaceWidth = m_pLayout->GetTokenExtent(" ").GetX();
    
    m_TokenWidthsValid = true;
}

void wxTextLayoutEngine::UpdateLayout()
{
    wxLogMessage ("UpdateLayout");
    
    if (!m_LineRectsValid)
        CalcLineRects ();
        
    if (!m_TokenWidthsValid)
        CalcTokenWidths ();
        
    // must have line rects and token widths before we split the lines
    if (!m_LinesValid)
        CalcLines ();
}

wxVector<wxRect>* wxTextLayoutEngine::GetLineRects()
{
    wxLogMessage ("GetLineRects");
    
    // only need rects, token widths and lines are not important. UpdateLayout
    // is not suitable here because it will also calculate lines and token widths
    // if they are not valid
    if (!m_LineRectsValid) 
        CalcLineRects (); 
    
    return &m_LineRects;
}

wxVector<wxString>* wxTextLayoutEngine::GetLines()
{
    wxLogMessage ("GetLines");
    
    // if the lines are required it is necessary to make sure that 
    // the text is valid, the text extents are valid and the rects are valid
    // and that the lines have been split, so UpdateLayout is called
    UpdateLayout ();
    return &m_LinesText;
}

// ----------------------------------------------------------------------------
// wxTextLayout: Default implementation to layout text in a rectangle
// ----------------------------------------------------------------------------

wxTextLayout::wxTextLayout (wxDC* dc, const wxString& text, const wxRect& rect)
{
    m_pDC = dc;
    m_pEngine = new wxTextLayoutEngine (this, text, new wxRectTextShape (wxSize(rect.GetWidth(), rect.GetHeight())));
}

wxTextLayout::~wxTextLayout()
{
    delete m_pEngine;
}

void wxTextLayout::Render (wxDC* dc, const wxPoint& pos, int options)
{
    wxLogMessage ("Render");

    // preferred way is to call GetLines() first because then the line rects
    // will automatically be updated
    wxVector<wxString>* lines = m_pEngine->GetLines();
    wxVector<wxRect>* rects = m_pEngine->GetLineRects();
    wxVector<wxRect>* textrects = m_pEngine->GetTextRects();
    
    if (lines->size() == 0)
        return;
    
    int count = 0;
    
    if (!(options & wxTEXTLAYOUT_DEBUG_HIDE_TEXT))
    {
        for (wxVector<wxString>::const_iterator i = lines->begin(); i < lines->end() - 1; i++)
            dc->DrawText(*i, pos + textrects->at(count++).GetTopLeft());
            
        if (m_pEngine->GetOverflow())
        {
            wxString last = lines->back();
            if (options & wxTEXTLAYOUT_CUSTOM_ELLIPSIS)
            {
                dc->DrawText (last.RemoveLast(3), pos + textrects->at(count).GetTopLeft());
                DrawEllipsis (dc, pos + textrects->at(count).GetBottomRight());
            }
            else
                dc->DrawText (last.RemoveLast(3) + "...", pos + textrects->at(count).GetTopLeft());
        }
        else
            dc->DrawText (lines->back(), pos + textrects->at(count).GetTopLeft());
    }
    
    if (options & wxTEXTLAYOUT_DEBUG_SIZE_RECTS)
    {
        // draw the available space rects
        dc->SetPen(wxColour(150, 150, 150));
        dc->SetBrush (*wxTRANSPARENT_BRUSH);
        for (wxVector<wxRect>::const_iterator i = rects->begin(); i != rects->end(); i++)
            dc->DrawRectangle(wxRect(pos + i->GetPosition(), i->GetSize()));
    }
        
    if (options & wxTEXTLAYOUT_DEBUG_TEXT_RECTS)
    {
        // draw the text boundary rects
        dc->SetPen(wxColour(150, 150, 255));
        dc->SetBrush (*wxTRANSPARENT_BRUSH);
        for (wxVector<wxRect>::const_iterator i = textrects->begin(); i != textrects->end(); i++)
            dc->DrawRectangle(wxRect(pos + i->GetPosition(), i->GetSize()));
    }
}

wxSize wxTextLayout::GetTokenExtent(const wxString& token)
{
    return m_pDC->GetTextExtent(token);
}

void wxTextLayout::SetGeometry(wxSize size)
{
    wxLogMessage ("Set Geometry");

    // The layout class interacts directly with the shape here because 
    // the layout engine is agnostic towards what shape is being drawn
    // The signature for SetGeometry is specific to the shape type because
    // whilst rects and ellipses may only have a size parameter for their
    // geometry, parallelgrams have shape and slope. This also allows for 
    // more flexibility in user defined shapes
    ((wxRectTextShape*)m_pEngine->GetShape())->SetGeometry (size);
    m_pEngine->InvalidateRects();
}

void wxTextLayout::DrawEllipsis(wxDC* dc, const wxPoint& pos)
{
    wxPoint points[] = { wxPoint(0,0), wxPoint(-10, 0), wxPoint(0, -10) };
    dc->SetBrush (*wxRED);
    dc->SetPen (*wxTRANSPARENT_PEN);
    dc->DrawPolygon (3, points, pos.x, pos.y);
}

// ----------------------------------------------------------------------------
// wxEllipseTextLayout: Implementation to layout text in an ellipse
// ----------------------------------------------------------------------------

wxEllipseTextLayout::wxEllipseTextLayout (wxDC* dc, const wxString& text, const wxRect& rect)
{
    m_pDC = dc;
    m_pEngine = new wxTextLayoutEngine (this, text, new wxEllipseTextShape (wxSize(rect.GetWidth(), rect.GetHeight())));
}

// ----------------------------------------------------------------------------
// wxDiamondTextLayout: Implementation to layout text in a diamond
// ----------------------------------------------------------------------------

wxDiamondTextLayout::wxDiamondTextLayout (wxDC* dc, const wxString& text, const wxRect& rect)
{
    m_pDC = dc;
    m_pEngine = new wxTextLayoutEngine (this, text, new wxDiamondTextShape (wxSize(rect.GetWidth(), rect.GetHeight())));
}


// ----------------------------------------------------------------------------
// wxRoundedRectTextLayout: Implementation to layout text in a rounded rect
// ----------------------------------------------------------------------------

wxRoundedRectTextLayout::wxRoundedRectTextLayout (wxDC* dc, const wxString& text, const wxRect& rect, int radius)
{
    m_pDC = dc;
    m_pEngine = new wxTextLayoutEngine (this, text, 
                                                new wxRoundedRectTextShape (wxSize(rect.GetWidth(), rect.GetHeight()), radius));
}

void wxRoundedRectTextLayout::SetGeometry(wxSize size, int radius)
{
    wxLogMessage ("Set Geometry");

    ((wxRoundedRectTextShape*)m_pEngine->GetShape())->SetGeometry (size, radius);
    m_pEngine->InvalidateRects();
}

// ----------------------------------------------------------------------------
// wxParallelogramTextLayout: Implementation to layout text in a rounded rect
// ----------------------------------------------------------------------------

wxParallelogramTextLayout::wxParallelogramTextLayout (wxDC* dc, const wxString& text, const wxRect& rect, int slope)
{
    m_pDC = dc;
    m_pEngine = new wxTextLayoutEngine (this, text, 
                                                new wxParallelogramTextShape (wxSize(rect.GetWidth(), rect.GetHeight()), slope));
}

void wxParallelogramTextLayout::SetGeometry (wxSize size, int slope)
{
    wxLogMessage ("Set Geometry");

    ((wxParallelogramTextShape*)m_pEngine->GetShape())->SetGeometry (size, slope);
    m_pEngine->InvalidateRects();
}

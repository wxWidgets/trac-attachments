#ifndef WXTEXTLAYOUT_H
#define WXTEXTLAYOUT_H

#include <wx/dc.h>
#include <wx/string.h>
#include <wx/vector.h>

#define MIN_LAYOUT_RECT_WIDTH 30

enum wxTextLayoutDebugFlags
{
    wxTEXTLAYOUT_DEBUG_OFF = 0,
    wxTEXTLAYOUT_DEBUG_HIDE_TEXT = 0x80,
    wxTEXTLAYOUT_DEBUG_SIZE_RECTS = 0x40,
    wxTEXTLAYOUT_DEBUG_TEXT_RECTS = 0x20,
    wxTEXTLAYOUT_CUSTOM_ELLIPSIS = 0x01
};

class wxTextLayout;

// ----------------------------------------------------------------------------
// wxTextShape: Abstract base class for shape geometry
// ----------------------------------------------------------------------------

class wxTextShape 
{ 
public: 
    virtual int GetHeight () const = 0;
    virtual void GetFitAtY (int y1, int y2, int& left, int& width) const = 0;
    virtual ~wxTextShape () {}

    // no set size method here as this will depend on what is 
    // needed to define the shape geometry and is optional
}; 

// ----------------------------------------------------------------------------
// wxTextLayoutEngine: Class to layout text in the shape of a wxTextShape
// ----------------------------------------------------------------------------

class wxTextLayoutEngine
{
public:
    // for now the layout class provides a call back for GetTextExtents depending on what it is laying out on
    wxTextLayoutEngine (wxTextLayout* layout, const wxString& text, wxTextShape* shape); 
    virtual ~wxTextLayoutEngine ();
    
    virtual wxVector<wxString>* GetLines ();
    virtual wxVector<wxRect>* GetLineRects ();
    virtual bool GetOverflow () { return m_Overflow; }
    virtual wxVector<wxRect>* GetTextRects () { return &m_TextRects; } // only needed for debugging
	virtual wxTextShape* GetShape () { return m_pShape; }
	virtual void InvalidateRects () { m_LinesValid = false; m_LineRectsValid = false; }
    virtual void UpdateLayout ();
	virtual void SetFlags (int flags) { m_Flags = flags; InvalidateRects(); }
    virtual void SetMargins (int left, int right, int top, int bottom, int pinch);
    virtual void SetText (const wxString& text) { Tokenize (text); }

protected:
    virtual void CalcLines ();
    virtual bool DoCalcLines (wxVector<wxRect>* calcRects);
    virtual void DoPushLine (int lineNo, const wxString* lineText, wxRect* textRect, const wxRect* lineRect);
    virtual void CalcLineRects ();
    virtual void CalcTokenWidths ();
    virtual void Tokenize (const wxString& text);

private:
    wxVector<wxRect> m_LineRects;   // the rectangles that define the available space for each line
    wxVector<wxString> m_LinesText; // the lines of text
    wxVector<wxRect> m_TextRects;   // the actual width of the text in each line
    wxVector<wxString> m_Tokens;    
    wxVector<int> m_TokenWidths;

    int m_SpaceWidth;
    int m_LineHeight;

    wxTextShape* m_pShape;

    bool m_LinesValid;
    bool m_LineRectsValid;
    bool m_Overflow;
    bool m_TokenWidthsValid;

    int m_Flags; // flags to control alignment (wxALIGN_LEFT, wxALIGN_RIGHT, wxALIGN_TOP, wxALIGN_BOTTOM etc.)
    
    int m_TopMargin;
    int m_BottomMargin;
    int m_LeftMargin;
    int m_RightMargin;
    int m_LineSpacing; // reduce the line height by this amount to squeeze more lines in
    
    wxTextLayout* m_pLayout; // hold the pointer to our get extent functor
};

// ----------------------------------------------------------------------------
// wxTextLayout: Default implementation to layout text in a rectangle
// ----------------------------------------------------------------------------

class wxTextLayout
{
public:
    wxTextLayout () { }
    wxTextLayout (wxDC* dc, 
    const wxString& text = "", 
    const wxRect& rect = wxRect (0, 0, 0, 0));
    
    wxTextLayout (wxGraphicsContext* gc) { }
    virtual ~wxTextLayout ();
    
    virtual wxVector<wxString>* GetLines () { return m_pEngine->GetLines(); }
    virtual wxVector<wxRect>* GetLineRects () { return m_pEngine->GetLineRects(); }

	virtual void SetGeometry (wxSize size); 
	virtual void SetMargins (int left, int right, int top, int bottom, int pinch = 0)
	{
		m_pEngine->SetMargins(left, right, top, bottom, pinch);
	}
	void SetFlags (int flags) { m_pEngine->SetFlags (flags); }
    void SetText (const wxString& text) { m_pEngine->SetText (text); }
    
    virtual void Render (wxDC* dc, const wxPoint& pos, 
                                int options = wxTEXTLAYOUT_DEBUG_OFF);
    virtual wxSize GetTokenExtent (const wxString& token);
    virtual void DrawEllipsis (wxDC* dc, const wxPoint& pos);
    
protected:
    wxDC* m_pDC;
    wxTextLayoutEngine* m_pEngine;
};

// ----------------------------------------------------------------------------
// wxEllipseTextLayout: Implementation to layout text in an ellipse
// ----------------------------------------------------------------------------

class wxEllipseTextLayout : public wxTextLayout
{
public:
    wxEllipseTextLayout (wxDC* dc, 
                            const wxString& text = "", 
                            const wxRect& rect = wxRect (0, 0, 0, 0));
    
    ~wxEllipseTextLayout () { }
};

// ----------------------------------------------------------------------------
// wxDiamondTextLayout: Implementation to layout text in an diamond
// ----------------------------------------------------------------------------

class wxDiamondTextLayout : public wxTextLayout
{
public:
    wxDiamondTextLayout (wxDC* dc, 
                            const wxString& text = "", 
                            const wxRect& rect = wxRect (0, 0, 0, 0));
    
    ~wxDiamondTextLayout () { }
};

// ----------------------------------------------------------------------------
// wxRoundedRectTextLayout: Implementation to layout text in a rounded rect
// ----------------------------------------------------------------------------

class wxRoundedRectTextLayout : public wxTextLayout
{
public:
    wxRoundedRectTextLayout (wxDC* dc, 
                                const wxString& text = "", 
                                const wxRect& rect = wxRect (0, 0, 0, 0),
                                int radius = 0);

    ~wxRoundedRectTextLayout () { }
	
    virtual void SetGeometry (wxSize size, int radius);
};

// ----------------------------------------------------------------------------
// wxParallelogramTextLayout: Implementation to layout text in a parallelogram
// ----------------------------------------------------------------------------

class wxParallelogramTextLayout : public wxTextLayout
{
public:
    wxParallelogramTextLayout (wxDC* dc, 
                                const wxString& text = "", 
                                const wxRect& rect = wxRect (0, 0, 0, 0),
                                int slope = 0);

    ~wxParallelogramTextLayout () { }
	
    virtual void SetGeometry (wxSize size, int slope);
};

#endif // WXTEXTLAYOUT_H

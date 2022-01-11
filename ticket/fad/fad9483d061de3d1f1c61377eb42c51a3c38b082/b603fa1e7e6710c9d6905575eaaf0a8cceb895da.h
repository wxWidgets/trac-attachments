#ifndef _WX_LEDNUMBERCTRL_H_
#define _WX_LEDNUMBERCTRL_H_

#ifdef __GNUG__
    #pragma interface "wxLEDNumberCtrl.h"
#endif

#include <wx/window.h>
#include <wx/control.h>

class wxEraseEvent;
class wxPaintEvent;
class wxSizeEvent;

// ----------------------------------------------------------------------------
// enum
// ----------------------------------------------------------------------------

enum wxLEDValueAlign
{
    wxLED_ALIGN_LEFT,
    wxLED_ALIGN_RIGHT,
    wxLED_ALIGN_CENTER
};

// ----------------------------------------------------------------------------
// wxLEDNumberCtrl
// ----------------------------------------------------------------------------

class wxLEDNumberCtrl :	public wxControl
{
public:
    // Constructors.
    wxLEDNumberCtrl();
    wxLEDNumberCtrl(wxWindow *pParent, wxWindowID Id = -1, wxPoint const &Pos = wxDefaultPosition,
        wxSize const &Size = wxDefaultSize);

    // Create functions.
    bool Create(wxWindow *pParent, wxWindowID Id = -1, wxPoint const &Pos = wxDefaultPosition,
        wxSize const &Size = wxDefaultSize);

    wxLEDValueAlign GetAlignment() const { return m_Alignment; }
    bool GetDrawFaded() const { return m_DrawFaded; }
    wxString const &GetValue() const { return m_Value; }

    void SetAlignment(wxLEDValueAlign Alignment, bool Redraw = true);
    void SetDrawFaded(bool DrawFaded, bool Redraw = true);
    void SetValue(wxString const &Value, bool Redraw = true);

private:
    // Members.
    wxString m_Value;
    wxLEDValueAlign m_Alignment;

    int m_LineMargin;
    int m_DigitMargin;
    int m_LineLength;
    int m_LineWidth;
    bool m_DrawFaded;
    int m_LeftStartPos;

    // Functions.
    void DrawDigit(wxDC &Dc, int Digit, int Column);
    void RecalcInternals(wxSize const &CurrentSize);

    // Events.
    DECLARE_EVENT_TABLE()

    void OnEraseBackground(wxEraseEvent &Event);
    void OnPaint(wxPaintEvent &Event);
    void OnSize(wxSizeEvent &Event);
};

#endif

 	  	 

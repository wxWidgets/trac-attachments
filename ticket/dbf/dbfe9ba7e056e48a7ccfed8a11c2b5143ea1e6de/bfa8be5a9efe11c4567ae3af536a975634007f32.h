#ifndef __WXRICH_TOOLTIP_H__
#define __WXRICH_TOOLTIP_H__

#include <wx/wx.h>
#include <wx/bitmap.h>
#include <wx/dc.h>
#include <wx/dcbuffer.h>
#include <wx/dcmemory.h>
#include <wx/artprov.h>
#include <wx/string.h>
#include <wx/event.h>
#include <wx/popupwin.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/panel.h>

#define wxRTT_POPUP_UNDER_PARENT 0x01

// Panel to hold the controls and background image
class wxRichToolTipCanvas: public wxPanel
{
public:
    wxRichToolTipCanvas(wxWindow* parent) : wxPanel(parent) {}
    void OnMouseMove(wxMouseEvent& event);
    void OnCaptureLost(wxMouseCaptureLostEvent& WXUNUSED(event));
private:
    DECLARE_EVENT_TABLE()
    wxDECLARE_NO_COPY_CLASS(wxRichToolTipCanvas);
    wxRichToolTipCanvas() {}
};

class wxRichToolTip: public wxPopupTransientWindow
{
public:
    wxRichToolTip(wxWindow* parent, const wxWindowID id = wxID_ANY,
                  const wxString& tip = wxEmptyString, const wxBitmap& tipImage = wxNullBitmap,
                  const wxString& header = wxEmptyString, const wxBitmap& headerIcon = wxNullBitmap,
                  const wxString& footer = wxEmptyString, const wxBitmap& footerIcon = wxNullBitmap,
                  const int flags = 0);
    ///Get the header label.
    void SetHeaderLabel(const wxString& header)
    {
        if (GetHeaderLabel() != header)
            { m_isDirty = true; }
        m_headerLabel->SetLabelMarkup(header);
    }
    ///Get the header label.
    wxString GetHeaderLabel() const { return m_headerLabel->GetLabel(); }
    ///Set the image for the header icon.
    void SetHeaderIcon(const wxBitmap& bmp)
    {
        m_headerIcon->SetBitmap(bmp);
        m_isDirty = true;
    }
    ///Set the tooltip text.
    void SetTip(const wxString& tip)
    {
        if (GetTip() != tip)
            { m_isDirty = true; }
        m_tipLabel->SetLabelMarkup(tip);
    }
    ///Get the tooltip text.
    wxString GetTip() const { return m_tipLabel->GetLabel(); }
    ///Set the image for the tooltip.
    void SetTipImage(const wxBitmap& bmp)
    {
        m_tipImage->SetBitmap(bmp);
        m_isDirty = true;
    }
    ///Set the footer text.
    void SetFooterLabel(const wxString& footer)
    {
        if (GetFooterLabel() != footer)
            { m_isDirty = true; }
        m_footerLabel->SetLabelMarkup(footer);
    }
    ///Get the footer text.
    wxString GetFooterLabel() const { return m_footerLabel->GetLabel(); }
    ///Set the image for the footer icon.
    void SetFooterIcon(const wxBitmap& bmp)
    {
        m_footerIcon->SetBitmap(bmp);
        m_isDirty = true;
    }
    ///Shows or hides the window.
    void Popup(wxWindow* winFocus);
    ///Set the delay after which the tooltip disappears or how long a tooltip remains visible.
    ///Setting to -1 (the default) will disable auto-popping (i.e., the tooltip will remain until the mouse leaves the tooltip's parent).
    static void SetAutoPop(long msecs)
        { m_autoPop = msecs; }
    ///Set the delay after which the tooltip appears.
    static void SetDelay(long msecs)
        { m_delay = msecs; }
    ///Set the delay between subsequent tooltips to appear.
    static void SetReshow(long msecs)
        { m_reshowDelay = msecs; }
    ///Enable or disable rich tooltips globally.
    static void Enable(bool flag)
        { m_enable = flag; }
private:
    void OnSize(wxSizeEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnAutoPopTimer(wxTimerEvent& WXUNUSED(event));

    void PrepareToShow(wxWindow* winFocus);

    wxRichToolTipCanvas* m_panel;
    wxBoxSizer* m_headerSizer;
    wxStaticText* m_headerLabel;
    wxStaticBitmap* m_headerIcon;
    wxStaticLine* m_headerLine;
    wxBoxSizer* m_descriptionSizer;
    wxStaticText* m_tipLabel;
    wxStaticBitmap* m_tipImage;
    wxBoxSizer* m_footerSizer;
    wxStaticText* m_footerLabel;
    wxStaticBitmap* m_footerIcon;
    wxStaticLine* m_footerLine;

    wxColour m_topColour;
    wxColour m_bottomColour;

    bool m_isDirty;

    static bool m_enable;
    static int m_autoPop;
    wxTimer m_autoPopTimer;
    static const int AUTOPOP_TIMER = 10001;
    static unsigned long m_delay;
    static unsigned long m_reshowDelay;

    int m_flags;
    wxRect m_popupBoundingRect;

    friend class wxRichToolTipCanvas;

    DECLARE_EVENT_TABLE()
    wxDECLARE_NO_COPY_CLASS(wxRichToolTip);
    wxRichToolTip() {}
};

#endif //__WXRICH_TOOLTIP_H__

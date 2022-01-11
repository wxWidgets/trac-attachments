#include "wxRichToolTip.h"

BEGIN_EVENT_TABLE(wxRichToolTipCanvas, wxPanel)
    EVT_MOTION(wxRichToolTipCanvas::OnMouseMove)
    EVT_MOUSE_CAPTURE_LOST(wxRichToolTipCanvas::OnCaptureLost)
END_EVENT_TABLE()

void wxRichToolTipCanvas::OnMouseMove(wxMouseEvent& event)
{
    wxASSERT_LEVEL_2_MSG(GetParent()->IsKindOf(CLASSINFO(wxRichToolTip)), "wxRichToolTipCanvas's parent must be a wxRichToolTip.");
    wxRichToolTip* tooltip = static_cast<wxRichToolTip*>(GetParent());
    if ( tooltip->m_popupBoundingRect.width &&
        !tooltip->m_popupBoundingRect.Contains(ClientToScreen(event.GetPosition())) )
    {
        // mouse left the bounding rect, disappear
        tooltip->Dismiss();
    }
    else if ((tooltip->m_flags & wxRTT_POPUP_UNDER_PARENT) == 0 && tooltip->IsShown())
    {
        int x, y;
        wxGetMousePosition(&x, &y);
        y += wxSystemSettings::GetMetric(wxSYS_CURSOR_Y)/2;
        tooltip->Position(wxPoint(x, y), wxSize(0,0));
    }
    else
    {
        event.Skip();
    }
}

void wxRichToolTipCanvas::OnCaptureLost(wxMouseCaptureLostEvent& WXUNUSED(event))
{}

BEGIN_EVENT_TABLE(wxRichToolTip, wxPopupTransientWindow)
    EVT_SIZE(wxRichToolTip::OnSize)
    EVT_TIMER(wxRichToolTip::AUTOPOP_TIMER, wxRichToolTip::OnAutoPopTimer)
END_EVENT_TABLE()

int wxRichToolTip::m_autoPop = -1;
unsigned long wxRichToolTip::m_delay = 500;//half a second
unsigned long wxRichToolTip::m_reshowDelay = 0;
bool wxRichToolTip::m_enable = true;

void wxRichToolTip::OnSize(wxSizeEvent& event)
{
    // redraw the gradient background in case of a resize
    wxBitmap bmp(event.GetSize());
    wxMemoryDC memDc(bmp);
    memDc.Clear();
    memDc.GradientFillLinear(GetClientRect(), m_topColour, m_bottomColour, wxSOUTH);
    memDc.SelectObject(wxNullBitmap);
    m_panel->SetBackgroundBitmap(bmp);
    event.Skip();
}

wxRichToolTip::wxRichToolTip(wxWindow* parent, const wxWindowID id,
                             const wxString& tip, const wxBitmap& tipImage,
                             const wxString& header, const wxBitmap& headerIcon,
                             const wxString& footer, const wxBitmap& footerIcon,
                             const int flags) :
    wxPopupTransientWindow(parent, wxBORDER_SIMPLE),
    m_panel(NULL),
    m_headerSizer(NULL), m_headerLabel(NULL), m_headerIcon(NULL), m_headerLine(NULL),
    m_descriptionSizer(NULL), m_tipLabel(NULL), m_tipImage(NULL),
    m_footerSizer(NULL), m_footerLabel(NULL), m_footerIcon(NULL), m_footerLine(NULL),
    m_topColour(*wxWHITE), m_bottomColour(*wxLIGHT_GREY),
    m_autoPopTimer(this, AUTOPOP_TIMER), m_isDirty(true), m_flags(flags)
{
    SetId(id);

    // the panel to hold the controls and have the background painted on
    m_panel = new wxRichToolTipCanvas(this);
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);

    // the header section
    m_headerSizer = new wxBoxSizer(wxHORIZONTAL);
    panelSizer->Add(m_headerSizer, 0, wxTOP|wxLEFT|wxRIGHT, 5);

    m_headerIcon = new wxStaticBitmap(m_panel, wxID_ANY, headerIcon);
    m_headerSizer->Add(m_headerIcon, 0, wxRIGHT, 5);

    m_headerLabel = new wxStaticText(m_panel, wxID_STATIC, wxEmptyString);
    m_headerLabel->SetLabelMarkup(header);
    m_headerSizer->Add(m_headerLabel, 0, wxALIGN_CENTER_VERTICAL);

    m_headerLine = new wxStaticLine(m_panel);
    panelSizer->Add(m_headerLine, 0, wxEXPAND|wxTOP|wxLEFT|wxRIGHT, 5);

    // the (optional) main image and description
    m_descriptionSizer = new wxBoxSizer(wxHORIZONTAL);
    panelSizer->Add(m_descriptionSizer, 0, wxALL, 5);

    m_tipImage = new wxStaticBitmap(m_panel, wxID_ANY, tipImage);
    m_descriptionSizer->Add(m_tipImage, 0, wxRIGHT, 5);

    m_tipLabel = new wxStaticText(m_panel, wxID_STATIC, wxEmptyString);
    m_tipLabel->SetLabelMarkup(tip);
    m_descriptionSizer->Add(m_tipLabel);

    // the footer section
    m_footerLine = new wxStaticLine(m_panel);
    panelSizer->Add(m_footerLine, 0, wxEXPAND|wxLEFT|wxRIGHT, 5);

    m_footerSizer = new wxBoxSizer(wxHORIZONTAL);
    panelSizer->Add(m_footerSizer, 0, wxTOP|wxLEFT|wxRIGHT, 5);

    m_footerIcon = new wxStaticBitmap(m_panel, wxID_ANY, footerIcon);
    m_footerSizer->Add(m_footerIcon, 0, wxRIGHT, 5);

    m_footerLabel = new wxStaticText(m_panel, wxID_STATIC, wxEmptyString);
    m_footerLabel->SetLabelMarkup(footer);
    m_footerSizer->Add(m_footerLabel, 0, wxALIGN_CENTER_VERTICAL);

    m_panel->SetSizer(panelSizer);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(m_panel);
    SetSizerAndFit(mainSizer);

    // draw a gradient background
    wxBitmap bmp(GetClientSize());
    wxMemoryDC memDc(bmp);
    memDc.Clear();
    memDc.GradientFillLinear(GetClientRect(), m_topColour, m_bottomColour, wxSOUTH);
    memDc.SelectObject(wxNullBitmap);

    m_panel->SetBackgroundBitmap(bmp);
}

void wxRichToolTip::OnAutoPopTimer(wxTimerEvent& WXUNUSED(event))
{
    Dismiss();
}

void wxRichToolTip::PrepareToShow(wxWindow* winFocus)
{
    if (m_isDirty)
    {
        wxMilliSleep(m_delay);
        // show or hide images based on whether they are valid bitmaps.
        // note that we need to detach the images if not being used
        // to get the layout correct for the text labels.
        if (m_headerIcon->GetBitmap().IsOk())
        {
            if (!m_headerSizer->GetItem(m_headerIcon))
            {
                m_headerSizer->Insert(0, m_headerIcon, 0, wxRIGHT, 5);
            }
        }
        else
        {
            m_headerSizer->Hide(m_headerIcon);
            m_headerSizer->Detach(m_headerIcon);
        }
        if (m_tipImage->GetBitmap().IsOk())
        {
            if (!m_descriptionSizer->GetItem(m_tipImage))
            {
                m_descriptionSizer->Insert(0, m_tipImage, 0, wxRIGHT, 5);
            }
        }
        else
        {
            m_descriptionSizer->Hide(m_tipImage);
            m_descriptionSizer->Detach(m_tipImage);
        }
        if (m_footerIcon->GetBitmap().IsOk())
        {
            if (!m_footerSizer->GetItem(m_footerIcon))
            {
                m_footerSizer->Insert(0, m_footerIcon, 0, wxRIGHT, 5);
            }
        }
        else
        {
            m_footerSizer->Hide(m_footerIcon);
            m_footerSizer->Detach(m_footerIcon);
        }
        // show or hide header based on whether it has content
        m_panel->GetSizer()->Show(m_headerSizer, !m_headerLabel->GetLabel().IsEmpty(), true);
        m_panel->GetSizer()->Show(m_headerLine, !m_headerLabel->GetLabel().IsEmpty(), true);
        // show or hide the description area based on whether it has content
        m_panel->GetSizer()->Show(m_descriptionSizer, !m_tipLabel->GetLabel().IsEmpty(), true);
        // show or hide the footer area based on whether it has content
        m_panel->GetSizer()->Show(m_footerSizer, !m_footerLabel->GetLabel().IsEmpty(), true);
        m_panel->GetSizer()->Show(m_footerLine, !m_footerLabel->GetLabel().IsEmpty(), true);
        Layout();
        Fit();
        m_isDirty = false;
    }
    else if (m_reshowDelay > 0)
    {
        wxMilliSleep(m_reshowDelay);
    }

    if (m_flags & wxRTT_POPUP_UNDER_PARENT)
    {
        Position(winFocus->GetScreenRect().GetBottomLeft(), wxSize(0,0));
    }
    else
    {
        int x, y;
        wxGetMousePosition(&x, &y);
        y += wxSystemSettings::GetMetric(wxSYS_CURSOR_Y)/2;
        Position(wxPoint(x, y), wxSize(0,0));
    }

    if (m_autoPop != -1)
    {
        m_autoPopTimer.Start(m_autoPop);
    }
}

void wxRichToolTip::Popup(wxWindow* winFocus)
{
    if (!m_enable)
    {
        return;
    }
    if (GetTip().IsEmpty())
    {
        Dismiss();
    }
    PrepareToShow(winFocus);
    if (IsShown())
    {
        return;
    }
    m_popupBoundingRect = winFocus->GetRect();
    wxPopupTransientWindow::Popup(winFocus);
}

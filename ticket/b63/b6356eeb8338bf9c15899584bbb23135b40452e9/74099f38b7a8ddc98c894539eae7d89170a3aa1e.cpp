#include "wx/wx.h"
#include "wx/vlbox.h"



/**
 *  VListBugList - Declaration and Implementation
 */

class VListBugList : public wxVListBox {
public:
    enum { NITEMS = 10 };
    VListBugList(wxWindow *parent) : wxVListBox(parent, wxID_ANY) {
        wxClientDC clientDC(this);
        wxCoord w;
        clientDC.GetTextExtent(" ", &w, &m_fontHeight);
        SetItemCount(NITEMS);
    }

protected:
    virtual wxCoord OnMeasureItem(size_t n) const {
        return m_fontHeight;
    }
    virtual void OnDrawItem(wxDC& dc, const wxRect& rect, size_t n) const {
        dc.DrawText(n == 1 ? "Going down!" : "", rect.x, rect.y);
    }

private:
    wxCoord m_fontHeight;
};



/**
 *  VListBugFrame - Declaration and Implementation
 */

class VListBugFrame : public wxFrame
{
public:
	VListBugFrame(const wxString &title) : wxFrame (NULL, wxID_ANY, title) {
        m_list = new VListBugList(this);
        wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(m_list, 1, wxEXPAND);
        sizer->Add(new wxButton(this, wxID_ANY, "Click Me"), 0, wxEXPAND);
        SetSizer(sizer);
    }

    void OnClick(wxCommandEvent &evt) {
        //! @bug  SetItemCount() results in physical scroll of VListBugFrame
        m_list->SetItemCount(VListBugList::NITEMS);
        // Uncomment Refresh() for update flicker instead.
        //Refresh();
    }

private:
	DECLARE_EVENT_TABLE();

private:
    VListBugList *m_list;
};

BEGIN_EVENT_TABLE(VListBugFrame, wxFrame)
EVT_BUTTON(wxID_ANY, VListBugFrame::OnClick)
END_EVENT_TABLE()



/**
 *  VListBugApp - Delcaration and Implementation
 */

class VListBugApp : public wxApp
{
public:
    virtual bool OnInit() {
        VListBugFrame *frame = new VListBugFrame(_T("VListBug"));
        frame->Show(TRUE);
        SetTopWindow(frame);
        return true;
    }
};

DECLARE_APP(VListBugApp)

IMPLEMENT_APP(VListBugApp)

 	  	 

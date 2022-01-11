#include "wx/wx.h"
#include "wx/listctrl.h"

class TestListCtrl : public wxListCtrl {
public:
    TestListCtrl(wxWindow *parent,
               const wxWindowID id,
               const wxPoint& pos,
               const wxSize& size,
               long style)
        : wxListCtrl(parent, id, pos, size, style)
    {}
    virtual wxString OnGetItemText(long item, long column) const {
        return wxString::Format(wxT("item %ld column %ld"), item, column);
    }
    virtual wxListItemAttr *OnGetItemAttr(long item) const {
        static wxListItemAttr normal(
            wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT), wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW), wxNullFont);
        static wxListItemAttr stripe(
            wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT), wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE), wxNullFont);
        if (item % 2) {
            return &stripe;
        } else {
            return &normal;
        }
    }
};

class TestApp : public wxApp {
public:
    virtual bool OnInit() {
        if ( !wxApp::OnInit() )
            return false;

        wxFrame *frame = new wxFrame(NULL, wxID_ANY, wxT("test"), wxDefaultPosition, wxSize(600, 500));

        wxPanel* panel = new wxPanel(frame, wxID_ANY);
        wxTextCtrl* text = new wxTextCtrl(panel, wxID_ANY, wxEmptyString,
                                     wxDefaultPosition, wxDefaultSize,
                                     wxTE_READONLY | wxTE_MULTILINE | wxSUNKEN_BORDER);

        TestListCtrl* list = new TestListCtrl(panel, wxID_ANY,
                                    wxDefaultPosition, wxDefaultSize,
                                    wxLC_REPORT | wxLC_VIRTUAL);
        list->EnableSystemTheme(false);

        list->AppendColumn(wxT("column"), wxLIST_FORMAT_LEFT, 150 );
        list->SetItemCount(100);

        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(list, 1, wxEXPAND, 1);
        sizer->Add(text, 0 , wxEXPAND , 1);
        panel->SetSizer(sizer);
        frame->Layout();

        frame->Show(true);

        return true;
    }

};

wxIMPLEMENT_APP(TestApp);

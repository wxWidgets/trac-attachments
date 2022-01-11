#include <wx/app.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/popupwin.h>
#include <wx/scrolwin.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/treelist.h>

class PopupWindow : public wxPopupTransientWindow {
 private:
  wxTreeListCtrl *m_tree_list_ctrl = nullptr;
  wxTextCtrl *m_text_ctrl = nullptr;

 public:
  PopupWindow(wxWindow *parent) : wxPopupTransientWindow{parent} {
    SetSize(wxSize{200, 220});
    auto panel = new wxPanel{this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                             wxBORDER_SIMPLE | wxTAB_TRAVERSAL | wxWANTS_CHARS};
    {  // panel
      m_tree_list_ctrl =
          new wxTreeListCtrl{panel, wxID_ANY, wxDefaultPosition,
                             wxSize{200, 200}, wxTL_MULTIPLE | wxTL_NO_HEADER};
      m_tree_list_ctrl->AppendColumn(wxEmptyString);
      for (int i = 1; i <= 10; ++i) {
        m_tree_list_ctrl->AppendItem(m_tree_list_ctrl->GetRootItem(),
                                     wxString::Format("item %d", i), -1, -1);
      }
      m_text_ctrl = new wxTextCtrl{panel, wxID_ANY};

      auto sizer = new wxBoxSizer{wxVERTICAL};
      sizer->Add(m_tree_list_ctrl, wxSizerFlags{0}.Expand());
      sizer->Add(m_text_ctrl, wxSizerFlags{0}.Expand());
      panel->SetSizer(sizer);
    }
    {  // popup window
      auto sizer = new wxBoxSizer{wxVERTICAL};
      sizer->Add(panel, wxSizerFlags{0}.Expand());
      SetSizer(sizer);
      Layout();
    }
    Bind(wxEVT_CHAR_HOOK, [this](wxKeyEvent &event) {
      switch (event.GetKeyCode()) {
        case WXK_RETURN:
        case WXK_ESCAPE:
          Dismiss();
          break;
        default:
          event.Skip();
      }
    });
  }
  void Popup(wxWindow *focus = nullptr) override {
    const auto pos = GetParent()->ClientToScreen(wxPoint{0, 0});
    Position(pos, wxSize{0, GetParent()->GetSize().y});  // (origin, size)
    wxPopupTransientWindow::Popup(focus);
  }
};

class TextWithPopup : public wxStaticText {
 private:
  PopupWindow *m_popup = nullptr;

 public:
  TextWithPopup(wxWindow *parent)
      : wxStaticText{parent, wxID_ANY, "click me or press enter or space"} {
    m_popup = new PopupWindow{this};
    Bind(wxEVT_LEFT_UP, [this](wxMouseEvent &event) {
      m_popup->Popup();
      event.Skip();
    });
  }
};

class Frame : public wxFrame {
 public:
  Frame()
      : wxFrame(nullptr, wxID_ANY, "test", wxDefaultPosition,
                wxSize{800, 600}) {
    auto sizer = new wxBoxSizer{wxVERTICAL};
    sizer->Add(new TextWithPopup{this});
    SetSizer(sizer);
  }
};

class App : public wxApp {
 public:
  bool OnInit() override {
    auto frame = new Frame();
    frame->Show();
    return true;
  }
};

IMPLEMENT_APP(App)

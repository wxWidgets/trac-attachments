#include <wx/app.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/popupwin.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>

class PopupWindow : public wxPopupTransientWindow {
 private:
  wxTextCtrl *m_text_ctrl = nullptr;

 public:
  PopupWindow(wxWindow *parent) : wxPopupTransientWindow{parent} {
    SetSize(wxSize{200, 200});
    auto panel = new wxPanel{this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                             wxBORDER_SIMPLE | wxTAB_TRAVERSAL | wxWANTS_CHARS};
    {  // panel
      m_text_ctrl = new wxTextCtrl{panel, wxID_ANY};

      auto sizer = new wxBoxSizer{wxVERTICAL};
      sizer->Add(m_text_ctrl, wxSizerFlags{0}.Expand());
      panel->SetSizer(sizer);
    }
    {  // popup window
      auto sizer = new wxBoxSizer{wxVERTICAL};
      sizer->Add(panel, wxSizerFlags{0}.Expand());
      SetSizer(sizer);
      Layout();
    }
  }
  void Popup(wxWindow *focus = nullptr) override {
    const auto pos = GetParent()->ClientToScreen(wxPoint{0, 0});
    Position(pos, wxSize{0, GetParent()->GetSize().y});  // (origin, size)
    wxPopupTransientWindow::Popup(focus);
  }
};

class TextWithPopup : public wxTextCtrl {
 private:
  PopupWindow *m_popup = nullptr;

 public:
  TextWithPopup(wxWindow *parent)
      : wxTextCtrl{parent, wxID_ANY, "click me or press enter or space"} {
    m_popup = new PopupWindow{this};
    Bind(wxEVT_LEFT_UP, [this](wxMouseEvent &) { m_popup->Popup(); });
    Bind(wxEVT_CHAR_HOOK, [this](wxKeyEvent &event) {
      std::cerr << "wxEVT_CHAR_HOOK\n";
      if (m_popup->IsShown()) {
        switch (event.GetKeyCode()) {
          case WXK_RETURN:
          case WXK_ESCAPE:
            m_popup->Dismiss();
            break;
          case WXK_TAB:
            m_popup->Dismiss();
            SetFocus();
            Navigate(event.ShiftDown() ? wxNavigationKeyEvent::IsBackward
                                       : wxNavigationKeyEvent::IsForward);
            break;
          default:
            event.Skip();
        }
      } else {
        switch (event.GetKeyCode()) {
          case WXK_TAB:
            Navigate(event.ShiftDown() ? wxNavigationKeyEvent::IsBackward
                                       : wxNavigationKeyEvent::IsForward);
            break;
          case WXK_RETURN:
          case WXK_SPACE:
            m_popup->Popup();
            break;
          default:
            event.Skip();
        }
      }
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

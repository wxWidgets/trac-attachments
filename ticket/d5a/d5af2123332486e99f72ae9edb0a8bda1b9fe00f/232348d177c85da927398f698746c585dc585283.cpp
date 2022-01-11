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
  wxTextCtrl *m_text_ctrl = nullptr;
  wxTreeListCtrl *m_tree_list_ctrl = nullptr;

 public:
  PopupWindow(wxWindow *parent) : wxPopupTransientWindow{parent} {
    SetSize(wxSize{200, 220});
    auto panel = new wxPanel{this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                             wxBORDER_SIMPLE | wxTAB_TRAVERSAL | wxWANTS_CHARS};
    {  // panel
      m_tree_list_ctrl = new wxTreeListCtrl{panel, wxID_ANY, wxDefaultPosition,
                                            wxSize{200, 200}};
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
    Bind(wxEVT_LEFT_UP, [this](wxMouseEvent &event) {
      m_popup->Popup();
      event.Skip();
    });
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
    auto frame_sizer = new wxBoxSizer{wxVERTICAL};
    SetSizer(frame_sizer);

    auto scrolled_win = new wxScrolledWindow{this, wxID_ANY, wxDefaultPosition,
                                             wxDefaultSize, wxVSCROLL};
    auto win_sizer = new wxBoxSizer{wxVERTICAL};
    scrolled_win->SetSizer(win_sizer);
    scrolled_win->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_ALWAYS);
    scrolled_win->SetScrollRate(0, GetCharHeight());
    for (auto i = 0; i < 50; ++i) {
      win_sizer->Add(new wxStaticText{scrolled_win, wxID_ANY,
                                      wxString::Format("Hello world %d", i)});
    }
    win_sizer->Add(new TextWithPopup{scrolled_win});
    for (auto i = 50; i < 70; ++i) {
      win_sizer->Add(new wxStaticText{scrolled_win, wxID_ANY,
                                      wxString::Format("Hello world %d", i)});
    }
    frame_sizer->Add(scrolled_win, wxSizerFlags{1}.Expand());
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

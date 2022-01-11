#include <wx/app.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>

#include <memory>

class Frame : public wxFrame {
 private:
  std::unique_ptr<wxMenu> m_popup_menu;

 public:
  Frame() : wxFrame(nullptr, wxID_ANY, wxT("test-wxwidgets")) {
    m_popup_menu = std::make_unique<wxMenu>();
    // top menu
    m_popup_menu->Bind(
        wxEVT_MENU,
        [](wxCommandEvent &) { wxMessageBox("context menu command"); },
        m_popup_menu->Append(wxID_ANY, "context menu command")->GetId());
    // sub menu
    auto sub_menu = new wxMenu{};
    // this bind is never called on MSW, why?
    sub_menu->Bind(wxEVT_MENU,
                   [](wxCommandEvent &) { wxMessageBox("sub menu command"); },
                   sub_menu->Append(wxID_ANY, "sub menu command")->GetId());
    m_popup_menu->AppendSubMenu(sub_menu, "sub menu");
    Bind(wxEVT_RIGHT_DOWN,
         [this](wxMouseEvent &) { PopupMenu(m_popup_menu.get()); });
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

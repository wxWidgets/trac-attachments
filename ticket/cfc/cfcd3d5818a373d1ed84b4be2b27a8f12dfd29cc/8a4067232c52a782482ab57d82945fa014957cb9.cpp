#include <wx/app.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>

#include <iostream>

class Dialog : public wxDialog {
 private:
  wxTextCtrl *m_text = nullptr;
  std::string m_text_str;

 public:
  Dialog(wxWindow *parent) : wxDialog{parent, wxID_ANY, wxT("Enter a text")} {
    std::cerr << "dialog address: " << this << '\n';
    auto sizer = new wxBoxSizer{wxVERTICAL};
    SetSizer(sizer);

    m_text = new wxTextCtrl{this, wxID_ANY};
    m_text->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent &event) {
      event.Skip();
      m_text_str = std::string{m_text->GetValue().utf8_str()};
      std::cout << "text=[" << m_text_str << "]\n";
    });
    sizer->Add(m_text, wxSizerFlags{}.Expand());

    {
      // sets 2 buttons, OK = default and Cancel
      auto bsizer = new wxStdDialogButtonSizer{};
      auto ok = new wxButton{this, wxID_OK};
      ok->SetDefault();
      bsizer->AddButton(ok);
      bsizer->AddButton(new wxButton{this, wxID_CANCEL});
      bsizer->Realize();
      sizer->Add(bsizer, wxSizerFlags{}.Center());
    }
  }
};

class Frame : public wxFrame {
 public:
  Frame() : wxFrame(nullptr, wxID_ANY, wxT("test")) {}
};

class App : public wxApp {
 public:
  bool OnInit() override {
    Dialog dlg{nullptr};
    if (dlg.ShowModal() != wxID_OK) return false;
    auto frame = new Frame();
    frame->Show();
    return true;
  }
};

IMPLEMENT_APP(App)

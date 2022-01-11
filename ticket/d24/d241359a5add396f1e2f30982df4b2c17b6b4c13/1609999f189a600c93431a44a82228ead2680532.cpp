#include <wx/app.h>
#include <wx/datectrl.h>
#include <wx/frame.h>
#include <wx/scrolwin.h>
#include <wx/sizer.h>
#include <wx/string.h>

class Frame : public wxFrame {
 private:
 public:
  Frame() : wxFrame(NULL, wxID_ANY, "Choice") {
    auto frame_sizer = new wxBoxSizer{wxVERTICAL};
    SetSizer(frame_sizer);
    auto scroll = new wxScrolledWindow{this, wxID_ANY, wxDefaultPosition,
                                       wxDefaultSize, wxVSCROLL};
    scroll->ShowScrollbars(wxSHOW_SB_DEFAULT, wxSHOW_SB_ALWAYS);
    scroll->SetScrollRate(0, 50);
    frame_sizer->Add(scroll, wxSizerFlags{}.Expand().Proportion(1));
    auto scroll_sizer = new wxBoxSizer{wxVERTICAL};
    scroll->SetSizer(scroll_sizer);
    for (auto i = 0; i < 50; ++i) {
      scroll_sizer->Add(
          new wxDatePickerCtrl{scroll, wxID_ANY, wxDefaultDateTime,
                               wxDefaultPosition, wxDefaultSize,
                               wxDP_DEFAULT | wxDP_DROPDOWN | wxDP_SHOWCENTURY},
          wxSizerFlags{}.Expand().Proportion(0));
    }
  }
};

class App : public wxApp {
 public:
  virtual bool OnInit() override {
    if (not wxApp::OnInit()) return false;
    auto frame = new Frame();
    frame->Show(true);
    return true;
  }
};

wxIMPLEMENT_APP(App);

#include <wx/app.h>
#include <wx/collpane.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/scrolwin.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/window.h>
#include <wx/wrapsizer.h>

class TextListCtrl : public wxWindow {
 public:
  TextListCtrl(wxWindow* parent, const wxColour& colour)
      : wxWindow{parent, wxID_ANY} {
    auto sizer = new wxWrapSizer{wxHORIZONTAL};
    SetSizer(sizer);
    for (int i = 0; i < 20; ++i) {
      wxString t;
      t.Printf("(hello world hello world %d)", i);
      auto stext = new wxStaticText{this, wxID_ANY, t};
      stext->SetForegroundColour(colour);
      sizer->Add(stext, wxSizerFlags{});
    }
  }
};

class Frame : public wxFrame {
 public:
  Frame()
      : wxFrame(nullptr, wxID_ANY, "test-wxwidgets", wxDefaultPosition,
                wxSize{800, 600}) {
    auto frame_sizer = new wxBoxSizer{wxVERTICAL};
    SetSizer(frame_sizer);

    // 1. Insert TextListCtrl directly in the wxFrame -> works
    frame_sizer->Add(new TextListCtrl{this, *wxBLUE}, wxSizerFlags{}.Expand());

    auto scrollwin = new wxScrolledWindow{this, wxID_ANY, wxDefaultPosition,
                                          wxDefaultSize, wxVSCROLL};
    auto scrollwin_sizer = new wxBoxSizer{wxVERTICAL};
    scrollwin->SetSizer(scrollwin_sizer);
    // 2. Insert TextListCtrl directly inside a wxScrolledWindow
    //    -> does not resize properly
    scrollwin_sizer->Add(new TextListCtrl{scrollwin, *wxRED},
                         wxSizerFlags{}.Expand());

    // 3. Insert TextListCtrl inside a wxCollapsiblePane
    //    -> does not resize properly
    // However, if you remove 3. (by replacing true by false below), then 2.
    // resizes properly!
    if (true) {
      auto colpane = new wxCollapsiblePane{
          scrollwin,     wxID_ANY,
          "colpane",     wxDefaultPosition,
          wxDefaultSize, wxCP_DEFAULT_STYLE | wxCP_NO_TLW_RESIZE};
      // this apprently doesn't help
      colpane->Bind(
          wxEVT_COLLAPSIBLEPANE_CHANGED,
          [scrollwin](wxCollapsiblePaneEvent&) { scrollwin->FitInside(); });
      auto pane = colpane->GetPane();
      auto vsizer = new wxBoxSizer{wxVERTICAL};
      pane->SetSizer(vsizer);
      //colpane->Expand();  // uncomment that line and 2. and 3. resize properly but not after manual collapse/expand

      vsizer->Add(new TextListCtrl{pane, *wxRED}, wxSizerFlags{}.Expand());
      scrollwin_sizer->Add(colpane, wxSizerFlags{1}.Expand());
    }

    scrollwin->Bind(wxEVT_SIZE,
                    [scrollwin](wxSizeEvent&) { scrollwin->FitInside(); });

    frame_sizer->Add(scrollwin, wxSizerFlags{1}.Expand());
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

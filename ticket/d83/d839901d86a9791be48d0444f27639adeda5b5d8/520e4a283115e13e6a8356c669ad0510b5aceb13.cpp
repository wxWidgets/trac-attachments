#include <wx/app.h>
#include <wx/artprov.h>
#include <wx/aui/auibar.h>
#include <wx/aui/framemanager.h>
#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/window.h>

class Panel : public wxWindow {
 private:
  wxAuiManager m_manager;

 public:
  Panel(wxWindow* parent);
  ~Panel() override { m_manager.UnInit(); }
};

Panel::Panel(wxWindow* parent) : wxWindow{parent, wxID_ANY} {
  m_manager.SetManagedWindow(this);
  m_manager.SetFlags(wxAUI_MGR_LIVE_RESIZE);
  {  // add a tool bar
    auto tool_bar = new wxAuiToolBar{this, wxID_ANY, wxDefaultPosition,
                                     wxDefaultSize, wxAUI_TB_DEFAULT_STYLE};
    tool_bar->AddTool(wxID_ANY, "tool label",
                      wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_TOOLBAR),
                      "tool help", wxITEM_NORMAL);
    tool_bar->Realize();
    m_manager.AddPane(tool_bar, wxAuiPaneInfo{}
                                    .Name("toolbar name")
                                    .Caption("toolbar caption")
                                    .ToolbarPane()
                                    .Top());
  }
  {  // add a window
    auto pane = new wxWindow{this, wxID_ANY};
    m_manager.AddPane(pane, wxAuiPaneInfo{}
                                .Name("window name")
                                .Caption("window caption")
                                .Center()
                                .MaximizeButton(true)
                                .CloseButton(false)
                                .Show());
  }
  m_manager.Update();
}

class Frame : public wxFrame {
 public:
  Frame(const wxString& title, const wxSize& size)
      : wxFrame{nullptr, wxID_ANY, title, wxDefaultPosition, size} {
    auto sizer = new wxBoxSizer{wxVERTICAL};
    sizer->Add(new Panel{this}, wxSizerFlags{1}.Expand());
    SetSizer(sizer);
  }
};

class App : public wxApp {
 public:
  bool OnInit() override {
    wxImage::AddHandler(new wxPNGHandler{});
    auto frame = new Frame{"aui-toolbar", wxSize{1024, 768}};
    frame->Show(true);
    return true;
  }
};

wxIMPLEMENT_APP(App);

// Window containing word-wrapping wxTextCtrl, with fixed width, that
// automatially resizes its height to fit current contents.
// Tests various methods of working with wrapped lines in wxGTK wxTextCtrl.
// build with:
//    g++ `wx-config --cxxflags --libs --toolkit=gtk2` `pkg-config --cflags --libs gtk+-2.0` textwrap.cpp -o textwrap
// When running, type/paste long lines into the text edit, and look at console output.

#include <wx/wx.h>
#include <gtk/gtk.h>

// subclassed wxTextCtrl with wxTE_MULTILINE|wxTE_BESTWRAP,
// that has fixed width, and adjusts its height according to number of wrapped lines displayed
class MyTextCtrl : public wxTextCtrl
{
private:
  int GetWrappedLinesCount();
public:
  void FitToWidth();
  MyTextCtrl(wxWindow* parent, const wxString& text, const wxPoint& pos, int width);
};

MyTextCtrl::MyTextCtrl(wxWindow* parent, const wxString& text, const wxPoint& pos, int width)
  :wxTextCtrl(parent, wxID_ANY, wxEmptyString, pos, wxSize(width, -1), wxBORDER_NONE | wxTE_MULTILINE | wxTE_BESTWRAP | wxTE_NO_VSCROLL)
{
  SetValue(text);
}

int MyTextCtrl::GetWrappedLinesCount()
{
  GtkTextView *textview = GTK_TEXT_VIEW(GetConnectWidget());
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);
  GtkTextIter iter;
  gtk_text_buffer_get_start_iter(buffer, &iter);
  int lines=1;
  while (gtk_text_view_forward_display_line(textview, &iter))
    lines++;

  // Preceding code won't count last line, if there is exactly one empty line at the end of buffer.
  // Probably it is some unfortunate handling of a special-case?
  // Check this case manually.
  gtk_text_buffer_get_end_iter(buffer, &iter);
  if (gtk_text_iter_starts_line(&iter))
    lines++;

  return lines;
}

void MyTextCtrl::FitToWidth()
{
  printf("------------ MyTextCtrl::FitToWidth:\n");

  int line_height = GetCharHeight();
  printf("GetCharHeight() = %d\n", line_height);

  int logical_lines = GetNumberOfLines();
  printf("GetNumberOfLines() = %d\n", logical_lines);

  int physical_lines = GetWrappedLinesCount();
  printf("GetWrappedLineCount() = %d\n", physical_lines);
  int correct_height = physical_lines*line_height;

  wxSize extent = GetTextExtent(GetValue());
  printf("GetTextExtent() = %d:%d\n", extent.GetWidth(), extent.GetHeight());

  long end_x, end_y;
  PositionToXY(GetLastPosition(), &end_x, &end_y);
  printf("PositionToXY(GetLastPosition()) = %d:%d\n", end_x, end_y);

  // PositionToCoords. Uses gtk_text_view_buffer_to_window_coords() internally.
  // returns wrong value first time after Enter is pressed
  wxPoint endcoords = PositionToCoords(GetLastPosition());
  printf("PositionToCoords(GetLastPosition()) = %d:%d\n", endcoords.x, endcoords.y);
  if (endcoords.y + line_height != correct_height)
    printf("    WRONG!\n");

  GtkTextView *view = GTK_TEXT_VIEW(GetConnectWidget());
  GtkRequisition req;
  gtk_widget_size_request(GTK_WIDGET(view), &req);
  printf("gtk_widget_size_request = %d:%d\n", req.width, req.height);
  if (req.height != correct_height)
    printf("    WRONG!\n");

  wxSize size(GetSize().GetWidth(), physical_lines * line_height);
  SetMinSize(size);
  SetMaxSize(size);
}

//----------------------------------------------
// Test MyTextCtrl
class MyFrame : public wxFrame
{
  MyTextCtrl* textctrl;
  wxBoxSizer* sizer;
public:
  MyFrame(const wxString& caption);
  void OnText(wxCommandEvent&);
  void OnButton(wxCommandEvent& event);
};

MyFrame::MyFrame(const wxString& caption)
  :wxFrame(0, wxID_ANY, caption, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
  wxButton* btn_resize = new wxButton(this, wxID_ANY, "Recalculate size", wxDefaultPosition, wxSize(200,40));
  btn_resize->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MyFrame::OnButton, this);

  wxString text("Blah blah");
  textctrl = new MyTextCtrl(this, text, wxDefaultPosition, 200);
  Bind(wxEVT_TEXT, &MyFrame::OnText, this);
  textctrl->FitToWidth();

  sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(btn_resize, 0);
  sizer->Add(textctrl, 1);
  SetSizerAndFit(sizer);
}

void MyFrame::OnButton(wxCommandEvent& event)
{
  textctrl->FitToWidth();
  sizer->Layout();
  sizer->Fit(this);
}

void MyFrame::OnText(wxCommandEvent& event)
{
  textctrl->FitToWidth();
  sizer->Layout();
  sizer->Fit(this);
}

class MyApp : public wxApp
{
public:
  virtual bool OnInit() wxOVERRIDE {
    MyFrame *frame = new MyFrame("Test wxTextCtrl width");
    frame->Show(true);
    return true;
  }
};
wxIMPLEMENT_APP(MyApp);

// g++ demo.cpp -o demo -std=gnu++11 -I/DeveloperLibs/wxWidgets-3.1.2/build-debug/lib/wx/include/osx_cocoa-unicode-static-3.1/ -I/DeveloperLibs/wxWidgets-3.1.2/include -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__ -D_DEBUG=1-stdlib=libc++ -L/DeveloperLibs/wxWidgets-3.1.2/build-debug/lib/ -framework IOKit -framework Carbon -framework Cocoa -framework AudioToolbox -framework System -lwx_baseu-3.1 -lwx_osx_cocoau_adv-3.1 -lwx_osx_cocoau_core-3.1 -liconv -lz -headerpad_max_install_names -lwxregexu-3.1 -lwx_osx_cocoau_qa-3.1 -framework Quartz -lwx_baseu_xml-3.1 -lwxjpeg-3.1 -lwxpng-3.1 -lwxzlib-3.1 -lwxexpat-3.1 -lwxtiff-3.1 -llzma

#include <wx/wx.h>
#include <wx/app.h>
#include <wx/graphics.h>
#include <wx/event.h>
#include <wx/dcbuffer.h>
#include <wx/dc.h>
#include <wx/dcbuffer.h>
#include <wx/font.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/slider.h>
#include <wx/tglbtn.h>
#include <wx/sizer.h>
#include <wx/timer.h>
#include <wx/frame.h>
#include <wx/window.h>
#include <wx/mstream.h>
#include <wx/colour.h>
#include <wx/gdicmn.h>
#include <wx/stopwatch.h>

class Widget : public wxWindow
{
  enum
  {
    red = 0,
    green,
    blue
  } state = red;
  wxStopWatch stopwatch;
  wxBitmap *bitmap = nullptr;
  long duration = 0;
  unsigned long counter = 0;
  int counterX = 0;
  double radius = 0;
  int radiusCurrent = 0;
  wxColour colour { 255,0,0 };
  int const displayDepth = wxDisplayDepth();
  wxSize size;
  int centreX = 0;
  int centreY = 0;
  void OnSize(wxSizeEvent& event)
  {
    event.Skip();
    size = event.GetSize();
    radius = static_cast<double>(std::min(size.GetWidth(), size.GetHeight())) / 2.0;
    radiusCurrent = radius;
    centreX = size.GetWidth() / 2;
    centreY = size.GetHeight() / 2;
    GenerateBitmap();
  }
  void GenerateBitmap()
  {
    delete bitmap;
    bitmap = nullptr;
    if (size.x == 0 || size.y == 0)
    {
      return;
    }
    bitmap = new wxBitmap(size.x, size.y, displayDepth);
    bitmap->UseAlpha(true);
    wxMemoryDC memorydc(*bitmap);
    wxGraphicsContext *context = wxGraphicsContext::Create(memorydc);
    if (context)
    {
      std::unique_ptr<wxGraphicsContext> cleanup(context);
      //context->SetBrush(*wxBLUE_BRUSH);
      //context->DrawRectangle(0.0, 0.0, size.GetWidth(), size.GetHeight());
      context->SetBrush(*wxTRANSPARENT_BRUSH);
      context->SetPen(*wxTRANSPARENT_PEN);
      wxGraphicsBrush brush = context->CreateRadialGradientBrush(centreX, centreY, centreX, centreY, radius, colour, wxTransparentColour);
      context->SetBrush(brush);
      context->SetPen(*wxWHITE_PEN);
      wxGraphicsPath path = context->CreatePath();
      path.AddCircle(centreX, centreY, radius);
      context->DrawPath(path);
      context->Flush();
    }
    memorydc.SelectObject(wxNullBitmap);
  }
  void OnPaint(wxPaintEvent& event)
  {
    wxAutoBufferedPaintDC dc(this);
    dc.SetBrush(*wxWHITE_BRUSH);
    dc.Clear();
    dc.SetPen(*wxBLACK_PEN);
    if (bitmap)
    {
      stopwatch.Start();
      dc.DrawBitmap(*bitmap, 0, 0, true);
      duration += stopwatch.Time();
      stopwatch.Pause();
    }
    dc.DrawCircle(centreX, centreY, radiusCurrent);
    wxString text;
    text << counter;
    wxSize extent = dc.GetTextExtent(text);
    dc.DrawText(text, centreX - (extent.x / 2), centreY - (extent.y / 2));
    event.Skip();
  }
public:
  Widget(wxWindow* const parent)
  : wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
  {
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    Bind(wxEVT_PAINT, &Widget::OnPaint, this, GetId());
    Bind(wxEVT_SIZE, &Widget::OnSize, this, GetId());
  }
  virtual ~Widget()
  {
    Unbind(wxEVT_PAINT, &Widget::OnPaint, this, GetId());
    Unbind(wxEVT_SIZE, &Widget::OnSize, this, GetId());
    delete bitmap;
    bitmap = nullptr;
  }
  void Fire()
  {
    ++counter;
    unsigned char r = colour.Red();
    unsigned char g = colour.Green();
    unsigned char b = colour.Blue();
    switch (state)
    {
      case red:
        ++r;
        if (r == 255)
        {
          state = blue;
        }
        break;
      case blue:
        ++b;
        if (b == 255)
        {
          state = green;
        }
      case green:
        ++g;
        if (g == 255)
        {
          state = red;
        }
        break;
    }
    colour = wxColour(r, g, b);
    GenerateBitmap();
    counterX += 10;
    if (counterX > size.x)
    {
      counterX = 0;
    }
    radiusCurrent -= 10;
    if (radiusCurrent < 0)
    {
      radiusCurrent = radius;
    }
    Refresh();
  }
  void Reset()
  {
    counter = 0;
    duration = 0;
  }
  wxString GetStats() const
  {
    wxString x;
    x << "Average milliseconds: " << (static_cast<double>(duration) / static_cast<double>(counter));
    return x;
  }
};

class MainFrame : public wxFrame
{
protected:
  Widget *slowPainter;
  wxStaticText* statusLabel;
  wxSlider* timerSlider;
  wxToggleButton* timerEnableButton;
  wxTimer timer;
  void OnTimerSlider( wxCommandEvent& event )
  {
    event.Skip();
    if (timerEnableButton->GetValue())
    {
      timer.Stop();
      timer.Start(event.GetInt());
    }
  }
  void OnTimerEnableButtonClick( wxCommandEvent& event )
  {
    event.Skip();
    if (event.IsChecked())
    {
      timer.Stop();
      slowPainter->Reset();
      timer.Start(timerSlider->GetValue());
    }
    else
    {
      timer.Stop();
      statusLabel->SetLabel(wxT("Timer disabled"));
    }
  }
  void OnTimer( wxTimerEvent& event )
  {
      event.Skip();
      slowPainter->Fire();
      wxString stats = slowPainter->GetStats();
      statusLabel->SetLabel(stats);
      SetTitle(stats);
  }
public:
  MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL )
  : wxFrame(parent, id, title, pos, size, style)
  {
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );
    wxBoxSizer* bSizer1;
    bSizer1 = new wxBoxSizer( wxVERTICAL );
    slowPainter = new Widget(this);
    bSizer1->Add( slowPainter, 1, wxALL|wxEXPAND, 5 );
    wxBoxSizer* bSizer2;
    bSizer2 = new wxBoxSizer( wxHORIZONTAL );
    statusLabel = new wxStaticText( this, wxID_ANY, wxT("Timer disabled"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT|wxST_NO_AUTORESIZE );
    statusLabel->Wrap( -1 );
    bSizer2->Add( statusLabel, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
    timerSlider = new wxSlider( this, wxID_ANY, 50, 1, 750, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
    bSizer2->Add( timerSlider, 0, wxALL, 5 );
    timerEnableButton = new wxToggleButton( this, wxID_ANY, wxT("Enable timer"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer2->Add( timerEnableButton, 0, wxALL, 5 );
    bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
    this->SetSizer( bSizer1 );
    this->Layout();
    timer.SetOwner( this, wxID_ANY );
    this->Centre( wxBOTH );
    timerSlider->Connect( wxEVT_SLIDER, wxCommandEventHandler( MainFrame::OnTimerSlider ), NULL, this );
    timerEnableButton->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnTimerEnableButtonClick ), NULL, this );
    this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( MainFrame::OnTimer ) );
  }
  virtual ~MainFrame()
  {
    timerSlider->Disconnect( wxEVT_SLIDER, wxCommandEventHandler( MainFrame::OnTimerSlider ), NULL, this );
    timerEnableButton->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnTimerEnableButtonClick ), NULL, this );
    this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( MainFrame::OnTimer ) );
  }
};

class demoApp: public wxApp
{
  MainFrame *frame = nullptr;
public:
  demoApp();
  virtual ~demoApp()
  {
  }
  virtual bool OnInit() override;
};

IMPLEMENT_APP(demoApp)
//#include <ApplicationServices/ApplicationServices.h>
demoApp::demoApp()
{
  //ProcessSerialNumber PSN;
  //GetCurrentProcess(&PSN);
  //TransformProcessType(&PSN,kProcessTransformToForegroundApplication);
}
bool demoApp::OnInit()
{
  frame = new MainFrame(nullptr);
  frame->Show();
  SetTopWindow(frame);
  SetExitOnFrameDelete(true);
  return true;
}
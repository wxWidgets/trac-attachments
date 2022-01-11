#include <wx/wx.h>
#include <wx/filepicker.h>

class MyApp: public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxFrame *frame = new wxFrame(NULL, wxID_ANY, "");
    wxButton *button = new wxButton(frame, wxID_ANY);
    wxFileButton *file_button = new wxFileButton(frame, wxID_ANY);

    // Test ordinary button
    button->Enable(false);
    button->SetFont(button->GetFont().Bold());
    button->SetLabel("other");

    // Test wxFileButton
    // Every line cause some error messages in stderr
    file_button->Enable(false);
    file_button->SetFont(file_button->GetFont().Bold());
    // file_button->SetLabel("some"); // Not fixed by patch

    frame->Close();
    return true;
}

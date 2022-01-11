bool MyApp::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;

    // create the main application window
    MyFrame *frame = new MyFrame("Minimal wxWidgets App");

    wxPanel *panel = new wxPanel(frame);
    wxCheckBox* checkbox = new wxCheckBox(panel, -1, _T("Initial label.\n"), wxDefaultPosition);

	wxString labelText = "&Some long text or other that should be wrapped.";
	int width = 0;
	int height = 0;

	// foreground color causes owner drawn mode
	checkbox->SetForegroundColour(*wxBLUE);

	checkbox->GetTextExtent(labelText, &width, &height);
	checkbox->SetLabel(labelText + wxT("\n"));
	// force wrapping
	checkbox->SetSize(width/3, height*5);

	frame->Show(true);


	return true;
}
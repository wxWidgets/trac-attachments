void DictFrame::onConvertText(wxCommandEvent& event)
{
  // Get the input file.
  wxFileDialog fd(this, "Select ASCII Dictionary", "", "",
                  "Text Files (*.txt)|*.txt|All Files (*.*)|*.*",
                  wxOPEN | wxHIDE_READONLY);
  if (fd.ShowModal() != wxID_OK)
  {
    return;
  }

  // Get the file they chose.
  wxString inFile = fd.GetPath();

  // Get the output file.
  fd.SetMessage("Save XML Dictionary As...");
  fd.SetWildcard("XML Files (*.xml)|*.xml");
  fd.SetStyle(wxSAVE | wxOVERWRITE_PROMPT);
  if (fd.ShowModal() != wxID_OK)
  {
    return;
  }

  // Get the output file.
  wxString outFile = fd.GetPath();
}


 	  	 

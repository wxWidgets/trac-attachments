Index: src/generic/dbgrptg.cpp
===================================================================
RCS file: /pack/cvsroots/wxwidgets/wxWidgets/src/generic/dbgrptg.cpp,v
retrieving revision 1.12
diff -u -r1.12 dbgrptg.cpp
--- src/generic/dbgrptg.cpp	2005/07/21 16:22:28	1.12
+++ src/generic/dbgrptg.cpp	2006/05/19 20:47:46
@@ -299,67 +299,79 @@
                               wxDEFAULT_DIALOG_STYLE | wxTHICK_FRAME),
                      m_dbgrpt(dbgrpt)
 {
+    // Borrowed from CreateTextSizer but adapted.
+    int widthMax = 450;
+    const bool is_pda = wxSystemSettings::GetScreenType() <= wxSYS_SCREEN_PDA;
+    if (is_pda)
+    {
+        widthMax = wxSystemSettings::GetMetric( wxSYS_SCREEN_X ) - 25;
+    }
+
     // upper part of the dialog: explanatory message
     wxString msg;
     msg << _("A debug report has been generated in the directory\n")
         << _T('\n')
         << _T("             \"") << dbgrpt.GetDirectory() << _T("\"\n")
         << _T('\n')
-        << _("The report contains the files listed below. If any of these files contain private information,\nplease uncheck them and they will be removed from the report.\n")
+        << _("The report contains the files listed below. If any of these files contain private information, please uncheck them and they will be removed from the report.\n")
         << _T('\n')
-        << _("If you wish to suppress this debug report completely, please choose the \"Cancel\" button,\nbut be warned that it may hinder improving the program, so if\nat all possible please do continue with the report generation.\n")
+        << _("If you wish to suppress this debug report completely, please choose the \"Cancel\" button, but be warned that it may hinder improving the program, so if at all possible please do continue with the report generation.\n")
         << _T('\n')
-        << _("              Thank you and we're sorry for the inconvenience!\n")
-        << _T("\n\n"); // just some white space to separate from other stuff
+        << _("Thank you and we're sorry for the inconvenience!\n");
+    
+    wxBoxSizer * sizerTop = new wxBoxSizer(wxVERTICAL);
+    SetSizer(sizerTop);
+
+    wxStaticBox * boxPreview = new wxStaticBox(this, wxID_ANY, _("Debug report preview:"));
+    wxStaticBoxSizer * sizerPreview = new wxStaticBoxSizer(boxPreview, wxVERTICAL);
+    sizerTop->Add(sizerPreview, 0, wxGROW|wxALL, 5);
 
-    const wxSizerFlags flagsFixed(SizerFlags(0));
-    const wxSizerFlags flagsExpand(SizerFlags(1));
-    const wxSizerFlags flagsExpand2(SizerFlags(2));
+    wxStaticText * previewText = new wxStaticText( this, wxID_ANY, msg, wxDefaultPosition, wxDefaultSize, 0 );
+    previewText->Wrap(widthMax);
+    sizerPreview->Add(previewText, 0, wxGROW|wxALL|wxADJUST_MINSIZE, 5);
 
-    wxSizer *sizerPreview =
-        new wxStaticBoxSizer(wxVERTICAL, this, _("&Debug report preview:"));
-    sizerPreview->Add(CreateTextSizer(msg), SizerFlags(0).Centre());
+    wxBoxSizer * sizerFiles = new wxBoxSizer(wxHORIZONTAL);
+    sizerPreview->Add(sizerFiles, 1, wxGROW|wxALL, 5);
 
-    // ... and the list of files in this debug report with buttons to view them
-    wxSizer *sizerFileBtns = new wxBoxSizer(wxVERTICAL);
-    sizerFileBtns->AddStretchSpacer(1);
-    sizerFileBtns->Add(new wxButton(this, wxID_VIEW_DETAILS, _T("&View...")),
-                        wxSizerFlags().Border(wxBOTTOM));
-    sizerFileBtns->Add(new wxButton(this, wxID_OPEN, _T("&Open...")),
-                        wxSizerFlags().Border(wxTOP));
-    sizerFileBtns->AddStretchSpacer(1);
+    m_checklst = new wxCheckListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_SINGLE );
+    sizerFiles->Add(m_checklst, 1, wxGROW|wxALL, 5);
 
-    m_checklst = new wxCheckListBox(this, wxID_ANY);
+    wxBoxSizer * sizerBtns = new wxBoxSizer(wxVERTICAL);
+    sizerFiles->Add(sizerBtns, 0, wxGROW|wxALL, 5);
 
-    wxSizer *sizerFiles = new wxBoxSizer(wxHORIZONTAL);
-    sizerFiles->Add(m_checklst, flagsExpand);
-    sizerFiles->Add(sizerFileBtns, flagsFixed);
+    wxButton * viewButton = new wxButton( this, wxID_VIEW_DETAILS, _("&View ..."), wxDefaultPosition, wxDefaultSize, 0 );
+    sizerBtns->Add(viewButton, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
 
-    sizerPreview->Add(sizerFiles, flagsExpand2);
+    wxButton * editButton = new wxButton( this, wxID_OPEN, _("&Open ..."), wxDefaultPosition, wxDefaultSize, 0 );
+    sizerBtns->Add(editButton, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
 
+    wxStaticBox * boxNotes = new wxStaticBox(this, wxID_ANY, _("Notes:"));
+    wxStaticBoxSizer * sizerNotes = new wxStaticBoxSizer(boxNotes, wxVERTICAL);
+    sizerTop->Add(sizerNotes, 2, wxGROW|wxALL, 5);
 
-    // lower part of the dialog: notes field
-    wxSizer *sizerNotes = new wxStaticBoxSizer(wxVERTICAL, this, _("&Notes:"));
+    wxStaticText * notesText = new wxStaticText( this, wxID_ANY, _("If you have any additional information pertaining to this bug report, please enter it here and it will be joined to it:"), wxDefaultPosition, wxDefaultSize, 0 );
+    notesText->Wrap(widthMax);
+    sizerNotes->Add(notesText, 0, wxGROW|wxALL|wxADJUST_MINSIZE, 5);
 
-    msg = _("If you have any additional information pertaining to this bug\nreport, please enter it here and it will be joined to it:");
+    m_notes = new wxTextCtrl( this, wxID_ANY, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
+    sizerNotes->Add(m_notes, 1, wxGROW|wxALL, 5);
 
-    m_notes = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
-                             wxDefaultPosition, wxDefaultSize,
-                             wxTE_MULTILINE);
+    wxStdDialogButtonSizer * defaultButtons = new wxStdDialogButtonSizer;
 
-    sizerNotes->Add(CreateTextSizer(msg), flagsFixed);
-    sizerNotes->Add(m_notes, flagsExpand);
+    sizerTop->Add(defaultButtons, 0, wxALIGN_RIGHT|wxALL, 5);
+    wxButton * okButton = new wxButton( this, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
+    defaultButtons->AddButton(okButton);
 
+    wxButton * cancelButton = new wxButton( this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
+    defaultButtons->AddButton(cancelButton);
 
-    wxSizer *sizerTop = new wxBoxSizer(wxVERTICAL);
-    sizerTop->Add(sizerPreview, flagsExpand2);
-    sizerTop->AddSpacer(5);
-    sizerTop->Add(sizerNotes, flagsExpand);
-    sizerTop->Add(CreateStdDialogButtonSizer(wxOK | wxCANCEL), flagsFixed);
+    defaultButtons->Realize();
 
-    SetSizerAndFit(sizerTop);
+    GetSizer()->Fit(this);
+    GetSizer()->SetSizeHints(this);
     Layout();
     CentreOnScreen();
+
 }
 
 // ----------------------------------------------------------------------------
@@ -382,6 +394,10 @@
             m_files.Add(name);
         }
     }
+
+    m_checklst->InvalidateBestSize();
+    m_checklst->SetMinSize(m_checklst->GetBestFittingSize());
+    Layout();
 
     return true;
 }

 	  	 

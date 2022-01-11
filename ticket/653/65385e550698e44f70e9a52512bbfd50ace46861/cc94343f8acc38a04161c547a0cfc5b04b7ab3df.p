Index: samples/controls/controls.cpp
===================================================================
RCS file: /pack/cvsroots/wxwidgets/wxWidgets/samples/controls/controls.cpp,v
retrieving revision 1.233
diff -u -r1.233 controls.cpp
--- samples/controls/controls.cpp	2005/08/17 13:13:42	1.233
+++ samples/controls/controls.cpp	2006/05/12 11:23:14
@@ -790,7 +790,7 @@
     m_combo = new MyComboBox( panel, ID_COMBO, _T("This"),
                               wxPoint(20,25), wxSize(120, wxDefaultCoord),
                               5, choices,
-                              wxCB_READONLY | wxPROCESS_ENTER);
+                              wxCB_DROPDOWN | wxPROCESS_ENTER);
     m_combo->SetBackgroundColour(*wxBLUE);
 
     (void)new wxButton( panel, ID_COMBO_SEL_NUM, _T("Select #&2"), wxPoint(180,30), wxSize(140,30) );

 	  	 

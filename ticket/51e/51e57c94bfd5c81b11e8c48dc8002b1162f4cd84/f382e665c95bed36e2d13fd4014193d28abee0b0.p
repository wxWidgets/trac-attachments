Index: combo.cpp
===================================================================
RCS file: /pack/cvsroots/wxwidgets/wxWidgets/samples/combo/combo.cpp,v
retrieving revision 1.2
diff -u -r1.2 combo.cpp
--- combo.cpp	2006/05/09 16:18:09	1.2
+++ combo.cpp	2006/05/15 18:32:55
@@ -706,7 +706,7 @@
                      wxALIGN_CENTER_VERTICAL|wxRIGHT|wxEXPAND, border );
 
     odc = new wxOwnerDrawnComboBox(panel,wxID_ANY,wxEmptyString,
-                                   wxDefaultPosition, wxDefaultSize,
+                                   wxDefaultPosition, wxSize(64,-1)/*wxDefaultSize*/,
                                    arrItems,
                                    wxCB_SORT // wxNO_BORDER|wxCB_READONLY
                                   );
@@ -715,7 +715,7 @@
 
     odc->SetValue(wxT("Dot Dash"));
 
-    groupSizer->Add( odc, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxALL, border );
+    groupSizer->Add( odc, 1, wxALIGN_CENTER_VERTICAL|wxALL, border );
 
     //
     // Readonly ODComboBox
@@ -762,7 +762,7 @@
                      wxALIGN_CENTER_VERTICAL|wxRIGHT|wxEXPAND, border );
 
     cb = new wxComboBox(panel,wxID_ANY,wxEmptyString,
-                        wxDefaultPosition, wxDefaultSize,
+                        wxDefaultPosition, wxSize(64,-1) /*wxDefaultSize*/,
                         arrItems,
                         wxCB_SORT // wxNO_BORDER|wxCB_READONLY
                        );
@@ -771,7 +771,7 @@
 
     cb->SetValue(wxT("Dot Dash"));
 
-    groupSizer->Add( cb, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxALL, border );
+    groupSizer->Add( cb, 1, wxALIGN_CENTER_VERTICAL|wxALL, border );
 
     //
     // Readonly wxComboBox

 	  	 

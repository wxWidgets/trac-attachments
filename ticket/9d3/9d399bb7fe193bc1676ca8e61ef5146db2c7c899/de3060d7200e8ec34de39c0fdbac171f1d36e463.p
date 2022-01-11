Index: odcombo.cpp
===================================================================
--- odcombo.cpp	(revision 1040)
+++ odcombo.cpp	(working copy)
@@ -688,7 +688,8 @@
 
     m_popupInterface->Clear();
 
-    GetTextCtrl()->SetValue(wxEmptyString);
+    if (GetTextCtrl())
+        GetTextCtrl()->SetValue(wxEmptyString);
 }
 
 void wxOwnerDrawnComboBox::Delete(int n)

 	  	 

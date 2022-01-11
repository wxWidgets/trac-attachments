Index: odcombo.cpp
===================================================================
--- odcombo.cpp	(revision 1080)
+++ odcombo.cpp	(working copy)
@@ -419,6 +419,7 @@
 
     m_clientDatas.SetCount(n+1,NULL);
     m_clientDatas[n] = clientData;
+    CheckWidth(n);
 }
 
 void* wxVListBoxComboPopup::GetItemClientData(int n) const

 	  	 

Index: odcombo.cpp
===================================================================
--- odcombo.cpp	(revision 1005)
+++ odcombo.cpp	(working copy)
@@ -559,6 +559,7 @@
                                            const wxString& name)
     : wxComboControl()
 {
+    m_popupInterface=NULL;
     Init();
 
     Create(parent,id,value,pos,size,choices,style, validator, name);

 	  	 

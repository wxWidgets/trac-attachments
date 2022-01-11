Index: src/gtk/filedlg.cpp
===================================================================
RCS file: /pack/cvsroots/wxwidgets/wxWidgets/src/gtk/filedlg.cpp,v
retrieving revision 1.71
diff -u -r1.71 filedlg.cpp
--- src/gtk/filedlg.cpp	2006/04/25 14:36:54	1.71
+++ src/gtk/filedlg.cpp	2006/05/08 20:08:12
@@ -177,6 +177,8 @@
                        ok_btn_stock, GTK_RESPONSE_ACCEPT,
                        NULL);
 
+        gtk_dialog_set_default_response(GTK_DIALOG(m_widget),GTK_RESPONSE_ACCEPT);
+
         if ( style & wxMULTIPLE )
             gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(m_widget), true);
 

 	  	 

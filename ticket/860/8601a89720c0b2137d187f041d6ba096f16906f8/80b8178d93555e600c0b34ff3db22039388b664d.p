=== include/wx/filedlg.h
==================================================================
--- include/wx/filedlg.h	(revision 572)
+++ include/wx/filedlg.h	(local)
@@ -30,7 +30,8 @@
     wxFD_OVERWRITE_PROMPT  = 0x0004,
     wxFD_FILE_MUST_EXIST   = 0x0010,
     wxFD_MULTIPLE          = 0x0020,
-    wxFD_CHANGE_DIR        = 0x0040
+    wxFD_CHANGE_DIR        = 0x0040,
+    wxFD_PREVIEW           = 0x0080
 };
 
 #if WXWIN_COMPATIBILITY_2_6
=== src/gtk/filedlg.cpp
==================================================================
--- src/gtk/filedlg.cpp	(revision 572)
+++ src/gtk/filedlg.cpp	(local)
@@ -109,7 +109,34 @@
 }
 }
 
+extern "C" {
+static void gtk_filedialog_update_preview_callback(GtkFileChooser *chooser,
+                                                   gpointer user_data)
+{
+#if GTK_CHECK_VERSION(2,4,0)
+    GtkWidget *preview;
+    char *filename;
+    GdkPixbuf *pixbuf = NULL;
+    gboolean have_preview;
+    
+    preview = GTK_WIDGET (user_data);
+    filename = gtk_file_chooser_get_preview_filename (chooser);
+    if (!filename)
+        return;
 
+    pixbuf = gdk_pixbuf_new_from_file_at_size (filename, 128, 128, NULL);
+    have_preview = (pixbuf != NULL);
+    g_free (filename);
+    
+    gtk_image_set_from_pixbuf (GTK_IMAGE (preview), pixbuf);
+    if (pixbuf)
+        g_object_unref (pixbuf);
+    
+    gtk_file_chooser_set_preview_widget_active (chooser, have_preview);
+#endif
+}
+}
+
 //-----------------------------------------------------------------------------
 // wxFileDialog
 //-----------------------------------------------------------------------------
@@ -224,6 +251,18 @@
                 gtk_file_chooser_set_current_folder( GTK_FILE_CHOOSER(m_widget),
                     wxConvFileName->cWX2MB(defaultDir) );
         }
+
+#if GTK_CHECK_VERSION(2,4,0)
+        if ((style & wxFD_PREVIEW) && !gtk_check_version(2,4,0))
+        {
+            GtkWidget *previewImage;
+            previewImage = gtk_image_new();
+            gtk_file_chooser_set_preview_widget(GTK_FILE_CHOOSER(m_widget), previewImage);
+            g_signal_connect (m_widget, "update-preview",
+                G_CALLBACK (gtk_filedialog_update_preview_callback), previewImage);
+        }
+#endif
+
     }
     else
         wxGenericFileDialog::Create( parent, message, defaultDir, defaultFileName, wildCard, style, pos );

 	  	 

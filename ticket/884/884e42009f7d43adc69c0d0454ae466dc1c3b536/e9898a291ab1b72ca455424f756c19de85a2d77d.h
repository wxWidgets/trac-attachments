diff --git a/interface/wx/filename.h b/interface/wx/filename.h
index c3d247b..940e28f 100644
--- a/interface/wx/filename.h
+++ b/interface/wx/filename.h
@@ -421,34 +421,43 @@ public:
     */
     void ClearExt();
 
-    //@{
+
     /**
         Returns a temporary file name starting with the given @e prefix.
-        If the @a prefix is an absolute path, the temporary file is created in this
-        directory, otherwise it is created in the default system directory for the
-        temporary files or in the current directory.
+        If @a prefix is an absolute path and ends in a separator, the
+        temporary file is created in this directory; if it is an absolute
+        filepath or there is no separator, the temporary file is created in its
+        path, with the 'name' segment prepended to the temporary filename;
+        otherwise it is created in the default system directory for temporary
+        files or in the current directory.
 
         If the function succeeds, the temporary file is actually created.
-        If @a fileTemp is not @NULL, this file will be opened using the name of
-        the temporary file. When possible, this is done in an atomic way ensuring that
-        no race condition occurs between the temporary file name generation and opening
-        it which could often lead to security compromise on the multiuser systems.
-        If @a fileTemp is @NULL, the file is only created, but not opened.
+        If @a fileTemp is not @NULL, this wxFile will be opened using the name of
+        the temporary file. Where possible this is done in an atomic way to ensure that
+        no race condition occurs between creating the temporary file name and opening
+        it, which might lead to a security compromise on multiuser systems.
+        If @a fileTemp is @NULL, the file is created but not opened.
         Under Unix, the temporary file will have read and write permissions for the
-        owner only to minimize the security problems.
+        owner only, to minimize security problems.
 
         @param prefix
-            Prefix to use for the temporary file name construction
+            Location to use for the temporary file name construction. If @a prefix
+            is a directory it must have a terminal separator
         @param fileTemp
-            The file to open or @NULL to just get the name
+            The file to open, or @NULL just to get the name
 
-        @return The full temporary file name or an empty string on error.
+        @return The full temporary filepath, or an empty string on error.
     */
     static wxString CreateTempFileName(const wxString& prefix,
                                        wxFile* fileTemp = NULL);
+
+    /**
+        This is the same as CreateTempFileName(const wxString &prefix, wxFile *fileTemp)
+        but takes a wxFFile parameter instead of wxFile.
+    */
     static wxString CreateTempFileName(const wxString& prefix,
                                        wxFFile* fileTemp = NULL);
-    //@}
+
 
     /**
         Returns @true if the directory with this name exists.

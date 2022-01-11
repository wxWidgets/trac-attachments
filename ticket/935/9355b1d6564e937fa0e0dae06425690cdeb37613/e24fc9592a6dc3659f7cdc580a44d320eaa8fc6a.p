Index: src/common/debugrpt.cpp
===================================================================
RCS file: /pack/cvsroots/wxwidgets/wxWidgets/src/common/debugrpt.cpp,v
retrieving revision 1.19
diff -u -r1.19 debugrpt.cpp
--- src/common/debugrpt.cpp	2005/07/21 16:19:39	1.19
+++ src/common/debugrpt.cpp	2006/05/19 21:35:32
@@ -556,10 +556,9 @@
 
 bool wxDebugReport::DoProcess()
 {
-    wxString msg = _("*** A debug report has been generated\n");
-    msg += wxString::Format(_("*** It can be found in \"%s\"\n"),
+    wxString msg = wxString::Format(_("A debug report has been generated. It can be found in\n\t\"%s\"\n\n"),
                             GetDirectory().c_str());
-    msg += _("*** And includes the following files:\n");
+    msg += _("And includes the following files:\n");
 
     wxString name, desc;
     const size_t count = GetFilesCount();

 	  	 

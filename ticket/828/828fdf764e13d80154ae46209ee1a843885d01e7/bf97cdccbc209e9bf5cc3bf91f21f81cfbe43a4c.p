Index: src/common/combo.cpp
===================================================================
--- src/common/combo.cpp	(revision 1021)
+++ src/common/combo.cpp	(working copy)
@@ -716,7 +716,7 @@
                                 // processed by looking at ancestors to see if they have
                                 // wxTAB_TRAVERSAL. The navigation event is then sent to
                                 // the wrong window.
-                                wxTE_PROCESS_TAB |
+                                wxTE_PROCESS_TAB | wxTE_PROCESS_ENTER |
                                 extraStyle,
                                 validator);
 

 	  	 

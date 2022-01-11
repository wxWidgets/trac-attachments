Index: src/unix/dlunix.cpp
===================================================================
RCS file: /pack/cvsroots/wxwidgets/wxWidgets/src/unix/dlunix.cpp,v
retrieving revision 1.11
diff -u -r1.11 dlunix.cpp
--- src/unix/dlunix.cpp	2005/04/19 12:38:24	1.11
+++ src/unix/dlunix.cpp	2006/05/19 18:36:50
@@ -373,7 +373,6 @@
             else if ( pathCur == pathNew )
             {
                 // continuation of the same module
-                wxASSERT_MSG( start == endCur, _T("hole in /proc/self/maps?") );
                 endCur = end;
             }
             else // end of the current module

 	  	 

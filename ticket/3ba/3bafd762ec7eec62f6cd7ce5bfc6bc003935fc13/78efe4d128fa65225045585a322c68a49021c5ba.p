Index: samples/widgets/widgets.cpp
===================================================================
RCS file: /pack/cvsroots/wxwidgets/wxWidgets/samples/widgets/widgets.cpp,v
retrieving revision 1.42
diff -u -r1.42 widgets.cpp
--- samples/widgets/widgets.cpp	2006/05/04 15:50:09	1.42
+++ samples/widgets/widgets.cpp	2006/05/05 16:56:57
@@ -525,7 +525,7 @@
         return;
 
     s_tip = dialog.GetValue();
-    s_tip.Replace("\\n", "\n");
+    s_tip.Replace(_T("\\n"), _T("\n"));
 
     WidgetsPage *page = wxStaticCast(m_book->GetCurrentPage(), WidgetsPage);
     page->GetWidget()->SetToolTip(s_tip);

 	  	 

--- window-o.cpp	2007-09-27 11:34:17.000000000 +0200
+++ window.cpp	2007-09-27 11:33:53.000000000 +0200
@@ -2906,7 +2906,7 @@
 
     int dx = 0;
     int dy = 0;
-    if (m_parent && m_parent->m_wxwindow)
+    if (!IsTopLevel() && m_parent && m_parent->m_wxwindow)
     {
         GtkPizza *pizza = GTK_PIZZA(m_parent->m_wxwindow);
         dx = gtk_pizza_get_xoffset( pizza );

 	  	 

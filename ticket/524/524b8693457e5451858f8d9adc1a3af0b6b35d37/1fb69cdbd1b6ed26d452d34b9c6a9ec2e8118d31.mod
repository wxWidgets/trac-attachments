--- C:/Users/raana_000/Desktop/string.cpp	Fri Jul 21 13:05:32 2017
+++ C:/Users/raana_000/Desktop/mystring.cpp	Fri Jul 21 13:13:43 2017
@@ -1553,15 +1553,35 @@
   return *this;
 }
 
-wxString& wxString::MakeCapitalized()
+inline int wxSafeIsspace(wxChar ch) { return (ch < 127) && wxIsspace(ch); }
+
+wxString& wxString::MakeCapitalized(bool multi)
 {
+    bool toUp = true;
     const iterator en = end();
     iterator it = begin();
+    
     if ( it != en )
-    {
-        *it = (wxChar)wxToupper(*it);
-        for ( ++it; it != en; ++it )
-            *it = (wxChar)wxTolower(*it);
+    {   
+        for ( ; it != en; ++it )
+        {
+            if (! wxSafeIsspace(*it) )
+            {
+                if (toUp)
+                {
+                    *it = (wxChar)wxToupper(*it);
+                    toUp = false;
+                }
+                else
+                {
+                    *it = (wxChar)wxTolower(*it);
+                }
+            }
+            else if ( multi )
+            {
+                toUp = true;
+            }
+        }
     }
 
     return *this;
@@ -1577,7 +1597,7 @@
 // this may fail to detect some spaces (I don't know if Unicode doesn't have
 // space-like symbols somewhere except in the first 128 chars), it is arguably
 // still better than trimming away accented letters
-inline int wxSafeIsspace(wxChar ch) { return (ch < 127) && wxIsspace(ch); }
+//inline int wxSafeIsspace(wxChar ch) { return (ch < 127) && wxIsspace(ch); } // moved before MakeCapitalized(bool multi)
 
 // trims spaces (in the sense of isspace) from left or right side
 wxString& wxString::Trim(bool bFromRight)

--- C:/Users/raana_000/Desktop/string.h	Fri Jul 21 13:05:33 2017
+++ C:/Users/raana_000/Desktop/mystring.h	Fri Jul 21 17:15:45 2017
@@ -2133,10 +2133,15 @@
   wxString Lower() const { return wxString(*this).MakeLower(); }
       // convert the first character to the upper case and the rest to the
       // lower one, return the modified string itself
-  wxString& MakeCapitalized();
+
+  wxString& MakeCapitalized(bool multi=false);
+      // When multi==false, behaviour is unchanged from original version:
       // convert the first character to the upper case and the rest to the
-      // lower one, return the copy of the string
-  wxString Capitalize() const { return wxString(*this).MakeCapitalized(); }
+      // lower one, returns the copy of the string
+      // When multi==true, first character of each word is converted to upper case
+      // returns the copy of the string
+
+  wxString Capitalize(bool multi = false) const { return wxString(*this).MakeCapitalized(multi); }
 
   // trimming/padding whitespace (either side) and truncating
       // remove spaces from left or from right (default) side

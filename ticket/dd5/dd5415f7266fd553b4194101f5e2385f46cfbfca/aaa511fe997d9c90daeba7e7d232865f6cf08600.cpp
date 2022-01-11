--- wxWidgets/branches/WX_2_8_BRANCH/src/xrc/xmlres.cpp	(revision 51218)
+++ wxWidgets/branches/WX_2_8_BRANCH/src/xrc/xmlres.cpp	(working copy)
@@ -1616,4 +1616,15 @@
 }
 
+wxChar *wxXmlResource::GetXRCID(int id)
+{
+    for (int i = 0; i < XRCID_TABLE_SIZE; i++) {
+        for (XRCID_record *rec = XRCID_Records[i]; rec; rec = rec->next) {
+            if (rec->id == id)
+                return rec->key;
+        }
+    }
+    return '\0';
+}
+
 static void CleanXRCID_Record(XRCID_record *rec)
 


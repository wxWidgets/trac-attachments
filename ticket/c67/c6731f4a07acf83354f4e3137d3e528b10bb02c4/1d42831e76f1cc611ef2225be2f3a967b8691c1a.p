Index: combo.cpp
===================================================================
--- src/common/combocmn.cpp	(revision 1063)
+++ src/common/combocmn.cpp	(working copy)
@@ -795,7 +795,7 @@
     int btnBorder; // border for button only
 
     if ( ( (m_iFlags & wxCC_BUTTON_OUTSIDE_BORDER) || m_blankButtonBg ) &&
-         m_btnSpacingX == 0 && m_btnWid == 0 && m_btnHei == 0 &&
+//         m_btnSpacingX == 0 && m_btnWid == 0 && m_btnHei == 0 &&
          (!m_bmpNormal.Ok() || m_blankButtonBg) )
     {
         buttonOutside = true;

 	  	 

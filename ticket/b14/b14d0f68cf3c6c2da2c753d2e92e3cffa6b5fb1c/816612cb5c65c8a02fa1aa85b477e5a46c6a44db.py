import wx
import sys
if sys.maxunicode <= 0xFFFF:
    print "Unicode: UCS-2 (max=%s)" % sys.maxunicode
else:
    print "Unicode: UCS-4 (max=%s)" % sys.maxunicode
print "Python %s" % sys.version.split("\n")[0]
sys.argv = [sys.argv[0], "ab\300c"]
app = wx.App()
app.MainLoop()


 	  	 

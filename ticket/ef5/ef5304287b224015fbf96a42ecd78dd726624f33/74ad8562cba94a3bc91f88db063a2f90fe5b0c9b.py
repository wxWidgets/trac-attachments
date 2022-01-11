# ActivePython 2.7.1.3 (ActiveState Software Inc.) based on
# Python 2.7.1 (r271:86832, Dec  5 2010, 12:04:08) [MSC v.1500 32 bit (Intel)] on win32
# Type "help", "copyright", "credits" or "license" for more information.
import platform
print platform.system()
# Windows
print platform.version()
# 6.1.7600
import wx
print wx.version()
# 2.9.1.1 (msw-unicode)
app=wx.App()
d = wx.DirDialog(None, "QWE", style=wx.DD_DEFAULT_STYLE, defaultPath="/tmp")
d.ShowModal()

# Causes a crash in python.exe
d = wx.DirDialog(None, "QWE", style=wx.DD_DEFAULT_STYLE, defaultPath="/")

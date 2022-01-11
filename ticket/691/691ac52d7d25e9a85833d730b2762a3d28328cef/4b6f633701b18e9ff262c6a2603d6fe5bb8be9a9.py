""" Run on a Windows XP system with wxPython 2.8.4.0,
    this code demonstrates that font.IsFixedWidth()
    always returns False, even if the given font is fixed-width
"""
import wx

app = wx.PySimpleApp()

e = wx.FontEnumerator()
e.EnumerateFacenames()
face_names = e.GetFacenames()

for face_name in face_names:
    font = wx.Font(10, wx.MODERN, wx.NORMAL, wx.BOLD, underline=False, face=face_name)
    print face_name.ljust(32), font.IsFixedWidth()


 	  	 

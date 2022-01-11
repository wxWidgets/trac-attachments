'''
Code showing bug in how wx.SearchCtrl handles the wx.TE_PROCESS_ENTER flag
For SearchCtrl, it correctly captures Enter, but also captures TAB, blocking
the transfer of focus to the next GUI element
If this flag is not set, TAB traversal works correctly

Note:
The standard wx.TextCtrl handles the wx.TE_PROCESS_ENTER flag correctly,
and doesn't interfere with TAB at all
'''
import wx

STYLE = wx.TE_PROCESS_ENTER
# Uncomment the next line to see that the SearchCtrl works correctly without this flag
#STYLE = 0

app = wx.PySimpleApp()
frame = wx.Frame(None, title='Tab Traversal with SearchCtrl')
panel = wx.Panel(frame)
search = wx.SearchCtrl(panel, style=STYLE)
text1 = wx.TextCtrl(panel, style=STYLE)
text2 = wx.TextCtrl(panel, style=STYLE)

sizer = wx.BoxSizer(wx.VERTICAL)
sizer.Add(search)
sizer.Add(text1)
sizer.Add(text2)
panel.SetSizer(sizer)

fsizer = wx.BoxSizer()
fsizer.Add(panel, 1, wx.EXPAND, 0)
frame.SetSizer(fsizer)

app.SetTopWindow(frame)
frame.Show()
frame.Centre()
frame.Raise()
app.MainLoop()

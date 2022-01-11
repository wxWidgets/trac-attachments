import wx
from wx.stc import StyledTextCtrl as STC

def fuk_me_up(stc, start, end, text):
    stc.SetTargetStart(start)
    stc.SetTargetEnd(end)
    stc.ReplaceTarget(text)
    

app = wx.App()

frame = wx.Frame(None)
stc = STC(frame)

stc.ReplaceTarget('Some\ninitial\ntext')
fuk_me_up(stc, 1, 0, 'more text') # Comment out this line

frame.Show()

app.MainLoop()

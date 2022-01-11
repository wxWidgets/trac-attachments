import wx
from wx.stc import StyledTextCtrl
import wx.stc 
import sys

repetition = 500
char = '8'
expected = char * repetition

def check_value(stc):
    value = stc.GetValue()
    if value != expected:
        print 'Expected:\n%r\n\nBut got:\n%r' % (expected, value)
        sys.exit(1)
    sys.exit(0)

def type_keys(stc):
    simulator = wx.UIActionSimulator()
    for n in range(repetition):
        simulator.KeyDown(ord(char), wx.MOD_NONE)
        simulator.KeyUp(ord(char), wx.MOD_NONE)

    wx.CallLater(1000, check_value, stc)

app = wx.PySimpleApp()
frame = wx.Frame(None)
stc = StyledTextCtrl(frame)
stc.SetWrapMode(wx.stc.STC_WRAP_WORD)
frame.Show()
wx.CallAfter(type_keys, stc)
app.MainLoop()

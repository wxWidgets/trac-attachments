#!/usr/bin/env python
import sys
import wx

class MyFrame(wx.Frame):

    def __init__(self):
        wx.Frame.__init__(self, None, -1)
        self.time_val = 600
        panel = wx.Panel(self, -1)
        self.slider = wx.Slider(panel, -1, self.time_val, 0, 600,
                                size=(200,-1), style=wx.SL_HORIZONTAL |
                                wx.SL_AUTOTICKS | wx.SL_LABELS)
        self.label = wx.StaticText(panel, -1, str(self.time_val))
        self.timer = wx.Timer(self)
        self.Bind(wx.EVT_TIMER, self.OnTimer, self.timer)
        self.timer.Start(1000)

    def OnTimer(self, event):
        self.time_val -= 1
        self.slider.SetValue(self.time_val)
        self.label.SetLabel(str(self.time_val))
        event.Skip()
    
def main():
    app = wx.PySimpleApp()
    frame = MyFrame()
    frame.Show(True)
    app.MainLoop()
    return 0

if __name__ == '__main__':
    sys.exit(main())

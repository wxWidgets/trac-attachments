#!/usr/bin/env python
import wx

class MyFrame (wx.Frame):
    def __init__ (self):
        wx.Frame.__init__(self, None, -1, title="Bind error test", size=(400, 400))
        self.panel = wx.Panel(self)

        self.button = wx.Button(self.panel, -1, label="A troublesome button.")

        # Incorrect syntax: swaps window and calback function.
        self.Bind(wx.EVT_BUTTON, self.button, self.OnClick)

        # Correct syntax:
        self.Bind(wx.EVT_BUTTON, self.OnClick, self.button)

    def OnClick (self, event):
        self.button.SetLabel("You clicked the troublesome button!")

if __name__=="__main__":
    app = wx.PySimpleApp(0)
    frame = MyFrame()
    frame.Show()
    app.MainLoop()


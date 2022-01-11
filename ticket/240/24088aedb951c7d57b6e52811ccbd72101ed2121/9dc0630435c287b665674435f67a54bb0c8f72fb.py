#!/usr/bin/python
import wx

class GUI(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, size=(480, 320))
        self.Bind(wx.EVT_PAINT, self.paint)
        
    def paint(self, event):
        dc = wx.PaintDC(self)
        dc.Clear()
        dc.DrawText("Hello, \t \t you!", 100, 100)

if __name__ == '__main__':
    app = wx.PySimpleApp()
    frame = GUI()
    frame.Show(True)
    app.MainLoop()
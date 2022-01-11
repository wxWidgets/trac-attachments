#!/usr/bin/python

import wx

class MyWindow(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1, "Test", size=(300,300))

class MyApp(wx.App):
    def OnInit(self):
        frame = MyWindow()
        sizer = wx.GridSizer(wx.HORIZONTAL)

        self.panel = wx.Panel(frame, -1, style=wx.BORDER_SUNKEN, size=(100,100))
        self.panel.SetBackgroundColour(wx.Colour(255,128,128))
        sizer.Add(self.panel, 1, wx.ALIGN_CENTER)
        button = wx.Button(frame, 1, "Delete")
        sizer.Add(button, 1, wx.ALIGN_CENTER)
        button.Bind(wx.EVT_BUTTON, self.do_del)

        frame.SetSizer(sizer)
        frame.Layout()

        self.SetTopWindow(frame)
        frame.Show(True)
        frame.Raise()
        return True

    def do_del(self, event):
        if self.panel:
            self.panel.Destroy()
            self.panel = None

app = MyApp()
app.MainLoop()

 	  	 

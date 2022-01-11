#!/usr/bin/env python

import wx

class MyFrame(wx.Frame):
    def __init__(self, *args, **kwds):
        kwds["style"] = wx.DEFAULT_FRAME_STYLE
        wx.Frame.__init__(self, *args, **kwds)

        # Create the spin control with default settings
        self.spin = wx.SpinCtrl(self, wx.ID_ANY)
        print "after SpinCtrl ctor, spin.GetValue() == %d" % self.spin.GetValue()

        # Init my internal value
        self._spin_value = 42

        sizer_1 = wx.BoxSizer(wx.VERTICAL)
        sizer_2 = wx.BoxSizer(wx.HORIZONTAL)
        sizer_2.Add(self.spin, 1, wx.EXPAND, 0)
        sizer_1.Add(sizer_2, 1, wx.EXPAND, 0)
        self.SetSizer(sizer_1)
        sizer_1.Fit(self)
        self.Layout()
        self.SetSize( (300, 300) ) 


        self.Bind(wx.EVT_SPINCTRL, self.on_spin_change, self.spin)
        self.Bind(wx.EVT_CLOSE, self.on_close)

        # Set the range. Under Windows, this fires self.on_spin_change.
        self.spin.SetRange(1, 100)


    def on_spin_change(self, event):
        print "on_spin_change: self.spin.GetValue() == %d" % self.spin.GetValue()

        self._spin_value = self.spin.GetValue()


    def on_close(self, event):
        print "Exiting, self._spin_value = %s" % self._spin_value
        self.Destroy()


if __name__ == "__main__":
    app = wx.PySimpleApp(0)
    frame_1 = MyFrame(None, wx.ID_ANY, "")
    app.SetTopWindow(frame_1)
    frame_1.Show()
    app.MainLoop()

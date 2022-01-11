#!/usr/bin/env python
# coding: UTF8

import wx
from wx.lib.masked.textctrl import TextCtrl

ID_MENU = wx.NewId()

class Absolute(wx.Frame):
    def __init__(self, title):
        wx.Frame.__init__(self, None, wx.ID_ANY, title, wx.DefaultPosition,
            wx.Size(450, 150))

        self.panel = wx.Panel(self)
        self.date = TextCtrl(self.panel, wx.ID_ANY, name="TCDate",
            pos=wx.Point(200, 10))

        if True:   # ----  either this
            self.date.SetAutoformat("EUDATEYYYYMMDD.")
        else:       # ----  or this
            self.date.SetDatestyle("YMD")
            self.date.SetFormatcodes("D")
            self.date.SetDescription("YYYY-MM-DD")
            self.date.SetMask("####-##-##")

        descr = wx.StaticText(self.panel, wx.ID_ANY, pos=(10, 40),
            label="Hit the combo:\n1 1 1 1 1 Left Left Backspace Right Right "
                "Left Backspace Right Right Up\n"
                "      or\n1 2 Tab Left Backspace Tab Up")

        self.date.Bind(wx.EVT_KEY_DOWN, self.OnKey)
        #self.date.Bind(wx.EVT_TEXT, self.FixOnText)

        self.date.SetFocus()

    def OnKey(self, event):
        print "self.date.GetValue(): %r" % self.date.GetValue()
        if event.GetKeyCode() == wx.WXK_ESCAPE:
            self.Close()
        event.Skip()

    def FixOnText(self, event):
        if len(self.date.GetValue()) == 9:
            self.date._SetValue(self.date.GetValue() + " ")
        event.Skip()


def main():
    app = wx.App()

    absolute = Absolute("TextCtrl - YMD")
    absolute.Show(True)
    app.MainLoop()


if __name__ == '__main__':
    main()

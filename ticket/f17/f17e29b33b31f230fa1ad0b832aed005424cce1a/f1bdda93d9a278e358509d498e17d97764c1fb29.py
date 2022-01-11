#! /usr/bin/env python3

import wx
import numpy as np

class MainFrame(wx.Frame):

    def __init__(self, parent, log):
        wx.Frame.__init__(self, parent, log, "MainFrame")
        p = wx.Panel(self, -1)
        box = wx.BoxSizer(wx.VERTICAL)
        self.is_red = True
        self.green = np.zeros((64, 64, 3), dtype=np.uint8)
        self.green[:, :, 1] = 255
        self.red = np.zeros((64, 64, 3), dtype=np.uint8)
        self.red[:, :, 0] = 255
        self.img = wx.Image(64, 64)
        self.img.SetData(self.red.tostring())
        self.staticbitmap = wx.StaticBitmap(p, -1, wx.Bitmap(self.img), style=wx.BORDER_RAISED)
        box.Add(self.staticbitmap, 0, wx.ALL, 5)
        box.Add(wx.Button(p, -1, 'Toggle'), 0, wx.ALL, 5)
        p.SetSizer(box)
        box.Fit(p)
        self.Fit()
        self.Bind(wx.EVT_BUTTON, self.on_button)

    def on_button(self, event):
        self.is_red = not self.is_red
        if self.is_red:
            self.img.SetData(self.red.tostring())
        else:
            self.img.SetData(self.green.tostring())
        self.staticbitmap.SetBitmap(wx.Bitmap(self.img))


def main():
    app = wx.App()
    MainFrame(None, -1).Show()
    return app.MainLoop()


if __name__ == '__main__':
    main()

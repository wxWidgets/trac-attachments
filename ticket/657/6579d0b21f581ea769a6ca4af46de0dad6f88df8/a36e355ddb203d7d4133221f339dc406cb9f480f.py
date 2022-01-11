#!/usr/bin/python

import wx

class Frame(wx.Frame):
    def __init__(self):
        super(Frame, self).__init__(None, wx.ID_ANY, 'Test')

        self.tbicon = wx.TaskBarIcon()
        self.tbicon.SetIcon(wx.Icon('taskcoach.png', wx.BITMAP_TYPE_PNG))

        self.Show()


if __name__ == '__main__':
    class App(wx.App):
        def OnInit(self):
            Frame()
            return True

    App(0).MainLoop()

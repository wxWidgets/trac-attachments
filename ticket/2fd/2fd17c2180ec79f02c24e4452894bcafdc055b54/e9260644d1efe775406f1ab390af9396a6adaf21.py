#!/usr/bin/env python
# coding: UTF8

import wx

ID_BUTTON = wx.NewId()


class Dialog(wx.Dialog):

    def __init__(self):
        wx.Dialog.__init__(self, None, -1, "Dialog")

        button = wx.Button(self, ID_BUTTON, "Show frame", pos=(10, 10), size=(80, 30))
        self.Bind(wx.EVT_BUTTON, self.OnButton, id=ID_BUTTON)

        self.ShowModal()
        self.Destroy()
        
    def OnButton(self, event):

        frame = Frame(self)
        frame.Show()
        frame.MakeModal(True)


class Frame(wx.Frame):
    def __init__(self, parent):
        wx.Frame.__init__(self, parent, -1, "Frame", wx.DefaultPosition)

        menubar = wx.MenuBar()
        file = wx.Menu()
        file.Append(wx.ID_EXIT, '&Quit')
        menubar.Append(file, '&File')
        self.SetMenuBar(menubar)

        self.Bind(wx.EVT_MENU, self.OnQuit, id=wx.ID_EXIT)
        self.Bind(wx.EVT_CLOSE, self.OnClose)
        self.Show()

    def OnQuit(self, event):
        self.Close()

    def OnClose(self, event):
        self.MakeModal(False)
        event.Skip()


app = wx.App()
#frame = Frame(None)
dialog = Dialog()
app.MainLoop()

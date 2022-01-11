#!/usr/bin/env python2.7
import wx

class FFrame(wx.Frame):
    def __init__(self, parent, *args, **kwargs):
        wx.Frame.__init__(self, parent, *args, **kwargs)
        menu = wx.Menu()
        
        menu.Append(id=10, text='Normal', kind=wx.ITEM_NORMAL)
        menu.Append(id=11, text='Radio 1', kind=wx.ITEM_RADIO)
        menu.Append(id=12, text='Radio 2', kind=wx.ITEM_RADIO)
        menu.Append(id=13, text='Radio 3', kind=wx.ITEM_RADIO)
        
        menu.Delete(10) # causes the first radio item to be wrongly checked
        
        menu.Check(13, True)
        
        self.PopupMenu(menu)
        
if __name__ == "__main__":
    app = wx.App()
    frame = FFrame(None)
    frame.Show()
    app.MainLoop()

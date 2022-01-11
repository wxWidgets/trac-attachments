

import wx

class Frame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1, "Menu Event", size=(200,100))
        menu = wx.Menu()
        menu.Append(101, "Exit")
        mb = wx.MenuBar()
        mb.Append(menu, "File")
        self.SetMenuBar(mb)
        wx.EVT_MENU(self, 101, self.OnDoExit)

    def OnDoExit(self, evt):
        print "evt", evt
        print "evt.GetEventObject", evt.GetEventObject()
        self.Close()


app = wx.PySimpleApp()
frame = Frame()
frame.Show()
app.MainLoop()

 	  	 

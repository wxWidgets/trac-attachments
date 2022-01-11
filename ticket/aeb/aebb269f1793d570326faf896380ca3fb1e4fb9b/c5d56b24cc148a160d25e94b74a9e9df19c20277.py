import sys
import wx


class ButtonBug(wx.Frame):
    def __init__(self, parent, id, **kwds):
        kwds['style'] = wx.MINIMIZE_BOX | wx.MAXIMIZE_BOX | wx.RESIZE_BORDER | wx.SYSTEM_MENU | wx.CAPTION
        wx.Frame.__init__(self, parent, id, "ButtonBug", **kwds)

        self.btnH = wx.Button(self, -1, "H\nH", size=(38,38))
        self.btnH.SetBackgroundColour((0,0,255))
        self.btnR = wx.Button(self, -1, "R\nR", size=(38,38))
 
        szrMain = wx.BoxSizer(wx.VERTICAL)
        szrMain.Add(self.btnH,0,wx.ALL,5)
        szrMain.Add(self.btnR,0,wx.ALL,5)
        self.SetAutoLayout(1)
        self.SetSizer(szrMain)
        szrMain.Fit(self)
        szrMain.SetSizeHints(self)
        self.Layout()
        self.Centre()
        return
        
app = wx.PySimpleApp()
frame = ButtonBug(None,-1)
frame.Show()
app.MainLoop()

 	  	 

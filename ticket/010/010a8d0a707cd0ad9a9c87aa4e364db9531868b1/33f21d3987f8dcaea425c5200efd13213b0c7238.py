
import wx
from cbscroll_xrc import xrcFRAME

class FRAME(xrcFRAME):
    def __init__(self):
        xrcFRAME.__init__(self, None)
        self.SPanel.SetVirtualSize(
            self.SPanel.GetSizer().GetMinSize())
        self.SPanel.SetScrollRate(20,20)


app = wx.App(False)
frm = FRAME()
frm.Show()
app.MainLoop()

 	  	 

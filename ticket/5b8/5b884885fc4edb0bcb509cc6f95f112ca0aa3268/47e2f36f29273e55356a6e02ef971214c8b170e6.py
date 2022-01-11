import wx
from random import randrange
import time

class MyFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, wx.ID_ANY, title='Testcase')
        
        self.textbox = wx.TextCtrl(self, wx.ID_ANY, style=wx.TE_MULTILINE)
        self.textbox.SetFont(wx.Font(pointSize=90, family=wx.DEFAULT,
            style=wx.FONTSTYLE_NORMAL, weight=wx.BOLD) )
        self.textbox.Bind(wx.EVT_CHAR, self.OnChar)

    def OnChar(self, evt):
        self.textbox.SetValue(self.textbox.GetValue()+u'\u2227')
        wx.CallAfter(self.changebg)
        
    def changebg(self):
        self.textbox.SetBackgroundColour( [wx.RED, wx.GREEN][randrange(0,2)] )
        self.textbox.Refresh()

        
if __name__ == '__main__':
    app=wx.App(False)
    myFrame = MyFrame()
    myFrame.Show()
    app.MainLoop()

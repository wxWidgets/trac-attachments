# -*- coding: utf-8 -*-
# Alignment bug, ALIGN_CENTER_VERTICAL doesn't center chinese text correctly on the mac
#        dc.DrawLabel(self.text, rect, self.align|wx.ALIGN_CENTER_VERTICAL)

import wx

class BugPanel(wx.Panel):
    def __init__(self, parent, text,align=0):
        wx.Panel.__init__(self, parent, -1, style=0)
        
        self.text = text
        self.align = align
        
        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.Bind(wx.EVT_ERASE_BACKGROUND, self.OnEraseBackground)
        
    def OnEraseBackground(self, event):
        pass

    def OnPaint(self, event):
        dc = wx.BufferedPaintDC(self)
        dc.SetBackground(wx.Brush(wx.WHITE))
        dc.Clear()
        rect = self.GetClientRect()
        dc.DrawLabel(self.text, rect, self.align|wx.ALIGN_CENTER_VERTICAL)
        
class MainFrame(wx.Frame):
    """
    This is the MainFrame.
    """
    def __init__(self, title):                
        wx.Frame.__init__(self, None, -1, title, pos=(150, 150), size=(400, 300))

        text = "他妈的"        
        pnl1 = BugPanel(self,text,wx.ALIGN_RIGHT)
        text = "TESTING"        
        pnl2 = BugPanel(self,text)
        
        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.Add(pnl1,1,wx.EXPAND|wx.ALL,border=10)
        sizer.Add(pnl2,1,wx.EXPAND|wx.ALL,border=10)
        self.SetSizer(sizer)
        self.Layout()
    
class MyApp(wx.App):
    def OnInit(self):
        frame = MainFrame("AlignBug")
        self.SetTopWindow(frame)
        frame.Show(True)
        return True

if __name__ == '__main__':
    app = MyApp(0)
    app.MainLoop()

# -*- coding: iso8859-1 -*-
import wx
import wx.aui
import os.path
import os

class BuggyFrame(wx.Frame):
    """This window fails when you try to drag the divisor to resize the panes"""
    def __init__(self, parent,id):
        wx.Frame.__init__(self, parent, id, u"Buggy Window",
                          style=wx.DEFAULT_FRAME_STYLE |
                                            wx.SUNKEN_BORDER |
                                            wx.CLIP_CHILDREN)

        self.fCaller=parent

        self._mgr = wx.aui.AuiManager()
        self._mgr.SetManagedWindow(self)

        self.pOne=wx.Panel(self,-1)
        self.pTwo=wx.Panel(self,-1)

        self._mgr.AddPane(self.pOne,
                  wx.aui.AuiPaneInfo().
                  Name(u"Panel One").Caption("Panel One").CenterPane())

        self._mgr.AddPane(self.pTwo,
                  wx.aui.AuiPaneInfo().
                  Name(u"Panel Two").Caption("Panel Two").CenterPane())
        self._mgr.Update()
        self.Bind(wx.EVT_CLOSE, self.OnClose)
        self.pOne.Bind(wx.EVT_PAINT, self.OnPaint)

    def OnClose(self, evt):
        if self.fCaller:
            self.Hide()
            self.fCaller.Show(True)
        else:
            self.Destroy()

    def OnPaint(self,evt):
        print "paint"
        dc=wx.PaintDC(self.pOne)
        penclr   = wx.Colour(0,   0, 139, 128) #Un azul
        brushclr = wx.Colour(  0,   0, 139,128)   # half transparent
        dc.SetPen(wx.Pen(penclr))
        dc.SetBrush(wx.Brush(brushclr))
        dc.DrawRectangle(0,0,100,100)



class MainFrame(wx.Frame):
    def __init__(self, parent, id):

        wx.Frame.__init__(self, parent, id, u"First Frame",
                          style=wx.DEFAULT_FRAME_STYLE |
                                            wx.SUNKEN_BORDER |
                                            wx.CLIP_CHILDREN)

        self.bSecond=wx.Button(self,-1,"Open Second Buggy Frame")
        self.pCanvas=wx.Panel(self,-1)

        s=wx.BoxSizer(wx.VERTICAL)
        s.Add(self.bSecond)
        s.Add(self.pCanvas)
        self.SetSizerAndFit(s)

        self.fSecond=BuggyFrame(self,-1)

        self.Bind(wx.EVT_BUTTON, self.OnButton)
        self.Bind(wx.EVT_PAINT, self.OnPaint)

    def OnButton(self, evt):
        self.fSecond.Show(True)
        self.Hide()

    def OnPaint(self,evt):
        dc=wx.PaintDC(self.pCanvas)
        penclr   = wx.Colour(0,   128, 0, 128) #Un azul
        brushclr = wx.Colour(  0,   128, 139,128)   # half transparent
        dc.SetPen(wx.Pen(penclr))
        dc.SetBrush(wx.Brush(brushclr))
        dc.DrawRectangle(0,0,100,100)



if __name__=="__main__":
    app=wx.PySimpleApp(useBestVisual=True)
    ven=MainFrame(None,-1)
    app.SetTopWindow(ven)

    ven.Show()

    app.MainLoop()

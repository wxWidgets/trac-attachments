import wx

class MyEditor(wx.App):
    def OnInit(self):
        frame = wx.Frame(None, -1, "Title")
        txt = wx.TextCtrl(frame, -1, "Hello.",
        style=wx.TE_MULTILINE|wx.TE_RICH2)

        f = wx.Font(pointSize=18, family=wx.MODERN,
        style=wx.NORMAL, weight=wx.NORMAL)
        print "Point Size as set:", f.GetPointSize()

        txt.SetStyle(0, 2, wx.TextAttr(font=f))

        attr = wx.TextAttr()
        txt.GetStyle(1, attr)
        print "Point Size as reported:", \
        attr.GetFont().GetPointSize()

        frame.Show()
        return True

app = MyEditor(0)
app.MainLoop()

 	  	 

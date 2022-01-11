import wx

class wxVis1(wx.Panel):
    def __init__(self, parent, id, label):
        wx.Panel.__init__(self, parent)

        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(wx.StaticText(self, -1, label), 0, wx.ALIGN_CENTER)

        self.Bind(wx.EVT_TIMER, self.OnTimer)
        self.Timer = wx.Timer(self)
        self.label = label
        
        self.Timer.Start(5000)

        print "Done Init!"

    def OnTimer(self, event):
        print "Label: %s, Is Visible: %s" % (self.label, self.IsShownOnScreen())
                


class wxN(wx.Notebook):
    def __init__(self, parent, id):
        wx.Notebook.__init__(self, parent, id, style=wx.BK_DEFAULT)

        a = wxVis1(self, -1, "Page A")
        self.AddPage(a, "Page A")

        b = wxVis1(self, -1, "Page B")
        self.AddPage(b, "Page B")
        


class wxTestFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, title = 'visibility test')

        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(wxN(self, -1), 0, wx.ALIGN_CENTER)


if __name__=="__main__":
    app = wx.PySimpleApp()

    frm = wxTestFrame()

    frm.Show()
    app.MainLoop()
    

 	  	 

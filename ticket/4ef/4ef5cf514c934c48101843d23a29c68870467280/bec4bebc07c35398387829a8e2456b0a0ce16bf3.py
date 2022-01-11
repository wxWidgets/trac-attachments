import wx

class TestFrame(wx.Frame):
    def __init__(self):
        """
        Main Test Frame
        """
        wx.Frame.__init__(self, None)

        p = wx.Panel(self)

        box = wx.BoxSizer(wx.HORIZONTAL)

        b1 = wx.Button(p, -1, "Dialog")
        self.Bind(wx.EVT_BUTTON, self.showDialog, id = b1.GetId())
        box.Add(b1, 0)

        b2 = wx.Button(p, -1, "Frame")
        self.Bind(wx.EVT_BUTTON, self.showFrame, id = b2.GetId())
        box.Add(b2, 0)

        p.SetSizer(box)
        self.Show()
        
    def showDialog(self, event):
        d = BugDialog()
        d.ShowModal()
        d.Destroy()
        
    def showFrame(self, event):
        BugFrame()
        
class BugFrame(wx.Frame):
    def __init__(self):
        """
        A simple Frame.
        Should get closed when ESC key is down (but it doesn't work in 2.7/2.8+)
        """
        wx.Frame.__init__(self, None)
        p = wx.Panel(self)
        
        b = wx.Button(p, -1, "Close")
        b.Bind(wx.EVT_BUTTON, self.OnClose)
        self.Bind(wx.EVT_CLOSE, self.OnClose)

        accelTable = wx.AcceleratorTable([(wx.ACCEL_NORMAL, wx.WXK_ESCAPE, b.GetId())])
        self.SetAcceleratorTable(accelTable)
        
        self.Show()
        
    def OnClose(self, event):
        print "closing BugFrame"
        self.Destroy()
        
class BugDialog(wx.Dialog):
    def __init__(self):
        """
        A simple Dialog.
        Should get closed when ESC key is down (but it doesn't work in 2.7/2.8+)
        """
        wx.Dialog.__init__(self, None, -1)
        
        outerbox = wx.BoxSizer( wx.VERTICAL)
        b = wx.Button(self, -1, "Close")
        b.Bind(wx.EVT_BUTTON, self.OnClose)
        outerbox.Add(b, 0)
            
        accelTable = wx.AcceleratorTable([(wx.ACCEL_NORMAL, wx.WXK_ESCAPE, b.GetId())])
        self.SetAcceleratorTable(accelTable)

        self.SetSizer(outerbox)

    def OnClose(self, event):
        print "closing BugDialog"
        self.EndModal(wx.ID_OK)
        
if __name__ == "__main__":
    app = wx.App("")
    frame = TestFrame()
    app.MainLoop()

 	  	 

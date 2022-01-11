import wx

class BugPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1, style=0)
      
        self.parent = parent
        sizer = wx.BoxSizer(wx.VERTICAL)
                
        self.test_window = wx.Panel(self,-1)
        self.test_window.SetBackgroundColour((0,0,0))
        
        sizer.Add(self.test_window, 1, wx.EXPAND)
        self.SetSizer(sizer)
        self.SetAutoLayout(True)
    
                
class MainFrame(wx.Frame):
    """
    This is the MainFrame.
    """
    def __init__(self, title):                
        wx.Frame.__init__(self, None, -1, title,
                          pos=(150, 150), size=(640, 480))

        self.nb = wx.Notebook(self,size=(640,480),style=wx.BORDER_DOUBLE)
        #self.nb = wx.Notebook(self,size=(640,480))
        self.pnl = BugPanel(self.nb)
        self.nb.AddPage(self.pnl,"Bug")        
        self.SetBackgroundColour((255,255,255))
        
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(self.nb,1,wx.EXPAND|wx.ALL,border=10)
        self.SetSizer(sizer)
        self.SetAutoLayout(True)
       
class MyApp(wx.App):
    def OnInit(self):
        frame = MainFrame("Template")
        self.SetTopWindow(frame)
        frame.Show(True)
        return True

if __name__ == '__main__':
    app = MyApp(0)
    app.MainLoop()


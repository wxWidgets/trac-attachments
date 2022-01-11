import wx
import flatnotebook as fnb

class BugPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1, style=wx.TAB_TRAVERSAL)#|wx.WANTS_CHARS)
      
        self.parent = parent
        sizer = wx.BoxSizer(wx.VERTICAL)
        self.SetBackgroundColour(wx.RED)
        
        self.test_window = wx.Panel(self,-1,style=wx.TAB_TRAVERSAL)
        self.test_window.SetBackgroundColour((0,0,255))
        
        test_sizer = wx.BoxSizer(wx.VERTICAL)
        
        st = wx.StaticText(self.test_window,-1,"Static Text!")
        test_sizer.Add(st,0,wx.ALL,border=10)
        st = wx.StaticText(self.test_window,-1,"Static Text!")
        test_sizer.Add(st,0,wx.ALL,border=10)
        
        self.test_window.SetSizer(test_sizer)
        self.test_window.Layout()
        sizer.Add(self.test_window, 1, wx.EXPAND|wx.ALL,border=10)
        
        self.SetSizer(sizer)
        self.Layout()
        
class MainFrame(wx.Frame):
    """
    This is the MainFrame.
    """
    def __init__(self, title):                
        wx.Frame.__init__(self, None, -1, title,
                          pos=(150, 150), size=(640, 480))

        #self.nb = fnb.FlatNotebook(self,size=(640,480))
        self.nb = wx.Notebook(self,size=(640,480))
        self.pnl = BugPanel(self.nb)
        self.nb.AddPage(self.pnl,"Bug")        
        self.pnl = BugPanel(self.nb)
        self.nb.AddPage(self.pnl,"Bug")        
        self.pnl = BugPanel(self.nb)
        self.nb.AddPage(self.pnl,"Bug")        
        
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(self.nb,1,wx.EXPAND|wx.ALL,border=10)
        self.SetSizer(sizer)
        self.Layout()
        self.timer = wx.Timer(self)
        self.Bind(wx.EVT_TIMER, self.onTimer)
        self.timer.Start(1000)
 
    def onTimer(self, evt):
        print 'Focused window:', wx.Window.FindFocus()
        
class MyApp(wx.App):
    def OnInit(self):
        frame = MainFrame("Template")
        self.SetTopWindow(frame)
        frame.Show(True)
        return True

if __name__ == '__main__':
    app = MyApp(0)
    app.MainLoop()


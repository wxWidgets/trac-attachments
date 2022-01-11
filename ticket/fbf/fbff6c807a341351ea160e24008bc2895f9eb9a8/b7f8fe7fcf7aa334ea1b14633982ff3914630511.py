
import wx

class frame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, title="Notebook with Sash test", size=(600,600))
        
        sz = wx.BoxSizer(wx.VERTICAL)
        
        self.splitter = splitter = wx.SplitterWindow(self)
        sz.Add(splitter, 1, wx.EXPAND)
        
        self.nb1 = wx.Notebook(splitter)
        self.nb2 = wx.Notebook(splitter)
        
        self.nb1.AddPage(wx.Panel(self.nb1), "panel on nb1")
        self.nb2.AddPage(wx.Panel(self.nb2), "panel on nb2")
        
        self.splitter.SplitHorizontally(self.nb1, self.nb2)        
        
        self.SetSizer(sz)

if __name__ == '__main__':
    a = wx.App(0)
    b = frame()
    b.Show(1)
    a.MainLoop()


 	  	 

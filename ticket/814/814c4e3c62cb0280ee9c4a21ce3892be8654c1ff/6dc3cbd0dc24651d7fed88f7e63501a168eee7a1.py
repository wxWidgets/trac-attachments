import wx 
 
class MainFrame(wx.Frame): 
    def __init__(self): 
        wx.Frame.__init__(self, None, -1, "Demonstration of wxTreeCtrl bug") 
        self.tree=wx.TreeCtrl(self,-1,style=wx.TR_HIDE_ROOT|wx.TR_DEFAULT_STYLE) 
        root = self.tree.AddRoot("") 
        longitem = self.tree.AppendItem(root, "Agriculture, environment and natural resources") 
        print self.tree.GetBoundingRect(longitem, True) 
        f = wx.TheFontList.FindOrCreateFont(12, wx.SWISS, wx.NORMAL, wx.NORMAL, False, "") 
        self.tree.SetItemFont(longitem,f) 
        print self.tree.GetBoundingRect(longitem, True) 
        self.tree.Show(1) 
  
if __name__ == "__main__": 
	app = wx.PySimpleApp() 
        frame = MainFrame() 
        frame.SetSize((400,200)) 
        frame.Show(1) 
        app.MainLoop() 
 

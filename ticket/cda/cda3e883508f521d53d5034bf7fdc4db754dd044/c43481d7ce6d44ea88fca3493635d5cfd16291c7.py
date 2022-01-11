import wx

class MainFrame(wx.Frame):
    """
    This is the MainFrame.
    """
    def __init__(self, title):                
        wx.Frame.__init__(self, None, -1, title,
                          pos=(150, 150), size=(640, 480))

        self.menuBar = wx.MenuBar()

        menu = wx.Menu() 
        menu.Append(wx.ID_NEW, "&New\tAlt-N", "New")
        self.Bind(wx.EVT_MENU,self.OnNew,id=wx.ID_NEW) 
        
        self.menuBar.Append(menu, "&File")
        self.SetMenuBar(self.menuBar)
        
        nb = wx.Notebook(self,size=(640,480),style=wx.BORDER_DOUBLE)
        #nb = wx.Notebook(self,size=(640,480))
        pnl = wx.Panel(nb)
        nb.AddPage(pnl,"1")        
        nb.AddPage(pnl,"2")        
        nb.AddPage(pnl,"3")        
        nb.AddPage(pnl,"4")        
        
        self.nb = nb

        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(nb,1,wx.EXPAND|wx.ALL,border=10)
        self.SetSizer(sizer)
        self.SetAutoLayout(True)
    
    def OnNew(self,event):
        print self.nb.GetSelection()
        print self.nb.ChangeSelection(1)
        
class MyApp(wx.App):
    def OnInit(self):
        frame = MainFrame("Template")
        self.SetTopWindow(frame)
        frame.Show(True)
        return True

if __name__ == '__main__':
    app = MyApp(0)
    app.MainLoop()


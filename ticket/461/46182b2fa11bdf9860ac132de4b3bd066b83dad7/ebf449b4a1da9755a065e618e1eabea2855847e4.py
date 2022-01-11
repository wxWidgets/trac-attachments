
import wx
import wx.grid as gridlib

class MyFrame(wx.Frame):
    def __init__(
            self, parent, ID, title, pos=wx.DefaultPosition,
            size=wx.DefaultSize, style=wx.DEFAULT_FRAME_STYLE
            ):

        wx.Frame.__init__(self, parent, ID, title, pos, size, style)
        panel = wx.Panel(self, -1)

        button1 = wx.Button(panel, wx.ID_ANY, "Close Me")
        button1.SetPosition((15, 15))
        button1.Bind(wx.EVT_BUTTON, self.OnCloseMe)

        button2 = wx.Button(panel,wx.ID_ANY, "Show selection")
        button2.SetPosition((110,15))
        button2.Bind(wx.EVT_BUTTON, self.OnShowSel)

        self.Bind(wx.EVT_CLOSE, self.OnCloseWindow)

        self.gg = gridlib.Grid(panel,wx.ID_ANY,pos=(15,50),size=(350,150))
        self.gg.CreateGrid(3,3)


    def OnCloseMe(self, event):
        self.Close(True)

    def OnCloseWindow(self, event):
        self.Destroy()

    def OnShowSel(self,evt):
        print 'Grid row selection',self.gg.GetSelectedRows()
        print 'Grid cell selection',self.gg.GetSelectedCells()
        print 'Grid column selection',self.gg.GetSelectedCols()

#---------------------------------------------------------------------------

class MyApp(wx.App):
    def OnInit(self):
        frame = MyFrame(None,-1,'Grid GetSelectedXX bug')
        self.SetTopWindow(frame)
        frame.Show(True)
        return True

appl = MyApp()
appl.MainLoop()

 	  	 

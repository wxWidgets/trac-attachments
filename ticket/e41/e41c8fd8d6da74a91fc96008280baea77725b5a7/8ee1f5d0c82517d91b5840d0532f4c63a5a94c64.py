import wx

class MainWindow(wx.Frame):
    def __init__(self, parent, id, title):
        wx.Frame.__init__(self, parent, id, title)

        self.splitter = wx.SplitterWindow(self, -1)
        self.splitter.SplitVertically(wx.Panel(self.splitter, -1), wx.Panel(self.splitter, -1), 100)
        self.ConstructMenu()

    def ConstructMenu(self):
        filemenu = wx.Menu()
        filemenu.Append(100, "&New")

        menubar = wx.MenuBar()
        menubar.Append(filemenu, "&File")
        self.SetMenuBar(menubar)


app = wx.PySimpleApp()
frame = MainWindow(None, -1, "Menu test")
frame.Show()
app.MainLoop()


 	  	 

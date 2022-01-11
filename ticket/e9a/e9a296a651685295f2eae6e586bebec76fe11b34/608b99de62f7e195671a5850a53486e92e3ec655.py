import wx

class Frame(wx.Frame):
    def __init__(self, *args, **kwargs):
        super(Frame, self).__init__(*args, **kwargs)
        menuBar = wx.MenuBar()
        menu = wx.Menu()
        labels = 'Without accelerator', '&With accelerator'
        for label in labels:
            menu.AppendItem(wx.MenuItem(menu, wx.NewId(), label))
        menuBar.Append(menu, 'Menu')
        self.SetMenuBar(menuBar)

        for label in labels:
            if menu.FindItem(label) == wx.NOT_FOUND:
                print 'Menu item %s not found'%label
            else:
                print 'Menu item %s found'%label


app = wx.App(False)
frame = Frame(None)
frame.Show()
app.MainLoop()

 	  	 

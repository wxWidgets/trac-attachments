import wx
import wx.grid


class CustomGrid(wx.grid.Grid):
    def __init__(self, parent):
        wx.grid.Grid.__init__(self, parent)
        self.CreateGrid(0,3)
        self.SetColLabelValue(0, "Just Testing")

    def Add(self):
        self.AppendRows(1)

    def Remove(self):
        self.DeleteRows(1)


class MainWindow(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, parent=None)
        panel = wx.Panel(self)
        self.the_grid = CustomGrid(panel)

        add = wx.Button(panel, id=-1, label="Add", pos=(10,50))
        remove = wx.Button(panel, id=-1, label="Remove", pos=(10,70))
        add.Bind(wx.EVT_BUTTON, self.Add)
        remove.Bind(wx.EVT_BUTTON, self.Remove)

        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(self.the_grid, 1, wx.EXPAND)
        panel.SetSizer(sizer)
        self.Show()
    
    def Add(self, event):
        self.the_grid.Add()

    def Remove(self, event):
        self.the_grid.Remove()

app = wx.App(False)
frame = MainWindow()
app.MainLoop()


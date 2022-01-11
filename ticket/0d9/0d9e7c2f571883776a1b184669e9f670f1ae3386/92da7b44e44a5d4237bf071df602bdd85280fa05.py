from time import sleep
import wx.grid

class Main(wx.Frame):
    def __init__(self):
        super(Main, self).__init__(parent=None, id=-1, title="wx.Yield test")

        sizer = wx.BoxSizer(wx.VERTICAL)

        self.SetSizer(sizer)
        button = wx.Button(self, -1, "Test Grid")
        self.Bind(wx.EVT_BUTTON, self.test_grid, button)
        sizer.Add(button, 1, wx.EXPAND|wx.ALL)

        self.grid = wx.grid.Grid(self, -1)
        self.grid.CreateGrid(1, 2)
        self.grid.SetColLabelValue(0, "A")
        self.grid.SetColLabelValue(1, "B")
        sizer.Add(self.grid, 1, wx.EXPAND|wx.ALL)

        self.text = wx.TextCtrl(self, id=-1)
        sizer.Add(self.text, 1, wx.EXPAND|wx.ALL)


    def test_grid(self, event):
        wx.CallAfter(self.grid.SetCellValue, 0, 0, "test a")
        wx.CallAfter(self.grid.SetCellValue, 0, 1, "test b")
        wx.GetApp().Yield(True)
        self.text.SetValue(unicode(self.grid.GetCellValue(0, 0)))


app = wx.App(False)
frame = Main()
frame.Show(True)
app.MainLoop()

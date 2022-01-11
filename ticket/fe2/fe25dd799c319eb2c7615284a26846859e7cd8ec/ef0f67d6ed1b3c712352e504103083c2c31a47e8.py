import sys
import wx
import wx.lib.inspection

app = wx.App()
f = wx.Frame(None, size=(900,200))
p = wx.Panel(f)
l = wx.ListCtrl(p, -1, style=wx.LC_REPORT | wx.TE_MULTILINE, size=(9,9))

f.Sizer = wx.BoxSizer(wx.VERTICAL)
f.Sizer.Add(p, 1, wx.EXPAND)
p.Sizer = wx.BoxSizer(wx.VERTICAL)
p.Sizer.Add(l, 1, wx.EXPAND)

columns = ("Name", "Address", "Count", "Suspension List", "Suspension Count")
for index, val in enumerate(columns):
    l.InsertColumn(index, val, width=120)

vals = ["bob", "0x23432", "10", "0x3284u", "0x3287913"]

rowIndex = l.InsertStringItem(sys.maxint, vals[0])
id = wx.NewId()
l.SetItemData(rowIndex, long(id))
for colIndex, val in enumerate(vals[1:]):
    l.SetStringItem(rowIndex, colIndex+1, val)
#l.SetForegroundColour((255,255,255))
l.SetTextColour((255, 255, 255))
l.SetBackgroundColour((0,0,0))


f.Layout()
f.Show()
app.MainLoop()
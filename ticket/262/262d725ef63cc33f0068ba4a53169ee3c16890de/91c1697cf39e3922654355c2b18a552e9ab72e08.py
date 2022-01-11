import wx
import wx.dataview

app = wx.App()
frame = wx.Frame(None)
test = wx.dataview.DataViewListCtrl(frame)
test.AppendDateColumn("Date", 0)
#test.AppendDateColumn("Date", 0, align=wx.ALIGN_CENTER_VERTICAL)
test.AppendTextColumn("Text", 1)
test.AppendItem((wx.DateTime.Now(), 'Test'))
frame.Centre()
frame.Show()
app.MainLoop()

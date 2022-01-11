import wx
import wx.dataview

def popup(event):
    test.PopupMenu(wx.Menu())
    event.Skip()

app = wx.App()
frame = wx.Frame(None)
test = wx.dataview.DataViewListCtrl(frame)
test.AppendTextColumn("Text", 0)
test.AppendItem(('Test1', ))
test.AppendItem(('Test2', ))
test.Bind(wx.dataview.EVT_DATAVIEW_ITEM_CONTEXT_MENU, popup)
frame.Centre()
frame.Show()
app.MainLoop()

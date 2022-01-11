import wx

app = wx.PySimpleApp()
frame = wx.Frame(None)
listctrl = wx.ListCtrl(frame)
listctrl.Append(["Test Item"])
frame.Show()
listctrl.Select(0)
itemId = listctrl.GetFirstSelected()
state1 = listctrl.GetItemState(itemId, 0xFFFF)
item = listctrl.GetItem(itemId)
item.SetMask(wx.LIST_MASK_STATE)
state2 = item.GetState()
print "listctrl.GetFirstSelectedItem() = itemId = ", itemId
print "listctrl.GetItemState(itemId, 0xFFFF) = ", state1
print "listctrl.GetItem(itemId).GetState()) = ", state2
app.MainLoop()
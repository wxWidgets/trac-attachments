import wx
import wx.gizmos

app = wx.PySimpleApp()

window = wx.Frame(None)
window.Show(True)

app.SetTopWindow(window)
sizer = wx.BoxSizer()

tree = wx.gizmos.TreeListCtrl(window, style= wx.TR_HIDE_ROOT | wx.TR_MULTIPLE)
sizer.Add(tree, 1, wx.EXPAND)
window.SetSizerAndFit(sizer)

tree.AddColumn("Column1")
tree.AddColumn("Column2")

root = tree.AddRoot("Root")
items = [tree.AppendItem(root, "Item %d" % i) for i in range(10)]

tree.SelectItem(items[3], items[5], False)
#selects 3,4,5

tree.SelectItem(items[1], items[3], False)
#selects 1,2,3 without deselecting others -> False parameter

#interactive scenario:
# 1. select "Item 3"
# 2. holding "Shift" select "Item 5" (selected items (3,4,5))
# 3. holding "Ctrl" select "Item 7" (selected items (3,4,5,7))
# 4. holding "Ctrl+Shift" select "Item 9" (selected items (7,8,9) -> should be (3,4,5,7,8,9))
app.MainLoop()


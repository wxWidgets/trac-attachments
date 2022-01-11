"""
Demonstrates that wx on Windows does not fire EVT_TREE_ITEM_EXPANDED
events when the user clicks a tree node if that node is marked as
"item has children" but has no actual children nodes. This behavior
differs from wx on Mac OS X.

On Mac OS X, clicking the expander beside the root node prints "got_event" (as expected).
On Windows, doing the same prints nothing.
"""

import wx

def got_event(event):
    print "got_event"

app = wx.App(False)
frame = wx.Frame(None, wx.ID_ANY, "Frame")

tree = wx.TreeCtrl(frame, style=wx.TR_DEFAULT_STYLE)

root = tree.AddRoot('')
tree.SetItemText(root, 'ROOT') # workaround http://trac.wxwidgets.org/ticket/10085
tree.SetItemHasChildren(root, True)

# If you uncomment the following line, Windows fires EVT_TREE_ITEM_EXPANDED correctly
#child1 = tree.AppendItem(root, 'Child 1')

tree.Bind(wx.EVT_TREE_ITEM_EXPANDED, got_event, tree)

frame.Show(True)
app.MainLoop()
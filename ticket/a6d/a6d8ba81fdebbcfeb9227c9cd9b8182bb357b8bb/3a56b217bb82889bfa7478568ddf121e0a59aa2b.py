import wx
from wx.lib.agw.hypertreelist import HyperTreeList, TR_NO_HEADER
print wx.lib.agw.hypertreelist.__file__
import os

# Disable overlayed scrollbars in Ubuntu. These are causing multiple wx/GTK issues
os.putenv('LIBOVERLAY_SCROLLBAR', '0')

# Disable ubuntus menu alternative placement
os.putenv('UBUNTU_MENUPROXY', '')

app = wx.PySimpleApp()
frame = wx.Frame(None)

style = 0
agwStyle = wx.TR_EDIT_LABELS \
         | wx.TR_NO_LINES | wx.TR_FULL_ROW_HIGHLIGHT | wx.TR_HIDE_ROOT \
         | wx.TR_HAS_VARIABLE_ROW_HEIGHT | wx.TR_SINGLE
                
tree = HyperTreeList(frame, style=style, agwStyle=agwStyle)

tree.AddColumn('Heading1', 180, edit=False)
tree.AddColumn('Heading2', 80, edit=False)
tree.AddColumn('Heading3', 30, edit=False)
tree.AddColumn('Heading4', 100, edit=False)


def set_item_columns_text(tree, item, *fields):
    for column, text in enumerate(fields):
        tree.SetItemText(item, text, column)

def add_item(tree, parent, n):
    wnd = wx.CheckBox(tree)
    item = tree.AppendItem(parent, '', wnd=wnd)
    text = str(n) + 'f' * n
    set_item_columns_text(tree, item, text, 'mick', 'john', 'wayne')
    tree.SetItemWindow(item, wnd, 0)
    return item

root = tree.AddRoot("The Root Item")
items = [add_item(tree, root, n) for n in range(30)]
wx.CallLater(5000, tree.EnsureVisible, items[15])

frame.Show()
app.MainLoop()



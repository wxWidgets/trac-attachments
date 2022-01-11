"""
Sample demonstrating focus stealing of TreeCtrl.DeleteAllItems() when wx.TR_HIDE_ROOT is used.

Tested on wxPython 2.9.5.0, Win 7 x64, Python 2.7 x32.

Steps to reproduce:
    Press any key inside the TextCtrl to trigger the onTextKeyDown event handler. The problem manifests only if TreeCtrl
    has style wx.TR_HIDE_ROOT and tree item is selected when deletion takes place.

Problem:
    DeleteAllItems() steals focus from the TextCtrl and emits EVT_TREE_SEL_CHANGED for tree items during deletion.

Workaround:
    If TreeCtrl.Unselect() is used before DeleteAllItems(), it behaves correctly.
"""
import wx
print wx.version()


def onTextKeyDown(event):
    #If we unselect the selected item, DeleteAllItems() behaves correctly
    #treeCtrl.Unselect()
    #It would appear that EVT_TREE_SEL_CHANGED is emitted only for items that come *after* the selected node
    #(including the selected node).
    #Note how all items after the currently selected one remain drawn in the TreeCtrl until next redraw.
    treeCtrl.DeleteAllItems()
    event.Skip()


def onTreeSelChanged(event):
    print "Tree selection changed"

#Create simple main frame
app = wx.App(False)
frame = wx.Frame(None, wx.ID_ANY, "treectrl_test")
masterSizer = wx.BoxSizer(wx.VERTICAL)
frame.SetSizer(masterSizer)

#Add TextCtrl
textField = wx.TextCtrl(frame, size=(200, -1), style=wx.PROCESS_ENTER)
textField.Bind(wx.EVT_KEY_DOWN, onTextKeyDown, textField)
masterSizer.Add(textField, 0, wx.EXPAND, 0)

#Add the TreeCtrl
treeCtrl = wx.TreeCtrl(frame, -1, style=wx.TR_DEFAULT_STYLE | wx.TR_HIDE_ROOT)
#If wx.TR_HIDE_ROOT is not used, the application behaves correctly
#treeCtrl = wx.TreeCtrl(frame, -1, style=wx.TR_DEFAULT_STYLE)

masterSizer.Add(treeCtrl, 1, wx.EXPAND, 0)
frame.Bind(wx.EVT_TREE_SEL_CHANGED, onTreeSelChanged, treeCtrl)

#Add some items to the tree
rootID = treeCtrl.AddRoot('root')
childList = []
for i in range(1, 10):
    child = treeCtrl.AppendItem(rootID, 'child' + str(i))
    childList.append(child)

#Item has to be selected for the problem to manifest.
treeCtrl.SelectItem(childList[0])

#Inspection tool snippet
#import wx.lib.inspection
#wx.lib.inspection.InspectionTool().Show()

#Run the sample
frame.Show(True)
app.MainLoop()


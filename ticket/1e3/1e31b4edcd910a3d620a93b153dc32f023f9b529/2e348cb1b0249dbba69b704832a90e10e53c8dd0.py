if __name__ == "__main__":
  import wxversion
  wxversion.select("3.0")
#  wxversion.select("2.9.4")

import wx.aui


class TestListView(wx.ListView):
  def __init__(self, parentWin, txt):
    wx.ListView.__init__(self, parentWin, style=wx.LC_REPORT)
    self.InsertColumn(0, txt, wx.LIST_FORMAT_LEFT, 50)
    self.InsertColumn(1, "Detail", wx.LIST_FORMAT_LEFT, -1)
    self.InsertStringItem(0, "Something")
    
class TestNotebook(wx.Notebook):
  def Change(self, txt, withFreeze):
    print "CHANGE TO", txt
    if withFreeze: self.Freeze()
    
    self.DeleteAllPages()
#    self.AddPage(wx.TextCtrl(self), txt)
#    self.AddPage(TestListView(self, txt), "List")
    self.AddPage(TestListView(self, txt), "List")
    self.InsertPage(0, wx.TextCtrl(self), txt)
    self.GetCurrentPage().SetValue("Version: %s\nFreeze: %s" % (wx.version(), str(withFreeze)))
    
    if withFreeze: self.Thaw()
    

class ObjTreeCtrl(wx.TreeCtrl):
  def __init__(self, parent):
    wx.TreeCtrl.__init__(self, parent, style=wx.TR_HAS_BUTTONS | wx.TR_HIDE_ROOT | wx.TR_LINES_AT_ROOT)
    self.AddRoot("ObjTreeRoot")
    item=self.AppendItem(self.GetRootItem(), "ToplevelEntry")
    self.AppendItem(item, "One")
    self.AppendItem(item, "Two")
    self.AppendItem(item, "Three")

    
class TestFrame(wx.Frame):
  def __init__(self):
    wx.Frame.__init__(self, None, title="AUI Test")

    menubar=wx.MenuBar()
    self.menu=wx.Menu()
    self.menu.AppendCheckItem(5000, "Freeze/Thaw")
    menubar.Append(self.menu, "Toggle")
    self.SetMenuBar(menubar)

    self.details = TestNotebook(self)
    self.tree=ObjTreeCtrl(self)
    self.tree.Bind(wx.EVT_TREE_SEL_CHANGED, self.OnTreeSelChange)

    self.manager=wx.aui.AuiManager(self)
    self.manager.AddPane(self.details, wx.aui.AuiPaneInfo().Caption("Details").Center())
    self.manager.AddPane(self.tree, wx.aui.AuiPaneInfo().Caption("Browser").Left().BestSize((250,350)))
    self.manager.Update()

  def OnTreeSelChange(self, evt):
    withFreeze=self.menu.IsChecked(5000)
    self.details.Change(self.tree.GetItemText(evt.GetItem()), withFreeze)

def main():
  app=wx.App()
  frame=TestFrame()
  app.SetTopWindow(frame)
  frame.Show()
  app.MainLoop()

if __name__ == "__main__":
  main()

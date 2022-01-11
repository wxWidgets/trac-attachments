"""
author: Bruce Who 胡旭昭
date: 2005-03-01
description: DnD，演示了把节点拖出为文件的功能，但是有bug
NOTE: you must create a test.txt file in the same directory of this script for testing.
"""
import os
import wx

class MyDropSource(wx.DropSource):
   def __init__(self, tree):
      wx.DropSource.__init__(self,tree)
      self.tree_ = tree

class MyTreeCtrl(wx.TreeCtrl):
    def __init__(self, parent):
        wx.TreeCtrl.__init__(self, parent,-1)
        root=self.AddRoot('root')
        item1 = self.AppendItem(root,'item1')
        item11 = self.AppendItem(item1,'item11')
        item12 = self.AppendItem(item1,'item12')
        item13 = self.AppendItem(item1,'item13')
        item2 = self.AppendItem(root,'item2')
        item21 = self.AppendItem(item2,'item21')
        item22 = self.AppendItem(item2,'item22')
        item23 = self.AppendItem(item2,'item23')
        self.Expand(root)
        self.Expand(item1)
        self.Expand(item2)

        ## events
        self.Bind(wx.EVT_TREE_BEGIN_DRAG,self.OnBeginDrag)
    def OnBeginDrag(self,evt):
      sel_item, flags = self.HitTest(evt.GetPoint())
      self.SelectItem(sel_item)

      print "A node called %s is being dragged" % (self.GetItemText(sel_item))

      cdo = wx.FileDataObject()
      ## this is a temp file
      cdo.AddFile(os.path.realpath('./test.txt'))

      tds = MyDropSource(self)
      tds.SetData(cdo)

      dragResult = tds.DoDragDrop(True)

      if dragResult == wx.DragCopy:
          print "Result indicated successful copy"
      elif dragResult == wx.DragMove:
          print "Result indicated successful move"
      else:
          print "Result indicated failed drop"
      print

class myFrame(wx.Frame):    # {{{
    def __init__(self, *args, **kwds):
        wx.Frame.__init__(self, *args, **kwds)
        #------ panel
        self.panel_=wx.Panel(self,-1)
        self.sizer_ = wx.BoxSizer( wx.VERTICAL )
        self.treeCtrl_ = MyTreeCtrl(self.panel_)
        #------ put stuff into sizer
        self.sizer_.Add(self.treeCtrl_,proportion = 1,flag=wx.EXPAND)

        # apply sizer
        self.panel_.SetSizer(self.sizer_)
        self.panel_.SetAutoLayout(True)
#   }}}

def main():    # {{{
    app = wx.PySimpleApp(0)
    frame = myFrame(None,-1,title='')
    frame.Show(True)
    app.SetTopWindow(frame)
    app.MainLoop()
#   }}}

if __name__ == "__main__":main()
 	  	 

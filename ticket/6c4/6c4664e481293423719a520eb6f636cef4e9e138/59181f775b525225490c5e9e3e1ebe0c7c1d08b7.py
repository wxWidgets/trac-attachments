import wx
import wx.xrc

resourceText="""<?xml version="1.0" ?>
<resource>
  <object class="wxPanel" name="TestPanel">
    <object class="wxBoxSizer">
      <orient>wxVERTICAL</orient>
      <object class="sizeritem">
        <object class="unknown" name="TestCtrl1">
          <size>-1,100</size>
        </object>
        <option>1</option>
        <flag>wxEXPAND</flag>
      </object>
      <object class="sizeritem">
        <object class="unknown" name="TestCtrl2">
          <size>-1,100</size>
        </object>
        <option>1</option>
        <flag>wxEXPAND</flag>
      </object>
    </object>
  </object>
</resource>
"""

class TestPanel(wx.Panel):

    def __init__(self, parent,resource):
        p = resource.LoadPanel(parent, 'TestPanel')
        self.PostCreate(p)

        items = ["choice %d"%i for i in range(20)]

        #Working...
        self.ListCtrl = wx.ListBox(self, -1,style=wx.LB_EXTENDED)
        resource.AttachUnknownControl('TestCtrl1', self.ListCtrl, self)
        self.ListCtrl.Set(items)

        #Not working...
        self.CheckListCtrl = wx.CheckListBox(self, -1)
        resource.AttachUnknownControl('TestCtrl2', self.CheckListCtrl, self)
        self.CheckListCtrl.Set(items)

class TestFrame(wx.Frame):

    def __init__(self, parent):
        wx.Frame.__init__(self, parent, -1, "testing...", size=(150,250), style=wx.DEFAULT_FRAME_STYLE )
        self.TestPanel = TestPanel(self,resource)

if __name__ == '__main__':

    app = wx.PySimpleApp()

    resource = wx.xrc.EmptyXmlResource()
    resource.LoadFromString(resourceText)

    f = TestFrame(None)
    f.Show()
    app.MainLoop()


 	  	 

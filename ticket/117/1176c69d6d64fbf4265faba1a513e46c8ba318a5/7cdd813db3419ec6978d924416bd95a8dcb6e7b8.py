import sys
import wx

class TestListCtrlPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1, style=wx.WANTS_CHARS)
        self.il = wx.ImageList(16, 16)

        image_ids = (wx.ART_ERROR, wx.ART_QUESTION, wx.ART_QUESTION)
        for image_id in image_ids:
            image = wx.ArtProvider.GetBitmap(image_id, wx.ART_OTHER, (16, 16))
            self.il.Add(image)
            
        self.list = wx.ListCtrl(self, style=wx.LC_REPORT|wx.BORDER_NONE)
        self.list.SetImageList(self.il, wx.IMAGE_LIST_SMALL)

        self.list.InsertColumn(0, "Column 1")

        self.add_with_default_icon()
        self.add_with_no_icon()
        self.add_with_icon()

    def add_with_default_icon(self):
        li = self.list.InsertStringItem(sys.maxint, 'default')

    def add_with_no_icon(self):
        image = -1 # This *should* indicate no icon
        index = self.list.InsertStringItem(sys.maxint, 'no icon', image)
        self.list.SetItemImage(index, -1) # But we need to explicitly state this

    def add_with_icon(self):
        image = 1
        index = self.list.InsertStringItem(sys.maxint, 'with icon', image)

if __name__ == '__main__':
    app = wx.App()
    parent = wx.Frame(None)
    panel = TestListCtrlPanel(parent)
    parent.Show()
    app.MainLoop()



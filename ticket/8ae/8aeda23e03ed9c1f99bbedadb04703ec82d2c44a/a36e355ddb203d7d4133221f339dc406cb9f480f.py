import wx
from wx.lib.agw import aui


class myParentFrame(aui.AuiMDIParentFrame):
    def __init__(self, parent):
        aui.AuiMDIParentFrame.__init__(self, parent, -1,
                                          title="Conveggie a convore client",
                                          size=(640,480),
                                          style=wx.DEFAULT_FRAME_STYLE )
        c1 = myChildFrame(self, 0)
        c2 = myChildFrame(self, 1)

        c1.Activate()


    def display_child(self, idx):
        if idx == 0:
            child = 1
        else:
            child = 0

        w = self.FindWindowByName('child:%d' % child)

        if not w:
            w = myChildFrame(self, child)

        w.Activate()

class myChildFrame(aui.AuiMDIChildFrame):
    def __init__(self, parent, idx):

        aui.AuiMDIChildFrame.__init__(self, parent, -1,
                                         title="Child: %d" % idx,
                                         name='child:%d' % idx)

        self.idx = idx
        self._parent = parent

        bs = wx.BoxSizer()

        bs.Add(wx.StaticText(self, -1, 'Index:%d' % self.idx), 1 ,10 )

        btn = wx.Button(self, -1, 'Index:%d' % self.idx)

        bs.Add(btn )

        self.Bind(wx.EVT_BUTTON, self.OnClick, btn)

    def OnClick(self, event):
        self._parent.display_child(self.idx)

class myApp(wx.App):
    def OnInit(self):
        frame = myParentFrame(None)
        self.SetTopWindow(frame)

        frame.Show(True)
        return True

if __name__ == '__main__':
    app = myApp(redirect=True)
    app.MainLoop()


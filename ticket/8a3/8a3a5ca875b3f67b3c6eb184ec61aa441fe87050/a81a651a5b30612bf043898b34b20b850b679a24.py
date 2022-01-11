import wx
import wx.lib.agw.hypertreelist as HTL
import sys

class TestFrame ( wx.Frame ):

    def __init__( self, parent ):
        wx.Frame.__init__  ( self, parent, id = wx.ID_ANY, title = u"TestFrame", pos = wx.DefaultPosition,
                size = wx.Size(500, 300), style = wx.DEFAULT_FRAME_STYLE|wx.TAB_TRAVERSAL )
        self.SetSizeHintsSz( wx.DefaultSize, wx.DefaultSize )
        sizer = wx.BoxSizer( wx.VERTICAL )
        self.tree = HTL.HyperTreeList(self, style=wx.TR_HAS_VARIABLE_ROW_HEIGHT)
        for column in range(columns):
            self.tree.AddColumn(u'Column %d' % column)
        self.tree.SetMainColumn(columns - 1)
        root = self.tree.AddRoot(u'root')
        text = wx.TextCtrl(self.tree.GetMainWindow(), value=u"Child 1 text")
        self.tree.AppendItem(root, u'child', wnd=text)
        sizer.Add(self.tree, 1, wx.ALL|wx.EXPAND, 5)
        self.SetSizer(sizer)
        self.Layout()

class App(wx.App):

    def __init__(self, redirect=True, filename=None):
        wx.App.__init__(self, redirect, filename)

    def OnInit(self):
        self.frame = TestFrame(None)
        self.frame.Show()
        self.SetTopWindow(self.frame)
        return True

    def OnExit(self):
        pass

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print 'Usage: htl_bug.py #columns'
        print 'where #columns is 1, 2, 3, etc.'
        print 'Example: htl_bug.py 3'
        sys.exit()
    global columns
    columns = int(sys.argv[1])
    app = App(redirect=False)
    app.MainLoop()

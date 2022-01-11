import wx
import wx.lib.customtreectrl as ctc

class App(wx.App):
    def OnInit(self):
        self.frame = wx.Frame(None, wx.ID_ANY, "Tree refresh")

        tree = ctc.CustomTreeCtrl(self.frame, style=wx.TR_HIDE_ROOT)
        root = tree.AddRoot("hidden root")
        tree.AppendItem(root, "child")

        self.frame.Show(True)
        return True

if __name__ == "__main__":
    app = App(0)
    app.MainLoop()

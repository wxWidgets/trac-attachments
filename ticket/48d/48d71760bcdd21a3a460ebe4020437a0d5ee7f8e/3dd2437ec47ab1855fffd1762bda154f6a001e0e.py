import wx

########################################################################
class SampleDialog(wx.Dialog):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, parent):
        """Constructor"""
        wx.Dialog.__init__(self, parent, title="Tutorial")
        print "Hello Here"
        btnOk = wx.Button(self, wx.ID_OK)
        print "Hello Here"
        btnCancel = wx.Button(self, wx.ID_CANCEL)
        btnSizer = wx.StdDialogButtonSizer()
        btnSizer.AddButton(btnOk)
        btnSizer.AddButton(btnCancel)
        btnSizer.Realize()
        self.SetSizer(btnSizer)
        
def main():
    app = wx.App(False)
    app.MainLoop()
    dlg = SampleDialog(None)
    dlg.ShowModal()
    dlg.Destroy()
#----------------------------------------------------------------------
if __name__ == '__main__':
    main()
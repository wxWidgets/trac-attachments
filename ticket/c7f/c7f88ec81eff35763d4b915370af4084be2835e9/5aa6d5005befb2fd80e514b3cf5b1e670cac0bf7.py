import  wx
import  wx.lib.iewin    as  iewin


class TestApp(wx.App):

    def OnInit(self):
        frame = wx.Frame(None, -1, u"Test")

        iePanel = iewin.IEHtmlWindow(frame, -1,
                style=wx.NO_FULL_REPAINT_ON_RESIZE)
        
        panel2 = wx.Panel(frame)

        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(panel2, 1, wx.EXPAND)
        sizer.Add(iePanel, 1, wx.EXPAND)

        frame.SetSizer(sizer)
        
        self.SetTopWindow(frame)
        
        frame.Show()
        iePanel.SetFocus()
        
        return True



if __name__ == '__main__':
    app = TestApp(0)
    app.MainLoop()

    # run.main(['', os.path.basename(sys.argv[0])] + sys.argv[1:])


#----------------------------------------------------------------------


 	  	 

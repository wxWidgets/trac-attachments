import wx


class MyTaskBarIcon(wx.TaskBarIcon):
    
    def __init__(self, *args, **kwargs):
        wx.TaskBarIcon.__init__(self, *args, **kwargs)
        icon = wx.Icon("./icon/logo-22x22.png", wx.BITMAP_TYPE_PNG)
        self.SetIcon(icon, "Control")
        self.Bind(wx.EVT_MENU, lambda _: self.Destroy())
        self.Bind(wx.EVT_TASKBAR_LEFT_UP, self.OnTaskBarLeftClick)
    
    def GetIconPosition(self):
        """
        Hack to find the TaskBarIcon's position
        """
        for win in wx.GetTopLevelWindows():
            if(win.GetClassName() == "wxTopLevelWindow"):
                return win.GetPosition()
    
    def CreatePopupMenu(self):
        menu = wx.Menu()
        menu.Append(wx.ID_EXIT, "E&xit")
        return menu
    
    def OnTaskBarLeftClick(self, event=None):
        pos = self.GetIconPosition()
        print "self.GetIconPosition() : %s" % str(pos)
        pos2 = wx.FindWindowAtPointer() # This returns None when GetIconPosition() returns (0, 0)
        print "wx.FindWindowAtPointer() : %s" % (str(pos2.GetPosition()) if pos2 else str(None))
        print "Mouse pos : %s" % str(wx.GetMousePosition())


class MyApp(wx.App):
    def OnInit(self):
        self.tsbico = MyTaskBarIcon()
        return True

if(__name__ == "__main__"):
    print "wxPython version : %s:" % wx.version()
    app = MyApp(False)
    #import wx.lib.inspection
    #wx.lib.inspection.InspectionTool().Show()
    app.MainLoop()



import wx

# -----------------------------------------------------------------------------

class TaskBarApp(wx.Frame):
    def __init__(self, parent, id, title):
        wx.Frame.__init__(self, parent, -1, title, size = (1, 1),
            style=wx.FRAME_NO_TASKBAR|wx.NO_FULL_REPAINT_ON_RESIZE)
        self.tbicon = wx.TaskBarIcon()
        icon = wx.Icon('helloworld.ico', wx.BITMAP_TYPE_ICO)
        self.tbicon.SetIcon(icon, '')
        self.tbicon.Bind(wx.EVT_TASKBAR_RIGHT_UP, self.OnTaskBarMenu)

        # create the NewId()
        self.TBMENU_1 = wx.NewId()
        self.TBMENU_2 = wx.NewId()
        self.TBMENU_3 = wx.NewId()
        self.TBMENU_4 = wx.NewId()
        self.TBMENU_5 = wx.NewId()
        self.TBMENU_QUIT = wx.NewId()

        # make THE menu
        self.menu = wx.Menu()
        self.menu.Append(self.TBMENU_1, "&Hello")
        self.menu.Append(self.TBMENU_2, "World", kind=wx.ITEM_CHECK)

        self.menu.AppendSeparator()
        self.menu.Append(self.TBMENU_QUIT, "&Quit")

        # bind the Event
        self.tbicon.Bind(wx.EVT_MENU, self.OnQuit, id=self.TBMENU_QUIT)
        
        # ---------------------------------------------------------------------
        self.Show(True)

    # -------------------------------------------------------------------------
    def OnTaskBarMenu(self, evt):
        self.tbicon.PopupMenu(self.menu)

    # -------------------------------------------------------------------------
    def OnQuit(self, evt):
        self.Close(True)
        wx.GetApp().ProcessIdle()

# -----------------------------------------------------------------------------

class MyApp(wx.App):
    def OnInit(self):
        frame = TaskBarApp(None, -1, ' ')
        frame.Center(wx.BOTH)
        frame.Show(False)
        return True

# -----------------------------------------------------------------------------

def main():
    app = MyApp(0)
    app.MainLoop()

# -----------------------------------------------------------------------------

if __name__ == '__main__':
    main()
 	  	 

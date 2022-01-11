import wx
import sha, os

class MyTaskBarIcon(wx.TaskBarIcon):
    ID_LOGIN = wx.NewId()
    ID_CONFIG = wx.NewId()
    ID_MUTE = wx.NewId()

    def __init__(self, parent, *args, **kwargs):
        wx.TaskBarIcon.__init__(self, *args, **kwargs)
        self.parent = parent
        icon = wx.Icon("./icon/logo-22x22.png", wx.BITMAP_TYPE_PNG)
        self.SetIcon(icon, "Control")

        self.Bind(wx.EVT_MENU, self.parent.showLogin, id=MyTaskBarIcon.ID_LOGIN)
        self.Bind(wx.EVT_MENU, self.onExit, id=wx.ID_EXIT)


    def CreatePopupMenu(self):
        menu=wx.Menu()
        menu.Append(MyTaskBarIcon.ID_LOGIN, "&Login/Change user")
        menu.AppendSeparator()
        menu.Append(wx.ID_EXIT, "E&xit")
        return menu

    def onExit(self, evt):
        print 'closing'
        wx.CallAfter(self.parent.Close)



class LoginDialog(wx.Frame):
    def __init__(self, parent=None, id=wx.ID_ANY, title="Login",
                 pos=wx.DefaultPosition, size=(300, 175),
                 #style=wx.FRAME_NO_TASKBAR|wx.NO_FULL_REPAINT_ON_RESIZE,
                 *args, **kwargs):
        wx.Frame.__init__(self, parent, id, title, pos, size, *args, **kwargs)
        panel = wx.Panel(self, wx.ID_ANY)  # added a panel

        icon = wx.Icon("./icon/logo-22x22.png", wx.BITMAP_TYPE_PNG)
        self.SetIcon(icon)
        wx.StaticText(panel, wx.ID_ANY, "Please type your user name and password.", wx.Point(15, 5))
        wx.StaticText(panel, wx.ID_ANY, "User name: ", wx.Point(20, 30))
        wx.StaticText(panel, wx.ID_ANY, "Password: ", wx.Point(20, 55))
        self.usernameBox = wx.TextCtrl(panel, wx.ID_ANY, "", wx.Point(100, 30), wx.Size(175, wx.ID_ANY))
        self.usernameBox.SetFocus()
        self.passwordBox = wx.TextCtrl(panel, wx.ID_ANY, "", wx.Point(100, 55), wx.Size(175, wx.ID_ANY), style=wx.TE_PASSWORD)
        self.checkBox = wx.CheckBox(panel, wx.ID_ANY, "Remember login information", wx.Point(20, 90))
        wx.Button(panel, wx.ID_OK, " OK ", wx.Point(100, 115), wx.DefaultSize).SetDefault()
        wx.Button(panel, wx.ID_CANCEL, " Cancel ", wx.Point(200, 115), wx.DefaultSize)
        self.Bind(wx.EVT_BUTTON, self.onOk, id=wx.ID_OK)
        self.Bind(wx.EVT_BUTTON, self.onCancel, id=wx.ID_CANCEL)
        
        self.tbIcon = MyTaskBarIcon(self)
        
        self.Bind(wx.EVT_CLOSE, self.onExit)

    def onOk(self, event):
        username = self.usernameBox.GetValue()
        password = self.passwordBox.GetValue()
        if(len(username) > 0 and len(password) > 0):   # Test if the user entered the required info
            password = sha.new(password).hexdigest()
            print "Username : %s, Password : %s" % (username, password)
            self.Show(False)
        else:
            dlg = wx.MessageDialog(self, "You are required to enter a username and password to login", "Missing information", wx.OK | wx.ICON_EXCLAMATION)
            dlg.ShowModal()
            dlg.Destroy()

    def onCancel(self, event):
        dlg = wx.MessageDialog(self, "Are you sure you want to cancel logging in?", "Cancel login?", wx.YES_NO | wx.ICON_QUESTION | wx.NO_DEFAULT)
        if dlg.ShowModal() == wx.ID_YES:
            self.abortLogin(event)
        dlg.Destroy()

    def onExit(self, event):
        dlg = wx.MessageDialog(self, "Are you sure you want to exit?", "Exit the application?", wx.YES_NO | wx.ICON_QUESTION | wx.NO_DEFAULT)
        if dlg.ShowModal() == wx.ID_YES:
            # need to destroy the icon BEFORE the frame
            # because the frame is passed into the icon's class
            self.tbIcon.Destroy()
            wx.CallAfter(self.Destroy)
        dlg.Destroy()
        print "self = %s" %str(type(self))

    def abortLogin(self, event):
        self.Show(False)

    def showLogin(self, event):
        self.usernameBox.SetValue("")
        self.passwordBox.SetValue("")
        self.usernameBox.SetFocus()
        self.Show(True)


class MyApp(wx.App):
    def OnInit(self):
        self.gui = LoginDialog()
        self.gui.Center(wx.BOTH)
        self.gui.Show(False)
        self.SetTopWindow(self.gui)
        return True

if(__name__ == "__main__"):
    app = MyApp(False)
    app.MainLoop()


import wx


class Test(wx.Frame):
    def __init__(self):
        super(Test, self).__init__(None)

        self.menubar = wx.MenuBar()
        self.menubar.Append(Menu(), "&File")
        self.SetMenuBar(self.menubar)

        self.Centre()
        self.Show()


class Menu(wx.Menu):
    def __init__(self):
        super(Menu, self).__init__()
        wx.CallLater(1000, self.delay_append)  # Simulate dynamic append

    def test(self, event):
        print(event)

    def delay_append(self):
        self.item = wx.MenuItem(self, wx.NewId(), "Click me\tF1")
        self.AppendItem(self.item)
        self.Bind(wx.EVT_MENU, self.test, self.item)
        self.AppendSubMenu(SubMenu(), "Test2")


class SubMenu(wx.Menu):
    def __init__(self):
        super(SubMenu, self).__init__()
        self.item = wx.MenuItem(self, wx.NewId(), "Click me\tF2")
        self.AppendItem(self.item)
        self.Bind(wx.EVT_MENU, self.test, self.item)

    def test(self, event):
        print(event)

app = wx.App()
Test()
app.MainLoop()

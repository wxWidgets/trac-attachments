import wx

class ChildWindow(wx.Frame):
    def init(self):
        self.menu = wx.Menu()
        self.menu.Append(1004, 'Close - Will go BaNg!')
        self.menu.Append(1005, 'Normal menu item')

        self.message = wx.StaticText(self, label="Right click for menu")
        self.message.Bind(wx.EVT_RIGHT_UP, self.on_right_click)

        self.Bind(wx.EVT_MENU, self.on_close, id=1004)
        self.Bind(wx.EVT_MENU, self.on_working_menu_item, id=1005)

    def on_right_click(self, e):
        self.message.SetFocus()
        self.PopupMenuXY(self.menu, 10, 10)

    def print_current_focus(self):
        print wx.Window.FindFocus()

    def on_close(self, e):
        self.message.Close()
        self.message.Destroy()
        wx.CallAfter(self.print_current_focus)

    def on_working_menu_item(self, e):
        wx.MessageBox("All quiet on the western front")

class LaunchChildWindows(wx.Frame):
    def init(self):
        self.show_child = wx.Button(self, label='Click to show child window')
        self.Bind(wx.EVT_BUTTON, self.on_show_child)

    def on_show_child(self, e):
        child = ChildWindow(self)
        child.init()
        child.Show()

def run_sample():
    app = wx.PySimpleApp()
    frame = LaunchChildWindows(None)
    frame.init()
    frame.Show()
    app.MainLoop()

if __name__ == '__main__':
    run_sample()

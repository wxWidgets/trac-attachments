import wx

description = """
Pressing this button will start a countdown timer. When the timer reaches 0 a new menubar will be created and set to this frame.
Before the countdown reaches 0 open the File menu from the menubar above and wait until the countdown completes.

Under GTK the application should now be hung printing WIDGET_REALIZED_FOR_EVENT messages for each and every event
"""

class MyFrame(wx.Frame):
    def __init__(self, parent):
        super(MyFrame, self).__init__(parent)

        self.countdown = -1
        self.create_a_new_menu_bar_and_set()

        outline = wx.StaticText(self, label=description)
        self.countdown_view = wx.StaticText(self, label='Press button to start countdown')
        start_timer = wx.Button(self, label='Start Timer')
        start_timer.Bind(wx.EVT_BUTTON, self.on_start_timer)

        self.Sizer = wx.BoxSizer(wx.VERTICAL)
        self.Sizer.Add(outline)
        self.Sizer.Add(start_timer, 0, wx.EXPAND)
        self.Sizer.Add(self.countdown_view)

        self.timer = wx.Timer(self)
        self.Bind(wx.EVT_TIMER, self.on_timer, self.timer)
        self.timer.Start(1000)

        self.Fit()

    def on_start_timer(self, evt):
        self.countdown = 10
        self.update_countdown_view()

    def on_timer(self, evt):
        if self.countdown < 0:
            return

        if self.countdown == 0:
            self.create_a_new_menu_bar_and_set()

        self.update_countdown_view()
        self.countdown -= 1

    def update_countdown_view(self):
        self.countdown_view.SetLabel('Countdown: %ds' % self.countdown)

    def create_a_new_menu_bar_and_set(self):
        menu_bar = wx.MenuBar()
        menu = wx.Menu()
        m_exit = menu.Append(wx.ID_EXIT, "E&xit\tAlt-X", "Close window and exit program.")
        menu_bar.Append(menu, "&File")
        self.menu_bar = self.SetMenuBar(menu_bar)

app = wx.App()

frame = MyFrame(None)
frame.Show()

app.MainLoop()


import wx

class CustomPage(wx.Panel):
    def __init__(self, parent, colour):
        super(CustomPage, self).__init__(parent)
        self.colour = colour

        self.info_bar = wx.InfoBar(self)

        page_contents = wx.Panel(self)
        page_contents.SetBackgroundColour(colour)

        self.Sizer = wx.BoxSizer(wx.VERTICAL)
        self.Sizer.Add(self.info_bar, 0, wx.EXPAND)
        self.Sizer.Add(page_contents, 1, wx.EXPAND)

    def show_banner(self, on):
        if on:
            self.info_bar.ShowMessage(str(self.colour))
        else:
            self.info_bar.Dismiss()


def build_color_notebook_thingy(parent, nb):
    page1 = CustomPage(nb, wx.RED)
    nb.AddPage(page1, 'Red')

    page2 = CustomPage(nb, wx.BLUE)
    nb.AddPage(page2, 'Blue')

    page3 = CustomPage(nb, wx.GREEN)
    nb.AddPage(page3, 'Green')

    return nb

class FrameHolder(wx.Frame):
    def __init__(self):
        super(FrameHolder, self).__init__(None)

        self.nb = wx.Notebook(self)
        build_color_notebook_thingy(self, self.nb)

        show_banner = self.add_button('Show Banner', self.on_show_banners)
        hide_banner = self.add_button('Hide Banner', self.on_hide_banners)

        button_sizer = wx.BoxSizer(wx.HORIZONTAL)
        button_sizer.Add(show_banner)
        button_sizer.Add(hide_banner)

        self.Sizer = wx.BoxSizer(wx.VERTICAL)
        self.Sizer.Add(self.nb, 1, wx.EXPAND)
        self.Sizer.Add(button_sizer, 0, wx.EXPAND)

        #self.nb.ChangeSelection(1)

    def add_button(self, label, handler):
        button = wx.Button(self, label=label)
        button.Bind(wx.EVT_BUTTON, handler)
        return button

    def show_banners(self, on):
        for index in range(self.nb.GetPageCount()):
            page = self.nb.GetPage(index)
            page.show_banner(on)

    def on_show_banners(self, evt):
        self.show_banners(True)

    def on_hide_banners(self, evt):
        self.show_banners(False)


if __name__ == '__main__':
    app = wx.App()
    parent = FrameHolder()

    parent.Show()
    app.MainLoop()

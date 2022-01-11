
import wx


class SetFocus(object):
    description = 'SetFocus'
    def __init__(self, panel):
        self.panel = panel
    def set_focus(self):
        self.panel.SetFocus()

class IgnoreChildren(object):
    description = 'SetFocusIgnoringChildren'
    def __init__(self, panel):
        self.panel = panel
    def set_focus(self):
        self.panel.SetFocusIgnoringChildren()


class Demo(wx.Frame):
    def __init__(self):
        super(Demo, self).__init__(None)

        self.panel = wx.Panel(self)
        self.panel.SetSizer(wx.BoxSizer(wx.VERTICAL))

        for n in range(10):
            self.panel.Sizer.Add(wx.CheckBox(self.panel, label='cb%d' % n))

        #self.focuser = SetFocus(self.panel)
        self.focuser = IgnoreChildren(self.panel)

        self.SetTitle(self.focuser.description)

    def continually_set_focus(self, delay):
        print 'Setting Focus to panel'
        self.focuser.set_focus()
        wx.CallLater(delay, self.continually_set_focus, delay)


if __name__ == '__main__':
    app = wx.PySimpleApp()
    demo = Demo()
    demo.Show()
    demo.continually_set_focus(2000)
    app.MainLoop()

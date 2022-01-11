
import wx

class ComboboxItemsBehavour(wx.Frame):
    def __init__(self):
        super(ComboboxItemsBehavour, self).__init__(None)

        self.cb = wx.ComboBox(self)
        self.cb.SetValue('Fred')
        assert(self.cb.GetValue() == 'Fred')
        self.cb.SetItems(['one', 'two', 'three'])
        assert(self.cb.GetValue() == 'Fred')
        assert(False)


app = wx.App()
demo = ComboboxItemsBehavour()
demo.Show()
app.MainLoop()

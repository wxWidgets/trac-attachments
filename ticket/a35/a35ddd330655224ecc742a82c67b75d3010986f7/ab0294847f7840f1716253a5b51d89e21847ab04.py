import wx
import wx.stc

class TestFrame(wx.Frame):
    def __init__(self, parent, title):
        wx.Frame.__init__(self, parent, title=title)

        # Attributes
        self.stc = wx.stc.StyledTextCtrl(self)

        # Setup
        self.stc.IndicatorSetStyle(0, wx.stc.STC_INDIC_ROUNDBOX)
        self.stc.IndicatorSetForeground(0, wx.RED)
        self.stc.SetText("Hello World should be highlighted in Red")
        self.stc.StartStyling(0, wx.stc.STC_INDIC0_MASK)
        self.stc.SetStyling(11, wx.stc.STC_INDIC0_MASK)

        # Layout
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(self.stc, 1, wx.EXPAND)

        self.Show()

if __name__ == '__main__':
    app = wx.App(False)
    frame = TestFrame(None, "Stc Indicator Test")
    app.MainLoop()

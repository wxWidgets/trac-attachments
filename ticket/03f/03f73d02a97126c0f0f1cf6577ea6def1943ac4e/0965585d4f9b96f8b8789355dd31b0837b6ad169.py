import wx

class Panel(wx.Panel):
    def __init__(self, parent):
        super(Panel, self).__init__(parent)
        box1 = wx.BoxSizer(wx.VERTICAL)
        self.SetSizer(box1)

        button = wx.Button(self, label="Test")
        box1.Add(button, flag=wx.EXPAND)

        choice = wx.Choice(self, choices=("A", "B"))
        choice.SetSelection(0)
        box1.Add(choice, flag=wx.EXPAND)

        self.Bind(wx.EVT_CHILD_FOCUS, self._on_panel_child_focus)
        button.Bind(wx.EVT_CHILD_FOCUS, self._on_child_focus)
        choice.Bind(wx.EVT_CHILD_FOCUS, self._on_child_focus)
        button.Bind(wx.EVT_SET_FOCUS, self._on_set_focus)
        choice.Bind(wx.EVT_SET_FOCUS, self._on_set_focus)

    def _on_panel_child_focus(self, event):
        print("Panel EVT_CHILD_FOCUS", event.GetEventObject())
        event.Skip()

    def _on_set_focus(self, event):
        print("EVT_SET_FOCUS", event.GetEventObject())
        event.Skip()

    def _on_child_focus(self, event):
        print("EVT_CHILD_FOCUS", event.GetEventObject())
        event.Skip()

app = wx.App()
frame = wx.Frame(None)
Panel(frame)
frame.Show()
app.MainLoop()

import wx

class Frame2(wx.Frame):
    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wx.Frame.__init__(self, id=wxID_FRAME2, name='', parent=prnt,
              pos=wx.Point(271, 260), size=wx.Size(399, 311),
              style=wx.DEFAULT_FRAME_STYLE, title='Frame2')
        self.SetClientSize(wx.Size(391, 284))

        self.panel1 = wx.Panel(id=wxID_FRAME2PANEL1, name='panel1', parent=self,
              pos=wx.Point(0, 0), size=wx.Size(391, 284),
              style=wx.TAB_TRAVERSAL)
        self.panel1.SetExtraStyle(0)
        self.calendarCtrl1 = wx.calendar.CalendarCtrl(date=wx.DateTime.Now(),
              id=wxID_FRAME2CALENDARCTRL1, name='calendarCtrl1',
              parent=self.panel1, pos=wx.Point(32, 8), size=wx.Size(328, 145),
              style=wx.calendar.CAL_SHOW_HOLIDAYS)
        self.calendarCtrl1.Bind(wx.EVT_LEFT_DCLICK,
              self.OnCalendarCtrl1LeftDclick)
        self.textCtrl1 = wx.TextCtrl(id=wxID_FRAME2TEXTCTRL1, name='textCtrl1',
              parent=self.panel1, pos=wx.Point(32, 168), size=wx.Size(328, 86),
              style=wx.TE_MULTILINE, value=u'')
        self.textCtrl1.Bind(wx.EVT_KEY_UP, self.OnTextCtrl1KeyUp)
        self.textCtrl1.Bind(wx.EVT_TEXT, self.OnTextCtrl1Text,
              id=wxID_FRAME2TEXTCTRL1)

    def __init__(self, parent):
        self._init_ctrls(parent)

    def OnCalendarCtrl1LeftDclick(self, event):
        self.Destroy()
        event.Skip()

    def OnTextCtrl1Text(self, event):
        inputbox = self.textCtrl1
        print self.textCtrl1.GetInsertionPoint(), self.textCtrl1.GetValue()
        event.Skip()
=====
 	  	 

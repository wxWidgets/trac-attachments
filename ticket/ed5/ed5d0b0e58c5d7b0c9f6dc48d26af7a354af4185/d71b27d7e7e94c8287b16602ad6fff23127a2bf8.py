import wx
import wx.calendar

class MyPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1)

        self.SetAutoLayout(1)

        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer1 = wx.BoxSizer(wx.HORIZONTAL)
        s1 = wx.StaticText( self, -1, "v", style = wx.ALIGN_RIGHT)
        sizer1.Add(s1,1, wx.EXPAND|wx.LEFT,5)
        s2 = wx.StaticText( self, -1, "v", size=(144,-1), style = wx.ALIGN_RIGHT)
        sizer1.Add(s2,0, wx.EXPAND|wx.RIGHT,8)
        sizer.Add(sizer1,0, wx.EXPAND)

        cal = wx.calendar.CalendarCtrl(self, -1, wx.DateTime_Now(), pos = (25,50),
                             style = wx.calendar.CAL_SHOW_HOLIDAYS
                             | wx.calendar.CAL_SUNDAY_FIRST
                             | wx.calendar.CAL_SEQUENTIAL_MONTH_SELECTION
                             )

        sizer.Add(cal,0,wx.EXPAND)
        self.SetSizer(sizer)
        sizer.Fit(self)

class MyFrame(wx.Frame):
    def __init__(self, parent):
        wx.Frame.__init__(self, parent, -1, size=(260,180))
        self.MyPanel = MyPanel(self)

def main():
    app = wx.PySimpleApp()
    f = MyFrame(None)
    f.Show()
    app.MainLoop()

if __name__ == '__main__':
    main()


 	  	 

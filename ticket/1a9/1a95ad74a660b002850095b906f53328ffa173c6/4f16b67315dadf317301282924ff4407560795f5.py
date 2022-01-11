import sys
import wx


class ButtonBug(wx.Frame):
    def __init__(self, parent, id, **kwds):
        kwds['style'] = wx.MINIMIZE_BOX | wx.MAXIMIZE_BOX | wx.RESIZE_BORDER | wx.SYSTEM_MENU | wx.CAPTION
        wx.Frame.__init__(self, parent, id, "ButtonBug", **kwds)

        self.cboBug = wx.ComboBox(self, -1, choices=[\
            "1",\
            "2",\
            "3",\
            "4",\
            "5",\
            "6",\
            "7",\
            "8",\
            "9",\
            "10",\
            "11",\
            "12",\
            "13",\
            ], style=wx.CB_DROPDOWN|wx.CB_READONLY)
        self.cboBug.SetValue("1")

        wx.EVT_COMBOBOX(self, self.cboBug.GetId(), self.BugChanged)
        szrMain = wx.BoxSizer(wx.VERTICAL)
        szrMain.Add(self.cboBug ,0,wx.ALL,5)
        self.SetAutoLayout(1)
        self.SetSizer(szrMain)
        szrMain.Fit(self)
        szrMain.SetSizeHints(self)
        self.Layout()
        self.Centre()
        return
        
    def BugChanged(self, *evt):
        print "self.cboBug.GetStringSelection() = " + self.cboBug.GetStringSelection()
        print "self.cboBug.GetValue() = " + self.cboBug.GetValue()
        return
        
app = wx.PySimpleApp()
frame = ButtonBug(None,-1)
frame.Show()
app.MainLoop()

 	  	 

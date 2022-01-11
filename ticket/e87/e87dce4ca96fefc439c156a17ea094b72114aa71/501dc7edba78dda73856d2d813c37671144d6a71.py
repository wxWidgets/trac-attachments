'''
Sample code showing text color problem with wx.SearchCtrl when
setting the text value using ChangeText() or SetText()

Two buttons are presented to first see the problem, and then a workaround solution.
The workaround solution was provided by Robin Dunn.
http://groups.google.com/group/wxpython-users/browse_thread/thread/6e999b3013e383f6

The problem is that calling ChangeValue(new_text) on the empty SearchCtrl causes the
text to update, but it doesn't change from the lighter color of text.  It then remains
in that state until the SearchCtrl is cleared and loses focus.
'''

import wx

class MyFrame(wx.Frame):
    def __init__(self, parent):
        wx.Frame.__init__(self, parent, title='Set SearchCtrl Value')
        self.panel = wx.Panel(self)
        self.bad_button = wx.Button(self.panel, -1, 'Click me first to see the problem')
        self.good_button = wx.Button(self.panel, -1, 'Click me to see the workaround')
        self.search = wx.SearchCtrl(self.panel)
        self.static = wx.StaticText(self.panel, -1, 'Type string here:')
        self.text = wx.TextCtrl(self.panel, -1, 'I was here')
        # Layout
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(self.search)
        sizer.Add(self.bad_button)
        sizer.Add(self.good_button)
        sizer.Add(self.static)
        sizer.Add(self.text)
        self.panel.SetSizer(sizer)
        sizer2 = wx.BoxSizer()
        sizer2.Add(self.panel, 1, wx.EXPAND, 0)
        self.SetSizer(sizer2)
        # Bind events
        self.Bind(wx.EVT_BUTTON, self.OnBadButton, self.bad_button)
        self.Bind(wx.EVT_BUTTON, self.OnGoodButton, self.good_button)

    def OnBadButton(self, event):
        self.search.ChangeValue(self.text.Value)
    
    def OnGoodButton(self, event):
        self.search.ChangeValue(self.search.GetDescriptiveText())
        wx.CallAfter(self.doPart2)

    def doPart2(self):
        self.search.SetFocus()
        self.search.ChangeValue(self.text.Value) 

if __name__ == '__main__':
    app = wx.PySimpleApp()
    frame = MyFrame(None)
    app.SetTopWindow(frame)
    frame.Show()
    frame.Center()
    frame.Raise()
    app.MainLoop() 
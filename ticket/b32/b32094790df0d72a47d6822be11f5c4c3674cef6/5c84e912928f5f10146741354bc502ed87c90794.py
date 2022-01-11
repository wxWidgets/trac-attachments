#!/usr/bin/env python2

import wx

app = wx.App()
frame = wx.Frame(None)

panel = wx.Panel(frame)
box = wx.BoxSizer(wx.HORIZONTAL)
panel.SetSizer(box)

def test1():
    text = wx.StaticText(panel, label='Test')
    box.Add(text)

    date = wx.DatePickerCtrl(panel)
    box.Add(date)

def test2():
    pane = wx.CollapsiblePane(panel)
    # The border triggers the error
    box.Add(pane, flag=wx.BOTTOM, border=4)

#test1()
test2()

print('AAA')
# Gtk-CRITICAL **: IA__gtk_widget_set_size_request: assertion 'height >= -1' failed
panel.Layout()
print('BBB')

frame.Show()
frame.Centre()
app.MainLoop()

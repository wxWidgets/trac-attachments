# -*- coding: utf-8 -*-
import wx


class MouseTestFrame (wx.Frame):
    def __init__(self, parent):
        wx.Frame.__init__ (self, parent, id = wx.ID_ANY, title = u"UIActionSimulator Bug Test", pos = wx.DefaultPosition, size = wx.Size(500,301), style = wx.DEFAULT_FRAME_STYLE|wx.TAB_TRAVERSAL)

        self.SetSizeHintsSz(wx.DefaultSize, wx.DefaultSize)
        self.action_simulator = wx.UIActionSimulator( )

        szr_main = wx.BoxSizer(wx.VERTICAL)

        szr_buttons = wx.BoxSizer(wx.HORIZONTAL)

        self.btn_test = wx.Button(self, wx.ID_ANY, u"Press Me", wx.DefaultPosition, wx.DefaultSize, 0)
        self.btn_test.SetDefault()
        self.btn_test.Bind(wx.EVT_BUTTON, self.on_btn_test)
        szr_buttons.Add(self.btn_test, 0, wx.ALL, 5)


        szr_buttons.AddSpacer((0, 0), 1, wx.EXPAND, 5)

        self.btn_simulate = wx.Button(self, wx.ID_ANY, u"Press for simulated click", wx.DefaultPosition, wx.DefaultSize, 0)
        self.btn_simulate.Bind(wx.EVT_BUTTON, self.on_btn_simulate)
        szr_buttons.Add(self.btn_simulate, 0, wx.ALL, 5)


        szr_main.Add(szr_buttons, 0, wx.EXPAND, 5)

        self.tc_log = wx.TextCtrl(self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, wx.TE_MULTILINE|wx.TE_READONLY)
        szr_main.Add(self.tc_log, 1, wx.ALL|wx.EXPAND, 5)


        self.SetSizer(szr_main)
        self.Layout()

        self.Centre(wx.BOTH)


    def on_btn_test(self, event):
        self.tc_log.WriteText('Left mouse press registered\n')


    def on_btn_simulate(self, event):
        coords = self.btn_test.GetPosition()
        size = self.btn_test.GetSize()
        self.WarpPointer((coords.x + (size.x / 2)), (coords.y + (size.y / 2 )))
        self.action_simulator.MouseClick(button = wx.MOUSE_BTN_LEFT)



if __name__ == '__main__':
    app = wx.App(False)
    frame = MouseTestFrame(None)
    frame.Show(True)
    app.MainLoop()
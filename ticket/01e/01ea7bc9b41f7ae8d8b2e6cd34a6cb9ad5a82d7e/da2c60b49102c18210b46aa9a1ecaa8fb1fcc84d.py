#! Python
# -*- coding: utf-8 -*-

import wx
appl = wx.App(False)
frm = wx.Frame(None, -1, "test wx.ComboBox + Tooltip")
pnl = wx.Panel(frm)

def newToolTip(evt):
    comboBox3.SetToolTip(wx.ToolTip(u"new SetToolTip"))

def SetTip(evt):
    comboBox3.ToolTip.SetTip("SetTip only")


comboBox1 = wx.ComboBox(pnl, -1, u"combo 1", (-1, -1), (-1, -1), ["combo 1"], wx.CB_DROPDOWN)
comboBox1.SetToolTip(wx.ToolTip(u"tooltip 1"))

comboBox2 = wx.ComboBox(pnl, -1, u"combo 2", (-1, -1), (-1, -1), ["combo 2"], wx.CB_DROPDOWN)
comboBox2.SetToolTip(wx.ToolTip(u"original tooltip 2"))
comboBox2.ToolTip.SetTip("CHANGED tooltip 2")
# by now the down-arrow shows shows the changed tooltip, while the text control has the previous one

comboBox3 = wx.ComboBox(pnl, -1, u"combo 3", (-1, -1), (-1, -1), ["combo 3"], wx.CB_DROPDOWN)
comboBox3.SetToolTip(wx.ToolTip(u"tooltip 3"))

btn1 = wx.Button(pnl, -1, u"new ToolTip3", (-1, -1), (-1, -1))
btn1.Bind(wx.EVT_BUTTON, newToolTip)

btn2 = wx.Button(pnl, -1, u"setTip3", (-1, -1), (-1, -1))
btn2.Bind(wx.EVT_BUTTON, SetTip)


sizerFrm = wx.BoxSizer(wx.HORIZONTAL)
sizerFrm.Add(btn1, 0)
sizerFrm.Add(btn2, 0)
sizerFrm.Add(comboBox1, 1)
sizerFrm.Add(comboBox2, 1)
sizerFrm.Add(comboBox3, 1)

pnl.SetSizer(sizerFrm)
frm.Show(1)
appl.MainLoop()

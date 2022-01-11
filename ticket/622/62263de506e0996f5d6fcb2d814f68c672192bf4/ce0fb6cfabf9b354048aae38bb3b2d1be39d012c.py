#!/usr/bin/env python

import wx

class MCDialog(wx.Dialog):
    def __init__(self, parent, msg, title, lst, pos = wx.DefaultPosition,
                 size = (200,200), style = wx.DEFAULT_DIALOG_STYLE):
        wx.Dialog.__init__(self, parent, -1, title, pos, size, style)
        
        x, y = pos
        if x == -1 and y == -1:
            self.CenterOnScreen(wx.BOTH)

        stat = wx.StaticText(self, -1, msg)
        self.lctrl = wx.ListCtrl(self, -1, wx.DefaultPosition,
                wx.DefaultSize, wx.LC_REPORT|wx.LC_NO_HEADER)
        self.lctrl.InsertColumn(0, "")
        import sys
        for name in lst:
            self.lctrl.InsertStringItem(sys.maxint, name)

        ok = wx.Button(self, wx.ID_OK, "OK")
        cancel = wx.Button(self, wx.ID_CANCEL, "Cancel")
        
        ok.SetDefault()
        dlgsizer = wx.BoxSizer(wx.VERTICAL)
        dlgsizer.Add(stat, 0, wx.ALL, 4)
        dlgsizer.Add(self.lctrl, 1, wx.EXPAND|wx.ALL, 4)
        
        btnsizer = wx.StdDialogButtonSizer()
        btnsizer.AddButton(ok)
        btnsizer.AddButton(cancel)
        btnsizer.Realize()
        dlgsizer.Add(btnsizer, 0, wx.ALL|wx.ALIGN_RIGHT, 4)
        self.SetSizer(dlgsizer)
        self.lst = lst
        self.Layout()
        # Allow for double-clicking an item to add it.
        self.Bind(wx.EVT_LIST_ITEM_ACTIVATED, self.Quit, self.lctrl)
        

    def Quit(self, event = None):
        self.EndModal(wx.ID_OK)
        return

    def GetValue(self):
        selections = []
        item = self.lctrl.GetFirstSelected()
        while item != -1:
            selections.append(item)
            item = self.lctrl.GetNextSelected(item)
        return selections

    def GetValueString(self):
        selections = self.GetValue()
        val = [ self.lst[i] for i in selections ]
        return tuple(val)

 	  	 

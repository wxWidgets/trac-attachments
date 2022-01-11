# -*- coding: utf-8 -*-#
#-----------------------------------------------------------------------------
#!/usr/bin/env python

import wx


class Dialog1(wx.Dialog):
    def _init_ctrls(self, *args, **kwds):
        super(Dialog1, self).__init__(*args, **kwds)

        # following line causes on Ubuntu that klicking "X" on title bar doesn't close
        self.SetExtraStyle(wx.WS_EX_VALIDATE_RECURSIVELY)

    def __init__(self, parent, *args, **kwds):
        self._init_ctrls(parent, title="Dialog",
                                *args, **kwds)

        sizer = wx.BoxSizer(wx.VERTICAL)

        btn = wx.Button(self, wx.ID_CANCEL, "Cancel")
        sizer.Add(btn)
        self.SetSizer(sizer)


if __name__ == '__main__':
    app = wx.PySimpleApp()
    dlg = Dialog1(None)
    try:
        dlg.ShowModal()
    finally:
        dlg.Destroy()
    app.MainLoop()

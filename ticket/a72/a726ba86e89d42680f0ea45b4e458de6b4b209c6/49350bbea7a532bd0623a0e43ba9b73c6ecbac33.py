#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import wx

class mDataListCtrl(wx.ListCtrl):

    def __init__(self, parent, id):
        wx.ListCtrl.__init__(self, parent, id, style=wx.LC_REPORT|wx.LC_VIRTUAL|wx.LC_HRULES|wx.LC_VRULES|wx.LC_SINGLE_SEL)

        self.InsertColumn(0, "Descripcion")
        self.InsertColumn(1, "Número")
        self.SetItemCount(0)

        self.mdata = []
        for x in range(100):
            self.mdata.append(("line %s" % x, str(x)))
                        
        self.filldata()

    def OnGetItemText(self, item, col):
        print "GetItem %d %d" % (item, col)
        return self.mdata[item][col]
    
    def OnGetItemImage(self, item):
        return -1
    
    def OnGetItemAttr(self, item):
        return None

    def filldata(self):
        self.DeleteAllItems()
        self.SetItemCount(100)
        self.Select(0)        
        
    

class mFrame(wx.Frame):
    def __init__(self, *args, **kwds):
        kwds["style"] = wx.DEFAULT_FRAME_STYLE
        wx.Frame.__init__(self, *args, **kwds)
        
        sizer_frame = wx.BoxSizer(wx.HORIZONTAL)
        self.SetSizer(sizer_frame)
        
        self.panel = wx.Panel(self, -1)
        sizer_frame.Add(self.panel, 1, wx.EXPAND, 0)        
        
        sizer_panel = wx.BoxSizer(wx.VERTICAL)
        self.panel.SetSizer(sizer_panel)

        sizer_cabecera = wx.StaticBoxSizer(wx.StaticBox(self.panel, -1, ""), wx.HORIZONTAL)
        sizer_panel.Add(sizer_cabecera, 0, wx.EXPAND)
        
        self.label_1 = wx.StaticText(self.panel, -1, "Buscar : ")
        self.fil_valor = wx.TextCtrl(self.panel, -1, "", style=wx.TE_PROCESS_ENTER )

        sizer_cabecera.Add(self.label_1, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL, 3)
        sizer_cabecera.Add(self.fil_valor, 1, wx.ALL|wx.EXPAND, 3)

        self.lista = mDataListCtrl(self.panel, -1)
        sizer_panel.Add(self.lista, 2, wx.EXPAND)
        
        self.btn = wx.Button(self.panel, -1, "Fill and SetFocus")
        sizer_panel.Add(self.btn,0)
        
        self.btn2 = wx.Button(self.panel, -1, "SetFocus")
        sizer_panel.Add(self.btn2,0)

        
        sizer_frame.SetSizeHints(self)
        sizer_frame.Fit(self)
        self.SetAutoLayout(True)
        self.Layout()
        
        self.SetSize((500, 350))

        self.btn.Bind(wx.EVT_BUTTON, self.OnBtnFill)
        self.btn2.Bind(wx.EVT_BUTTON, self.OnBtnSetFocus)
        
    def OnBtnFill(self, evt):
        self.lista.filldata()
        self.lista.SetFocus()
        
        evt.Skip()
        
    def OnBtnSetFocus(self, evt):
        self.lista.SetFocus()
        evt.Skip()
        
        
if __name__ == "__main__":
    app = wx.PySimpleApp(0)
    wx.InitAllImageHandlers()

    frame_1 = mFrame(None, -1, "")
    app.SetTopWindow(frame_1)
    frame_1.Show()

    app.MainLoop()


 	  	 

#!/usr/bin/env python

from wxPython.wx import *

class Dialog(wxDialog):
    def __init__(self):
        wxDialog.__init__(self,None,-1,"x",size=(500,400))
        self.lv=wxListCtrl(self,style=wxLC_REPORT|wxLC_SINGLE_SEL,pos=(0,0),size=(500,350))
        self.lv.InsertColumn(0,"TEST",format=wxLIST_FORMAT_RIGHT)
        self.bt=wxButton(self,-1,"x",pos=(0,350),size=(500,30))
        EVT_BUTTON(self.bt,self.bt.GetId(),self.onClick)
    def onClick(self,event):
        while self.lv.GetItemCount():
            self.lv.DeleteAllItems()
        for i in xrange(8000):
            self.lv.InsertStringItem(i,"the Item")
        for i in xrange(self.lv.GetItemCount()):
            self.lv.SetItemData(i,42)

class App(wxApp):
    def OnInit(self):
        d=Dialog()
        d.ShowModal()
        d.Destroy()
        return 1

app=App()
app.MainLoop()

 	  	 

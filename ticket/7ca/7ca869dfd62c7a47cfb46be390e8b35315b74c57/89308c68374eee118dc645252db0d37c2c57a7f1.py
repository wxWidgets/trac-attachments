#!/usr/local/bin/python2.4

import wx
import os

class Base(wx.Frame):
    def __init__(self,parent=None,id=wx.ID_ANY):
        wx.Frame.__init__(self,parent,id)
        #The extension should be "XPMP" in uppercase
        defaultFileName = "example" + ".XPMP"
        print defaultFileName
        saveDialog = wx.FileDialog(self, message="Save as:",
                  defaultDir=os.getcwd(), defaultFile=defaultFileName,
                  wildcard="XPMP",
                  style=wx.SAVE | wx.FD_OVERWRITE_PROMPT | wx.FD_CHANGE_DIR)
        if saveDialog.ShowModal()==wx.ID_OK:
            fileName=saveDialog.GetPath()
            saveDialog.Destroy()
            #The file name has been changed to "example.xpmp", lowercase extension
            print fileName
            self.Destroy()
        else:
            saveDialog.Destroy()
            self.Destroy()

app=wx.PySimpleApp()
frame = Base()
frame.Show()
app.MainLoop()
 	  	 

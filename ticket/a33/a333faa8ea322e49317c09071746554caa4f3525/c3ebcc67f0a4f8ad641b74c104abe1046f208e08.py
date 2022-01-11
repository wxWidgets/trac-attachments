# coding: utf8

from __future__ import absolute_import, division, print_function, unicode_literals

import wx

SPACE_OUT = 10
SPACE_VERT = 5
SPACE_HOR = 10


class MyFrameName(wx.Frame):

	def __init__(self,parent,id):
		wx.Frame.__init__(self,parent,id,title='Labels demo', size=(640,480))
		self.Bind(wx.EVT_CLOSE, self.onQuit)
		self.Centre()
		panel = wx.Panel(self)
		mainSizer = wx.GridSizer(cols=1)
		vbox = wx.BoxSizer(wx.VERTICAL)
		
		hbox = wx.BoxSizer(wx.HORIZONTAL)
		self.myLabel = wx.StaticText(panel, label='Label for spin control')
		hbox.Add(self.myLabel)
		hbox.AddSpacer(SPACE_HOR)
		self.mySpinCtrl = wx.SpinCtrl(panel)
		hbox.Add(self.mySpinCtrl)
		vbox.AddSpacer(SPACE_VERT)
		vbox.Add(hbox, border=SPACE_OUT, flag=wx.ALL|wx.EXPAND, proportion=1)
		
		hbox = wx.BoxSizer(wx.HORIZONTAL)
		self.myLabel2 = wx.StaticText(panel, label='Label for spin control double')
		hbox.Add(self.myLabel2)
		hbox.AddSpacer(SPACE_HOR)
		self.mySpinCtrlDouble = wx.SpinCtrlDouble(panel)
		hbox.Add(self.mySpinCtrlDouble)
		vbox.AddSpacer(SPACE_VERT)
		vbox.Add(hbox, border=SPACE_OUT, flag=wx.ALL|wx.EXPAND, proportion=1)
		
		hbox = wx.BoxSizer(wx.HORIZONTAL)
		self.myLabel3 = wx.StaticText(panel, label='Label for text control')
		hbox.Add(self.myLabel3)
		hbox.AddSpacer(SPACE_HOR)
		self.myEdit = wx.TextCtrl(panel)
		hbox.Add(self.myEdit)
		vbox.AddSpacer(SPACE_VERT)
		vbox.Add(hbox, border=SPACE_OUT, flag=wx.ALL|wx.EXPAND, proportion=1)
		
		#Bouton fermer
		self.closeBtn = wx.Button(panel, id=wx.ID_CLOSE, label="&Close")
		self.Bind(wx.EVT_BUTTON, self.onQuit, self.closeBtn)
		vbox.Add(self.closeBtn, flag=wx.ALIGN_CENTER)
		mainSizer.Add(vbox, border=SPACE_OUT, flag=wx.ALL|wx.EXPAND, proportion=1)
		panel.SetSizer(mainSizer)
		
	def onQuit(self,event):
		self.closeBtn.SetFocus()
		self.Destroy()


if __name__=='__main__':
	app = wx.App()
	frame=MyFrameName(parent=None,id=-1)
	frame.Show()
	app.MainLoop()
	#print('toto')

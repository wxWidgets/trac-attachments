#!/usr/bin/python

import wx
import wx.stc

class MainPanel(wx.Panel):

	def __init__(me,parent):
		wx.Panel.__init__(me,parent)

		sz=wx.BoxSizer(wx.VERTICAL)
		sz.Add(wx.stc.StyledTextCtrl(me),1,wx.EXPAND)
		me.SetSizer(sz)
		
		me.Bind(wx.stc.EVT_STC_PAINTED, me.OnTextPainted)
		
	def OnTextPainted(me,e):
		# this call causes a "CGContextRestoreGState: invalid context"
		me.GetParent().SetStatusText('text')
		print 'setting'	
		
		
class MainFrame(wx.Frame):
	def __init__(me):
		wx.Frame.__init__(me,parent=None)
		me.SetStatusBar(wx.StatusBar(me))
		me.panel=MainPanel(parent=me)
		
		

app = wx.PySimpleApp()
frame = MainFrame()
frame.Show()
frame.Centre()
app.MainLoop()
 	  	 

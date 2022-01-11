#!/usr/bin/env python
import wx
from wx import glcanvas
from OpenGL.GL import glClear, GL_COLOR_BUFFER_BIT



class fooDialog(wx.Dialog):
	def __init__(self, parent, id=-1, **opts):
		wx.Dialog.__init__(self, parent, id, **opts)
		btn = wx.Button(self, wx.ID_OK, " OK ")
		btn.SetDefault()
		wx.EVT_BUTTON(self, wx.ID_OK, self.OnOK)

 	def OnOK(self, event=None):
		print "start OK"
		self.EndModal(wx.ID_OK)
		print "OK"	
		
class GraphGL(glcanvas.GLCanvas):

	def __init__(self, parent):
		glcanvas.GLCanvas.__init__(self, parent, -1)
		self.Bind(wx.EVT_PAINT, self.OnDraw)
		wx.EVT_CHAR(self, self.OnKey)

	def OnKey(self, event):
		foo=fooDialog(self)
		print "launching"
		q=foo.ShowModal()
		print "returned"
		print q	

	def OnDraw(self, event=None):
		self.SetCurrent()
		glClear(GL_COLOR_BUFFER_BIT)
		self.SwapBuffers()

		
	

app = wx.PySimpleApp()
#bar = {'size':(600,600), 'style':wx.DEFAULT_FRAME_STYLE|wx.NO_FULL_REPAINT_ON_RESIZE}
frame = wx.Frame(None, -1, "Test")
frame.g = GraphGL(frame)
frame.Show(True)
app.MainLoop()


 	  	 

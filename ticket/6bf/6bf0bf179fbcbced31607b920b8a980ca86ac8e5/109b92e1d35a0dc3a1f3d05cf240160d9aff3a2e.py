import wx

class MyControl(wx.PyControl):
	def __init__(self, parent, size):
		wx.PyControl.__init__(self, parent, style=wx.BORDER_NONE)
		self.Bind(wx.EVT_PAINT, self.OnPaint)
		self.Bind(wx.EVT_ERASE_BACKGROUND, self.OnEraseBackground)
		self.SetInitialSize(size)

	def OnPaint(self, event):
		dc = wx.BufferedPaintDC(self)
		dc.Clear()
		dc.DrawText("A", 0, 0)

	def OnEraseBackground(self, event):
		pass

class GUI(object):
	def __init__(self):
		app = wx.App(False)
		windowFrame = wx.Frame(None)
		windowFrame.SetSize((300, 300))

		notebook = wx.Notebook(windowFrame, style=wx.NB_TOP)
		tab1 = wx.Panel(notebook)
		tab1Sizer = wx.BoxSizer(wx.VERTICAL)
		tab1.SetSizer(tab1Sizer)
		notebook.AddPage(tab1, "Tab1")

		tab2 = wx.Panel(notebook)
		notebook.AddPage(tab2, "Tab2")

		myControl1 = MyControl(tab1, size=(20,20))
		tab1Sizer.Add(myControl1)
		myControl2 = MyControl(tab1, size=(20,20))
		tab1Sizer.Add(myControl2)
		label3 = wx.StaticText(tab1, label="Test3")
		tab1Sizer.Add(label3)

		windowFrame.Show()
		#This is a workaround for the bug
		#myControl2.Refresh()
		app.MainLoop()

def main():
	GUI()

main()

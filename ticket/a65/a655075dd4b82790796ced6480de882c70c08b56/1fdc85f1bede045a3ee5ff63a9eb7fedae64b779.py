import wxversion
wxversion.select("2.8")
import wx, wx.html

enableBug=True

aboutText = """<p>Modal Dialog bug demo program</p>"""

class Frame(wx.Frame):
	def __init__(self, title):
		wx.Frame.__init__(self, None, title=title, pos=(150,150), size=(350,200))
		
		menuBar = wx.MenuBar()
		menu = wx.Menu()
		m_dialog = menu.Append(-1, "&Dialog\tAlt-D", "Open dialog.")
		m_exit = menu.Append(wx.ID_EXIT, "E&xit\tAlt-X", "Close window and exit program.")
		self.Bind(wx.EVT_MENU, self.OnDialog, m_dialog)
		menuBar.Append(menu, "&File")
		menu = wx.Menu()
		self.SetMenuBar(menuBar)

		panel = wx.Panel(self)
		panel.Layout()
		self.ppanel=panel;
		
		self.ppanel.Bind(wx.EVT_PAINT, self.onPanelPaint)
	
	def OnDialog(self,evt):
		dlg=TestDialog(self)
		mret=dlg.ShowModal()
		print "ShowModal returned:",mret

	def onPanelPaint(self, e):
		#do some drawing here
		pdc=wx.PaintDC(self)
		#if we do not skip this event, dialog will not exit from modal
		if not enableBug:
			e.Skip();
		

class TestDialog(wx.Dialog):

	def __init__(self, parent):
		wx.Dialog.__init__(self, parent, -1, "Test modal") 
		self.InitUI()
		self.SetSize((250, 200))

	def InitUI(self):
		pnl = wx.Panel(self)
		vbox = wx.BoxSizer(wx.VERTICAL)

		sb = wx.StaticBox(pnl, label='Simple data')
		sbs = wx.StaticBoxSizer(sb, orient=wx.VERTICAL)
	   
		hbox2 = wx.BoxSizer(wx.HORIZONTAL)
		okButton = wx.Button(self, label='Ok')
		closeButton = wx.Button(self, label='Close')
		hbox2.Add(okButton)
		hbox2.Add(closeButton, flag=wx.LEFT, border=5)
		self.btnsizer=hbox2
		
		vbox.Add(pnl, proportion=1, 
			flag=wx.ALL|wx.EXPAND, border=5)
		vbox.Add(hbox2, 
			flag=wx.ALIGN_CENTER|wx.TOP|wx.BOTTOM, border=10)

		self.SetSizer(vbox)
		
		okButton.Bind(wx.EVT_BUTTON, self.OnOk)
		closeButton.Bind(wx.EVT_BUTTON, self.OnCancel)
		
		
	def OnOk(self, e):
		print "Ok clicked"
		self.EndModal(wx.ID_OK)
		
	def OnCancel(self, e):
		print "Cancel clicked"
		self.EndModal(wx.ID_CANCEL)


app = wx.App(redirect=False)   # Error messages go to command line
top = Frame("ModalTest")
top.Show()
app.MainLoop()
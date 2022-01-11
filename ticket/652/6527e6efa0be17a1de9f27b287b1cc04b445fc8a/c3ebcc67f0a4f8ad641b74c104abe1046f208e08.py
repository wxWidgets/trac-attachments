import wx

class MainFrame(wx.Frame):
	def __init__(self, parent, id, title):
		wx.Frame.__init__(self, parent, id, title, size = (800,600))
		
		LoginPanel = wx.Panel(self, -1)

		#~ #Make menu items
		ReportMenu = wx.Menu()
		
		Daily = wx.MenuItem(ReportMenu,wx.NewId(),"&Daily")
		ReportMenu.AppendItem(Daily)
		
		Menu = wx.MenuBar()
		Menu.Append(ReportMenu,'Reports')
		#Set the menu bar
		self.SetMenuBar(Menu)
		
		print dir(self)
		#self.Bind(self.wx.EVT_MENU, self.ReportForm, Daily)

		#setup panel sizer
		StaticBox2 = wx.StaticBox(LoginPanel,-1,"sub box")
		StaticBoxSizer2 = wx.StaticBoxSizer(StaticBox2,wx.VERTICAL)
		StaticBoxSizer2.Add(wx.TextCtrl(self,-1,"SECOND LAYER STATIC BOX SIZER"))
		
		StaticBox = wx.StaticBox(LoginPanel,-1,"Login")
		StaticBoxSizer = wx.StaticBoxSizer(StaticBox,wx.VERTICAL)
		StaticBoxSizer.Add(wx.TextCtrl(self,-1,"FIRST LAYER STATIC BOX SIZER"))
		StaticBoxSizer.Add(StaticBoxSizer2)

		LoginPanel.SetSizer(StaticBoxSizer)
		self.SendSizeEvent()
		LoginPanel.Fit()
		
class App(wx.App):
	"""This class is the application handle for wxPython"""
	def OnInit(self):
		frame = MainFrame(None, -1, 'exmaple')
		frame.Show(True)
		return True
		
		
def Main():
	"""Main function, the last thing to run, runs 
	the wxPython application in a loop"""
	App().MainLoop()

Main()

 	  	 

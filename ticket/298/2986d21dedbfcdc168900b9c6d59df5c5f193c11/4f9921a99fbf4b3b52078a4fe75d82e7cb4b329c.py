import wx
from PIL import Image

class Window(wx.Frame):
	def __init__(self):
		wx.Frame.__init__(self,None,-1,'wx.TaskBarIcon Test')
		
		
		self.menu = wx.Menu()
		self.menu.Append(1000,'Exit')
		self.menu.Bind(wx.EVT_MENU,self.OnExit, id=1000)
		
		
		self.tray_icon = wx.TaskBarIcon()

		image = apply(wx.EmptyImage, Image.open('icon.png', 'r').size)
		image.SetData(Image.open('icon.png', 'r').convert('RGB').tostring())
		image.SetAlphaData(Image.open('icon.png', 'r').convert('RGBA').tostring()[3::4])
		image = image.ConvertToBitmap()
		
		icon = wx.EmptyIcon()
		icon.CopyFromBitmap(image)
		self.tray_icon.SetIcon(icon)
		self.tray_icon.Bind(wx.EVT_TASKBAR_RIGHT_UP,self.OnIconRight)
		
		self.Show()
		
		
	def OnIconRight(self, event):
		self.tray_icon.PopupMenu(self.menu)
		
	def OnExit(self, event):
	
		import pdb; pdb.set_trace()
	
		self.tray_icon.Destroy()
		self.Destroy()	
	
	
app = wx.PySimpleApp()
Window()
app.MainLoop()
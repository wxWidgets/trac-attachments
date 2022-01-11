import wx
import wx.lib.iewin_old as iewin
class Frame(wx.Frame):
	def __init__(self, parent = None, id= -1, pos = wx.DefaultPosition, title = "Hello, wxPython!"):
		wx.Frame.__init__(self, parent, id, title, pos, size=(600,800))
		self.html = iewin.IEHtmlWindow(self, -1, size = (600, 800),\
                                               style = wx.NO_FULL_REPAINT_ON_RESIZE)
		self.html.Navigate(r'http://www.google.com')
		sizer = wx.BoxSizer(wx.VERTICAL)
		sizer.Add(self.html, 1, wx.EXPAND | wx.ALIGN_CENTER, 0)
		self.SetSizer(sizer)

class Joystick:
        def __init__(self, window):
                self.__window = window
                joystick = wx.Joystick(wx.JOYSTICK1)
                self.joystick = joystick
                joystick.SetCapture(window, 20)
                wx.EVT_JOYSTICK_EVENTS(window, self.OnJoystick)

        def OnJoystick(self, event):
                #print 'OnJoystick...'
                pov = self.joystick.GetPOVPosition()
                if pov != 65535:
                        print pov
                
class App(wx.App):
	def OnInit(self):
		self.frame = Frame()
		self.frame.Show()
		self.SetTopWindow(self.frame)
		self.joystick = Joystick(self.frame)
		return True
                
def main():
	app = App()
	app.MainLoop()
	
if __name__ == '__main__':
	main()

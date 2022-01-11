from wxPython.wx import *
import threading


# -----------------------------------------------------------------------

class Test:
	def __call__(self):
		while 1:
			pass

th = threading.Thread( None, Test() )
th.start()


# -----------------------------------------------------------------------

class MyApp(wxApp):
	def OnInit(self):
		frame = MyFrame()
		frame.Show(true)
		self.SetTopWindow(frame)

		return true

class MyFrame(wxFrame):

	def __init__(self):
		wxFrame.__init__(self, None, wxNewId(), "Thread test" )

		#EVT_IDLE(self, self.OnCrash)	# Comment this out and watch it run forever

	def OnCrash(self, event):
		# event.RequestMore()		# Will crash much faster with this command enabled
		pass								# Will fail here after a few calls (move mouse around in window to trigger it)
		


app = MyApp(0)
app.MainLoop()	# Crashes in here! 
 	  	 

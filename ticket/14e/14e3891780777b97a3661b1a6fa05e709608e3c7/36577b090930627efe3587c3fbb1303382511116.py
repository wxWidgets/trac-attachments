import wx
from xml.sax import make_parser, handler

class DataReader(handler.ContentHandler):
	#constructor
	def __init__(self):  
		print "Object Created"
	#this is done for every element
	def startElement(self, element, attrs):
		print "Start of Element Encountered"
	# done at the end of the document
	def endDocument(self):
		print "Finished Parsing The Document"

# nothing fancy, just a normal frame
class mainWindow(wx.Frame):
	def __init__(self, parent, title):
		wx.Frame.__init__(self, parent,wx.ID_ANY,title,
			style=wx.DEFAULT_FRAME_STYLE|wx.NO_FULL_REPAINT_ON_RESIZE)
		# make an object
		self.obj = DataReader()
		# the next line causes the program to do a segmentation fault
		self.parser = make_parser()
		self.parser.setContentHandler(self.obj)
		self.parser.parse('data.xml')
		# Put in all the widgets
		self.control = wx.TextCtrl(self,1,style=wx.TE_MULTILINE)
		self.Show(True)
		
class MyApp(wx.App):
	def OnInit(self):
		frame = mainWindow(None, "Test Application")
        	self.SetTopWindow(frame)
	        frame.Show(True)
	        return True
        	
app = MyApp()
app.MainLoop()

 	  	 

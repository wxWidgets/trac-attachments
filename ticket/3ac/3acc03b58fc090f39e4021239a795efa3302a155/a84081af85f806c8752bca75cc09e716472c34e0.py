from wxPython.wx import *
class Dlg(wxDialog):
	def __init__(self, parent):
		wxDialog.__init__(self, parent, -1, 'Test')

	def ShowModal(self):
#		wxDialog.ShowModal(self)
		dlg = wxFileDialog(self,'test')
		dlg.ShowModal()

# GUI canvas area that holds and displays DrawShapes
class DrawCanvas(wxPanel):
	def __init__(self, parent, ID=-1):
		wxScrolledWindow.__init__(self, parent, ID)

		EVT_LEFT_DCLICK(self, self.__OnLeftDClick)

	def __OnLeftDClick(self, evt):
		dlg = Dlg(self)
		dlg.ShowModal()


# APP FOR TESTING PANELS
class TestFrame(wxFrame):
	def __init__(self):
		wxFrame.__init__(self, None, -1, "Spec")

		self.canvas = DrawCanvas(self)
		

if __name__ == '__main__':
	# App for testing panels
	app = wxPySimpleApp()
	frame = TestFrame()
	frame.Show(true)
	app.MainLoop()
	

 	  	 

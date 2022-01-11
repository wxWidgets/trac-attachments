from wxPython.wx import *

[wxID_WXFRAME1] = map(lambda _init_ctrls: wxNewId(), range(1))

class wxFrame1(wxFrame):
   def __init__(self, prnt):
      wxFrame.__init__(self, id=wxID_WXFRAME1, name='', parent=prnt,
            pos=wxPoint(322, 188), size=wxSize(672, 481),
            style=wxDEFAULT_FRAME_STYLE, title='wxFrame1')
      
class MyApp(wxApp):
   def OnInit(self):
      wxInitAllImageHandlers()
      self.main = wxFrame1(None)
      self.SetTopWindow(self.main)
      self.main.Show()
      return True

def main():
   application = MyApp(0)
   application.MainLoop()

if __name__ == '__main__':
   main()

 	  	 

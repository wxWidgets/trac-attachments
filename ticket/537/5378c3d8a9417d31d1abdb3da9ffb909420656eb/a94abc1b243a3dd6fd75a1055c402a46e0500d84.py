from wxPython.wx import *
from wxPython.lib.maskededit import Field, wxMaskedTextCtrl

class myFrame(wxFrame):
  def __init__(self):
    wxFrame.__init__(self, None, -1, 'My Frame', size=wxSize(300,100))
    
    #wxMaskedTextCtrl(self, -1, '', formatcodes='F_',  mask='N{18}, N{18}', demo = True,
    #                 fields = {1 : Field(choices=['Bristol Central', 'Maloney', '789'],
    #                                     choiceRequired=True, formatcodes='_')})
    wxMaskedTextCtrl(self, -1, '', formatcodes='F_',  mask='N{18}, N{18}', demo = True, fields = {1 : Field(choices=['OKString', 'Not OK Digits', 'OKString', 'Platt Tech'], choiceRequired=True)})
                     
if __name__ == '__main__':
  app = wxPySimpleApp(0)
  frame = myFrame()
  app.SetTopWindow(frame)
  frame.Show()  
  app.MainLoop()
 	  	 

############################################################
# IN THIS SAMPLE, I WANT THE 'a' IN BLUE AND THE 'b' IN RED.
############################################################

import wx
import wx.richtext as rt

class DemoApp(wx.App):
  def OnInit(self):
    frame = MainFrame(None, -1, "bugtest")
    frame.Show(True)
    self.SetTopWindow(frame)
    return True

class MainFrame(wx.Frame):
  def __init__(self, *args, **kwds):
    wx.Frame.__init__(self, *args, **kwds)
    txt=MyEdit(self,size=(500,300))
    box=wx.BoxSizer()
    box.Add(txt)
    self.SetSizerAndFit(box)
    return
  
class MyEdit(rt.RichTextCtrl):
  def __init__(self, *args, **kwds):
    kwds["style"] = wx.NO_BORDER|wx.TE_MULTILINE|wx.TE_CHARWRAP|wx.TE_READONLY
    rt.RichTextCtrl.__init__(self, *args, **kwds)
    #choose a bigger font so it stands better :)
    self.SetFont(wx.Font(24,wx.DEFAULT, wx.NORMAL, wx.NORMAL, False,'Arial'))
    #put some text in the control
    self.SetValue("abc\nzzz\n")
    ####################################################
    # I want the letter 'a' in blue and the 'b' in red.
    ####################################################
    self.Color(0,1,rt.RichTextAttr(wx.BLUE)) #bug1: superscript letters 'bc'
    #bug2: if a newline follows, wrong range is taken
    self.Color(1,2,rt.RichTextAttr(wx.RED))
    return
    
  def Color(self,pos1,pos2,attribute):
    rtrange=rt.RichTextRange(pos1,pos2)
    self.SetStyleEx(rtrange,attribute,rt.RICHTEXT_SETSTYLE_CHARACTERS_ONLY)
    return

app = DemoApp()
app.MainLoop()
    
    




 	  	 

import wx
import wx.stc as stc
import win32api

TEXT = """wx.version: 2.9.3.1 msw (classic)

In searching for `self.SetWrapIndentMode(stc.STC_WRAPINDENT_INDENT)`, I came across a bug in StyledTextCtrl's SendMsg.

For a wxPython STC control:

SCI_SETWRAPINDENTMODE = 2472

# This works but results in a memory leak:
# swig/python detected a memory leak of type 'wxIntPtr *', no destructor found.
self.SendMsg(SCI_SETWRAPINDENTMODE, 2)

# This causes an Exception:
# TypeError: in method 'StyledTextCtrl_SendMsg', expected argument 4 of type 'wxIntPtr'
self.SendMsg(SCI_SETWRAPINDENTMODE, 2, 0) 

# This doesn't work.  It seems that self.Handle isn't actually the handle of the STC hwnd.  It doesn't seem possible to get the STC hwnd.
win32api.SendMessage(self.Handle, SCI_SETWRAPINDENTMODE, 2, 0)

-------------------------------------
This should word wrap indented.  This should word wrap indented.  This should word wrap indented.  This should word wrap indented.  This should word wrap indented.  This should word wrap indented.  This should word wrap indented.  This should word wrap indented.  This should word wrap indented.  This should word wrap indented.  This should word wrap indented.  This should word wrap indented.  This should word wrap indented.  This should word wrap indented.  This should word wrap indented.  This should word wrap indented.  This should word wrap indented.  This should word wrap indented.  This should word wrap indented.  This should word wrap indented.

"""

   
class MyFrame(wx.Frame):
   def __init__(self,*args,**kargs):
      wx.Frame.__init__(self,*args,**kargs)
      self.stc = MySTC(self,-1)
      self.Show()
      
class MySTC(stc.StyledTextCtrl):
   def __init__(self,*args,**kargs):
        stc.StyledTextCtrl.__init__(self,*args,**kargs)

        self.SetText(TEXT)

        self.SetWrapMode(stc.STC_WRAP_WORD)

        SCI_SETWRAPINDENTMODE = 2472
        
        # This works but results in a memory leak:
        # swig/python detected a memory leak of type 'wxIntPtr *', no destructor found.
        self.SendMsg(SCI_SETWRAPINDENTMODE, 2)

        # This causes an Exception:
        # TypeError: in method 'StyledTextCtrl_SendMsg', expected argument 4 of type 'wxIntPtr'
#        self.SendMsg(SCI_SETWRAPINDENTMODE, 2, 0) 

        # This doesn't work.  It seems that self.Handle isn't actually the handle of the STC hwnd.  It doesn't seem possible to get the STC hwnd.
#        win32api.SendMessage(self.Handle, SCI_SETWRAPINDENTMODE, 2, 0)

if __name__ == '__main__':
    print wx.version() 
    app = wx.App()
    frame = MyFrame(None,1,'StyledTextCtrl SendMsg Bug',size=(800,600))
    app.MainLoop()

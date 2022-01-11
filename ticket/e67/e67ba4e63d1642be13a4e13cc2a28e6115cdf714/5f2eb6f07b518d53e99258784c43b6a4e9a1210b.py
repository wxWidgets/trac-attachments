import wx


class MyFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self,None)
        #panel = wx.Panel(self)
        self.cb = wx.CheckListBox(self,choices=['test1','test2','test3'])
        self.Bind(wx.EVT_CHECKLISTBOX, self.OnCheck, self.cb)

    def OnCheck(self, event):
        i = event.GetSelection()
        check = event.IsChecked() #<= return False or True all the time !
        print i,'from event:',check
        i = event.GetSelection()
        check = self.cb.IsChecked(i) #<= that works !
        print i,'from control:',check


class MyApp(wx.App):
    def OnInit(self):
        frame = MyFrame()
        frame.Show()
        return True

app = MyApp()
app.MainLoop()

 	  	 

import  wx

combo_values = ['Option1', 'Option2']

class MyFrame(wx.Frame):
    def __init__(self, parent, id, title, pos = wx.DefaultPosition, size = wx.Size(800,600),
                 style = wx.DEFAULT_FRAME_STYLE |wx.WANTS_CHARS , name="test"):
        wx.Frame.__init__(self, parent, id, title, pos, size, style, name)

        psizer = wx.BoxSizer(wx.HORIZONTAL)
        p = wx.Panel(self, -1)

        self.t = wx.TextCtrl(p, -1, size=wx.Size(225,-1), name="misc_business_url")
        self.c = wx.ComboBox(p, -1, "", style=wx.CB_DROPDOWN, name="name_title")
        self.b = wx.Button(p, -1, "Click")
        
        psizer.Add(self.t)
        psizer.Add(self.c)
        psizer.Add(self.b)
        
        self.b.Bind(wx.EVT_BUTTON, self.OnClick)
        p.SetAutoLayout(1)
        p.SetSizerAndFit(psizer)

        for option in combo_values:
            self.c.Append(option)
        
        self.c.SetValue('Option1')
    def OnClick(self, event):
        self.c.SetValue('Option2')
        
if __name__ == '__main__':

   class App(wx.App):
       def OnInit(self):
           self.frame = MyFrame(None, -1, "Test")
           self.frame.Show()
           return True

   app = App(0)
   app.MainLoop()

 	  	 

import wx


class testComboBox(wx.Frame):
    def __init__(self, parent):
        wx.Frame.__init__(self, parent, -1, "Test ComboBox Events", size=(220,220))
        self.SetBackgroundColour(wx.NullColour)
        self.Center(wx.HORIZONTAL|wx.VERTICAL)
        
        self.date_format = wx.ComboBox(choices=['MM-DD-YYYY',
              'MM-DD-YY', 'DD-MM-YYYY', 'DD-MM-YY'],
              name=u'date_format', parent=self, style=0, value='')
        self.date_format.SetSelection(0)
        # use either or:
        self.date_format.Bind(wx.EVT_COMBOBOX, self.TestComboBox)
        #self.date_format.Bind(wx.EVT_TEXT, self.TestComboBox)
                
    def TestComboBox(self, event):
        msg = str(self.date_format.GetValue())
        dlg = wx.MessageDialog(self, msg, "test")
        dlg.ShowModal()



#---------------------------------------------------------------------------

class BoaApp(wx.App):
    def OnInit(self):
        #wx.InitAllImageHandlers()
        #self.main = main_window.create(None)
        frame = testComboBox(None)
        frame.Show(True)
        return True
    

if __name__ == '__main__':
    application = BoaApp(0)
    application.MainLoop()
    
    
 	  	 

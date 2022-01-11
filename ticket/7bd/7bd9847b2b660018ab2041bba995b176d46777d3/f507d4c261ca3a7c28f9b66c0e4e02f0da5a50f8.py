import wx 
class MyForm(wx.Frame): 
    def __init__(self): 
        wx.Frame.__init__(self, None, wx.ID_ANY, "Font Bomb") 
        self.panel = wx.Panel(self, wx.ID_ANY) 
        sampleList = ['one', 'two', 'three'] 
        combo = wx.ComboBox(self.panel, wx.ID_ANY, 'Default', 
                            wx.DefaultPosition, 
                            (100,-1), sampleList, wx.CB_DROPDOWN) 
###        font = wx.Font(-1, wx.MODERN, wx.NORMAL, wx.BOLD)  # This works
        font = wx.Font(-1, -1, wx.NORMAL, wx.BOLD)  # This fails
        combo.SetFont(font) 
if __name__ == "__main__": 
    app = wx.App() 
    frame = MyForm().Show() 
    app.MainLoop() 

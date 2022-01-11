import wx

class TestFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1, title= "TestFrame")
        sizer= wx.BoxSizer(wx.VERTICAL)
        
        button= wx.Button(self, -1, "Print selection style info")
        self.Bind(wx.EVT_BUTTON, self.printSelectionStyleInfo, button)
        
        sizer.Add(button, flag= wx.ALL | wx.EXPAND, border= 0)
        
        self.text= wx.TextCtrl(self, -1, size= (400, 400),
            style= wx.TE_MULTILINE | wx.TE_RICH)
        self.text.SetDefaultStyle(
            wx.TextAttr(wx.Colour(0, 0, 0), wx.Colour(255, 255, 255),
            wx.Font(10, wx.SWISS, wx.NORMAL, wx.NORMAL, False)))
                
        self.text.AppendText("Lorem ipsum dolores sit amet!\n")
        
        sizer.Add(self.text, flag= wx.ALL | wx.EXPAND, border= 0)
        
        self.SetSizer(sizer)

        self.Fit()
        self.Show(True)
        
    def printSelectionStyleInfo(self, event):
        (start, end)= self.text.GetSelection()
        print start, ",", end
        for c in range(start, end):
            ch= self.text.GetRange(c, c+ 1)
            ta= wx.TextAttr()
            if self.text.GetStyle(c, ta):
                _font= ta.GetFont()
                _style= _font.GetStyle()
                _weight= _font.GetWeight()
                _underline= _font.GetUnderlined()
                
                print "char:", ch,
                print "pos:", c,
                print "style:", _style,
                print "weight:", _weight,
                print "underline:", _underline,
                print "fontsize:", _font.GetPointSize()
                
                
class TestApp(wx.App):
    def OnInit(self):
        frame= TestFrame()
        return True
        
        
if __name__== "__main__":
    app= TestApp(0)
    app.MainLoop()

 	  	 

import wx

app = wx.PySimpleApp()

frame = wx.Frame(None)

button = wx.Button(frame)
font = button.GetFont()

# Try to change the point size and set the font
font.SetPointSize(23)

## behavior correct if following line is uncommented:
#button.SetLabel("Hello!")
button.SetFont(font)

## behavior incorrect if following line is uncommented:
button.SetLabel("Hello!")

frame.Show()
app.MainLoop()


 	  	 

from wxPython.wx import *
from wxPython.html import *
import wxPython.lib.wxpTag

class MyChoice(wxChoice):
    def __init__(self, parent, size = wxDefaultSize, **kwargs):
        wxChoice.__init__(self, parent, -1,
                          choices = ['blaat', 'piet'] * 10,
                          size = size)

class MyApp(wxApp):
    def OnInit(self):
        frame = wxFrame(NULL, -1, "Problem!")
        self.html = wxHtmlWindow(frame, -1)
        self.html.SetPage("""

<html>
<head>
</head>
<body>
<h1>blaat</h1>

<wxp class="wxButton" width="50%">
<param name="label" value="It works!">
<param name="id" value="wxID_OK">
</wxp>

<wxp module="problem" class="MyChoice" heigth="32" width="100">
</wxp>

</body>
</html>

""")

        frame.Show(true)
        frame.SetAutoLayout(true)
        
        
        self.SetTopWindow(frame)
        return true

app = MyApp(0)
app.MainLoop()


 	  	 

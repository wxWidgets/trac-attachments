#!/usr/bin/env python2.5

import wx

class ToolBarMixin:

    def BuildToolBar(self):
        tb = self.ToolBar
        print "bitmap size:", getMagPlusBitmap().GetSize()
        tb.SetToolBitmapSize((24, 24))
        
        self.ZoomInTool = tb.AddRadioTool(wx.ID_ANY, bitmap=getMagPlusBitmap(), shortHelp = "Zoom In")
        self.Bind(wx.EVT_TOOL, lambda evt : self.SetMode(Mode="ZoomIn"), self.ZoomInTool)

        self.ZoomOutTool = tb.AddRadioTool(wx.ID_ANY, bitmap=getMagMinusBitmap(), shortHelp = "Zoom Out")
        self.Bind(wx.EVT_TOOL, lambda evt : self.SetMode(Mode="ZoomOut"), self.ZoomOutTool)

        self.MoveTool = tb.AddRadioTool(wx.ID_ANY, bitmap=getMoveButtonBitmap(), shortHelp = "Move")
        self.Bind(wx.EVT_TOOL, lambda evt : self.SetMode(Mode="Move"), self.MoveTool)

        tb.AddSeparator()

        self.ZoomButton = wx.Button(tb, label="Zoom To Fit")
        tb.AddControl(self.ZoomButton)
        self.ZoomButton.Bind(wx.EVT_BUTTON, self.ZoomToFit)

        tb.Realize()
        
        print "ToolBitmapSize", tb.GetToolBitmapSize()

        return tb

    def SetMode(self, Mode):
        print "In SetMode", Mode

    def ZoomToFit(self,Event):
        print "In ZoomToFit"


class TestPanel(wx.Panel, ToolBarMixin):

    def __init__(self, *args, **kwargs):
        wx.Panel.__init__(self, *args, **kwargs)

        self.ToolBar = wx.ToolBar(self)
        self.BuildToolBar()

        ## Create the vertical sizer for the toolbar and Panel
        box = wx.BoxSizer(wx.VERTICAL)
        box.Add(self.ToolBar, 0, wx.ALL | wx.ALIGN_LEFT | wx.GROW, 4)

        self.Canvas = wx.Panel(self)
        self.Canvas.SetBackgroundColour("Blue")

        box.Add(self.Canvas, 1, wx.EXPAND)

        self.SetSizerAndFit(box)

        # default to Mouse mode
        self.ToolBar.ToggleTool(self.ZoomInTool.GetId(), True)

        return None

class TestFrame(wx.Frame, ToolBarMixin):
    def __init__(self, *args, **kwargs):
        wx.Frame.__init__(self, *args, **kwargs)

        self.ToolBar = self.CreateToolBar()
        self.BuildToolBar()
        
        p = TestPanel(self)

       
class App(wx.App):
    def OnInit(self):
        frame = TestFrame(None)
        self.SetTopWindow(frame)
        frame.Show()
        return True

# The data for the icons. These functions were generated by img2py,
# which comes with the wxPython distribution, in the tools directory.
# It is a pretty handy way to imbed icons in your Python code.

#import cPickle, zlib
import cStringIO, zlib

def getMagPlusData():
    return zlib.decompress(
'x\xda\x01*\x01\xd5\xfe\x89PNG\r\n\x1a\n\x00\x00\x00\rIHDR\x00\x00\x00\x18\
\x00\x00\x00\x18\x08\x06\x00\x00\x00\xe0w=\xf8\x00\x00\x00\x04sBIT\x08\x08\
\x08\x08|\x08d\x88\x00\x00\x00\xe1IDATx\x9c\xb5U\xd1\x0e\xc4 \x08\xa3n\xff\
\xff\xc5\xdb\xb8\xa7\xee<\x04\x86gFb\xb2\x88\xb6\x14\x90\x01m\x937m\x8f\x1c\
\xd7yh\xe4k\xdb\x8e*\x01<\x05\x04\x07F\x1cU\x9d"\x19\x14\\\xe7\xa1\x1e\xf07"\
\x90H+$?\x04\x16\x9c\xd1z\x04\x00J$m\x06\xdc\xee\x03Hku\x13\xd8C\x16\x84+"O\
\x1b\xa2\x07\xca"\xb7\xc6sY\xbdD\x926\xf5.\xce\x06!\xd2)x\xcb^\'\x08S\xe4\
\xe5x&5\xb4[A\xb5h\xb4j=\x9a\xc8\xf8\xecm\xd4\\\x9e\xdf\xbb?\x10\xf0P\x06\
\x12\xed?=\xb6a\xd8=\xcd\xa2\xc8T\xd5U2t\x11\x95d\xa3"\x9aQ\x9e\x12\xb7M\x19\
I\x9f\xff\x1e\xd8\xa63#q\xff\x07U\x8b\xd2\xd9\xa7k\xe9\xa1U\x94,\xbf\xe4\x88\
\xe4\xf6\xaf\x12x$}\x8a\xc2Q\xf1\'\x89\xf2\x9b\xfbKE\xae\xd8\x07+\xd2\xa7c\
\xdf\x0e\xc3D\x00\x00\x00\x00IEND\xaeB`\x82\xe2ovy' )

def getMagPlusBitmap():
    return wx.BitmapFromImage(getMagPlusImage())

def getMagPlusImage():
    stream = cStringIO.StringIO(getMagPlusData())
    return wx.ImageFromStream(stream)

#----------------------------------------------------------------------
def getPointerData():
    return zlib.decompress(
"x\xda\xeb\x0c\xf0s\xe7\xe5\x92\xe2b``\xe0\xf5\xf4p\t\x02\xd2\x12 \xcc\xc1\
\x06$\x1f\x94\xdb\xfe\x00R,\xc5N\x9e!\x1c@P\xc3\x91\xd2\x01\xe4o\xf5tq\x0c\
\xa9\x98\xb3\xf5\xdaE\xa1V\x05\x0e\x96\x0bw\xbf\xfc\xdf\xbfc\xd1\xf4\xd9\x87\
\xa7\xa84Mw_n\xa3\xeb&\xbcS\xf4N\xa9\xdcn\x86\x03aZ\x1bWl{\xcet\x92m\xed\x8a\
[\xd1*\x9c\x82\x91\x93\x9eMuP\xd6\xbe4\xa3\xa1\xcd\xe8\x84\xc0\t%=\x85\xe6\
\x1d\x8d\x1aF\xac.\x132\x13\xc4^\x9ek\x14\xffx\xc6K\xa3\xd1\xcd-3\xa8\xa1M'\
\x85\xf3Ck\xcb\xb9\x07\xd7\x7f\x85\x7f=\xa7Ts\xe2^\xff\x83\xfb\xf1\x97\x15\
\x15\x94\xd2\xbc/5tl\t\xb3\x11\xcc\xe7\x12\xbe0;\xfa\xef7\x85X\x87\xfc{z:S'\
\x86-}\xb6\xe0\xbb\xc2\xfc\x03\x7f\xa7\\\xf3\xb5jM/fX\xf0/\xf7\xe3\xb5\xca7\
\x8f\xe66s\xf3\x99\xe7\xf8\x9e\xb4(\xfd\t\xf4\x00\x83\xa7\xab\x9f\xcb:\xa7\
\x84&\x00\xc7Jh8" )

def getPointerBitmap():
    return wx.BitmapFromImage(getPointerImage())

def getPointerImage():
    stream = cStringIO.StringIO(getPointerData())
    return wx.ImageFromStream(stream)

#----------------------------------------------------------------------
def getMagMinusData():
    return zlib.decompress(
'x\xda\xeb\x0c\xf0s\xe7\xe5\x92\xe2b``\xe0\xf5\xf4p\t\x02\xd2\x12 \xcc\xc1\
\x06$\x1f\x94\xdb\xfe\x00R,\xc5N\x9e!\x1c@P\xc3\x91\xd2\x01\xe4\xdf\xf6tq\
\x0c\xa9\x98\xb354\x9a\xaf\xc5\x80#e\xd5w\xfb\x8d\xa7\xea.\xa6j\x06\xec\xeaU\
Q[vE\xb2m\xba\x83\xf5\x0b_k\xe5\xe3\xc5\xf12?o\x15.\xf2b\xf0ol`V\xe63\xd6\
\x9f\xc8\xc35\xefw\x12\xff\x0fi\xc1\x96\x0em\x15{\x16\xb1\x98E_9\x18\xa6x\
\xdc\xe2\xdaa\xcb>\xe1\xda*\xe1\x1b\xde\x82\x15O\xfc\xa5\x9d\xdc\x83\x19\xb7\
\xabD\xee\xed\x98dv\xd6n\r\x9b\xe3\x12\x91=\xa9\xeb\x85[4\xa3<\x9d\xd3b\x1d\
\xb7f$]]\x96\xe1\xf2\xf8\xc6y\x8f5\xf6\xd2\xdb\x96\xe9\xdfT\\\xd5p\xbe-7\xa2\
ls\xac\x88\xa4\xf1n\xaf6=!\xd5\x9b\xab:\xca\xa6,?\x92\x1b\xdc\xe9r\xe0\xcb\
\xe2\xe6\x15\x13v\xfco^\xe5\xfa\xf2\xca\xcb[R[\xba&\xbd\xf5\xec\xf3\xd8U?\
\xfd\x80\xf2EM\xae\xf0\xa3\xf3Ut\xde\x17\xed\x0b}\xd2U\xcb0Ugv\x82\xa1Q\xc7S\
\xa07\x19<]\xfd\\\xd69%4\x01\x00+\xecq\xf9' )

def getMagMinusBitmap():
    return wx.BitmapFromImage(getMagMinusImage())

def getMagMinusImage():
    stream = cStringIO.StringIO(getMagMinusData())
    return wx.ImageFromStream(stream)

#----------------------------------------------------------------------
def getMoveButtonData():
    return zlib.decompress(
'x\xda\x01,\x01\xd3\xfe\x89PNG\r\n\x1a\n\x00\x00\x00\rIHDR\x00\x00\x00\x18\
\x00\x00\x00\x18\x08\x06\x00\x00\x00\xe0w=\xf8\x00\x00\x00\x04sBIT\x08\x08\
\x08\x08|\x08d\x88\x00\x00\x00\xe3IDATx\x9c\xb5\x96\xd1\x16\x84 \x08D\x19\
\xf5\xff\xbf\xb8\x9a}Y[\xc2P\xe8\xb4<\xaa\xcc\x15\x1c-\xa0T\x89\xc6\xb1o\x14\
\x11)\xb5!\x9aS2\xe2\x00\x04\xc0\tz\r\xd0\xc5{d K\x80\x15\xcfB\xa6\x00O<\x03\
q\x01+\xf1(\xa4\xb9\xe4\xda@\xf2\x92\xd8\x81fx\xea\xaa\x01p\xec\x1b{\x82N\
\xb4\xbb\xb4\xa2\x9e\x85\x8b]\x94\xb5\xa1\x8e\xbb\xdc\x13\xa0{\x9e\xb9H+\x08\
P\xeap\xa0\xb6\xc7:92\xdf\xd7\x94\xda\x00\x92!\xb7<\t\x92\xf1\xa7\xe2i\xb4n\
\xc7\x7f\xb5\xa8\x89\xfc<\xaf\x17x6\x8c\xccwq\x11\xe5\xa2/\xe4\xbe\xceDh\xf1\
\x0b@C\x9e\xd8\xd4\xcb\xc5\xec\x83c\xdb\xf2\xcaS\xa1\xc5=\xfb\xdaq\x92\xf4 \
\xaeM\xa3g\xb2j\xe9\xf4\x1e\xac \x91\r\xb8-2\x90\xa1]Q3\x84n\xb2\xad$\xe3\
\xb4e\x05\x06\x92\xfem\xf9\x00\x8d\xa7\xbb\x936\xe9\xf2\xae\x00\x00\x00\x00I\
END\xaeB`\x82\xed\x9c\x836' )

def getMoveButtonBitmap():
    return wx.BitmapFromImage(getMoveButtonImage())

def getMoveButtonImage():
    stream = cStringIO.StringIO(getMoveButtonData())
    return wx.ImageFromStream(stream)

     
if __name__ == "__main__":
    app = App(0)
    app.MainLoop()















 	  	 

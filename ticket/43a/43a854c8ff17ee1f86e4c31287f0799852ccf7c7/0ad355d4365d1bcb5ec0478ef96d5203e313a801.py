import wx
import wx.lib.embeddedimage

WXPdemo = wx.lib.embeddedimage.PyEmbeddedImage(
    "iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABHNCSVQICAgIfAhkiAAAAWlJ"
    "REFUWIW1V1sSwjAIBMebeBU9db2KZ8EPmxbCI4TUnXGskWaXDQktwhjErjERP4XRhER08iPi"
    "5SKiyQR5JyI7xxB3j7wn5GI6V2hFxM0gJtjYANFBiIjQu7L/1lYlwR0QxLDZhE0II1+CtwRC"
    "RI8riBva7DL7CC9VAwDbbxwKtdDXwBi7K+1zCP99T1vDFedd8FBwYd6BCAUXuACEF7QsbET/"
    "FaHs+gDQw4vOLNHkMojAnTw8nlNipIiwmR0DCXJbjCXkFCAL23BnpQgRWt1EMbyujCK9AZzZ"
    "f+b3sX0oSqJQ6EorFeT4NiL6Wtj0+LXnQAzThYoAAsN6ehqR3sHExmcEqGeFApQLcTvm5Kt9"
    "wkHGgb+RZwSkyc1dwOcpCtCoNKSz6FRCUQ3o7Nn+5Y+Lg+y5CIXlcyAk99ziiQS32+svz/UY"
    "vClJoLpIC8gi+VwwfDecEiEtT/WZTJDf94uk1Ru8vbz0cvoF7S2DnpeVL9UAAAAASUVORK5C"
    "YII=")

class DemoTaskBarIcon(wx.TaskBarIcon):
    TBMENU_RESTORE = wx.NewId()
    TBMENU_CLOSE   = wx.NewId()
    TBMENU_CHANGE  = wx.NewId()
    TBMENU_REMOVE  = wx.NewId()

    def __init__(self, frame):
        wx.TaskBarIcon.__init__(self)
        self.frame = frame

        # Set the image
        icon = self.MakeIcon(WXPdemo.GetImage())
        self.SetIcon(icon, "wxPython Demo")
        self.imgidx = 1

        # bind some events
        self.Bind(wx.EVT_TASKBAR_CLICK, self.Menu)
        self.Bind(wx.EVT_TASKBAR_LEFT_UP, self.Menu)
        self.Bind(wx.EVT_MENU, self.OnTaskBarClose, id=self.TBMENU_CLOSE)

    def Menu(self, unused_event):
        self.PopupMenu(self.CreatePopupMenu())

    def CreatePopupMenu(self):
        menu = wx.Menu()
        menu.Append(self.TBMENU_CLOSE,   "Close application")
        return menu


    def MakeIcon(self, img):
        """
        The various platforms have different requirements for the
        icon size...
        """
        if "wxMSW" in wx.PlatformInfo:
            img = img.Scale(16, 16)
        elif "wxGTK" in wx.PlatformInfo:
            img = img.Scale(22, 22)
        # wxMac can be any size upto 128x128, so leave the source img alone....
        icon = wx.IconFromBitmap(img.ConvertToBitmap() )
        return icon


    def OnTaskBarClose(self, evt):
        wx.CallAfter(self.frame.Close)



class MainFrame(wx.Frame):
    def __init__(self, parent):
        wx.Frame.__init__(self, parent, title="Hello World")
        self.tbicon = DemoTaskBarIcon(self)
        self.Bind(wx.EVT_CLOSE, self.OnCloseWindow)

        self.button = wx.Button(self, wx.ID_ANY, "Show balloon")
        self.button.Bind(wx.EVT_BUTTON,
            lambda evt: self.tbicon.ShowBalloon("Title", "Text", 3000))

        self.sizer = wx.BoxSizer(wx.VERTICAL)
        self.sizer.Add(self.button)
        self.SetSizer(self.sizer)
        self.Layout()

    def OnCloseWindow(self, evt):
        self.tbicon.Destroy()
        evt.Skip()


app = wx.App(redirect=False)
frame = MainFrame(None)
frame.Show(True)
app.MainLoop()

import wx

class myFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1, "Were am I horizontally?")

class App(wx.App):
    def OnInit(self):
        frame = myFrame()
        frame.Show()
        frame.CentreOnScreen(wx.BOTH)
        return True

def main():
    app = App()
    app.MainLoop()

if __name__ == "__main__":
    main()

import wx
import wx.html2

class WebViewDialog(wx.Dialog):
    def __init__(self, *args, **kw):
        wx.Dialog.__init__(self, *args, **kw)
        self.browser = wx.html2.WebView.New(self)
        sizer = wx.BoxSizer()
        sizer.Add(self.browser, 1, wx.EXPAND|wx.ALL, 10)
        self.SetSizer(sizer)
        self.SetSize((700,700))

    def LoadURL(self, url):
        self.browser.LoadURL(url)
        
class TestFrame(wx.Frame):
    def __init__(self, *args, **kw):
        wx.Frame.__init__(self, *args, **kw)
        panel = wx.Panel(self)
        btn1 = wx.Button(panel, -1, "ShowModal")
        btn2 = wx.Button(panel, -1, "Show non-modal")

        btn1.Bind(wx.EVT_BUTTON, self.onShowModal)
        btn2.Bind(wx.EVT_BUTTON, self.onShowNonModal)

        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(btn1, 0, wx.ALL, 5)
        sizer.Add(btn2, 0, wx.ALL, 5)
        panel.SetSizer(sizer)

    def onShowModal(self, evt):
        dlg = WebViewDialog(self)
        dlg.LoadURL('http://www.google.com/')
        dlg.ShowModal()
        dlg.Destroy()
        
    def onShowNonModal(self, evt):
        dlg = WebViewDialog(self)
        dlg.LoadURL('http://www.google.com/')
        dlg.Show()     

app = wx.App()
frm = TestFrame(None, title="Test WebView Dialogs")
frm.Show()
app.MainLoop()

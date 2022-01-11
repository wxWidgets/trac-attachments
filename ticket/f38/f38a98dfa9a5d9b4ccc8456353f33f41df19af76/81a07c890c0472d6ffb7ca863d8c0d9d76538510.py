import sys, wx, os
import wx.html

class MainFrame(wx.Frame):

    def __init__(self, *args, **kwargs):
        wx.Frame.__init__(self, *args, **kwargs)

        sizer = wx.BoxSizer(wx.VERTICAL)

        panel = wx.Panel(self, -1, style=wx.TAB_TRAVERSAL)

        btn1 = wx.Button(panel, -1, "Top Button 1")
        btn2 = wx.Button(panel, -1, "Top Button 2")
        desc_html = InfoHtmlWindow(panel, size=(200, 85), style=wx.SUNKEN_BORDER)
        btn3 = wx.Button(panel, -1, "Bottom Button 3")
        btn4 = wx.Button(panel, -1, "Bottom Button 4")
        self.Bind(wx.EVT_BUTTON, self.OnClick, btn1)
        self.Bind(wx.EVT_BUTTON, self.OnClick, btn2)
        self.Bind(wx.EVT_BUTTON, self.OnClick, btn3)
        self.Bind(wx.EVT_BUTTON, self.OnClick, btn4)


        sizer.Add(btn1, 0, wx.ALL | wx.ALIGN_LEFT, 5)
        sizer.Add(btn2, 0, wx.ALL | wx.ALIGN_LEFT, 5)
        sizer.Add(desc_html, 0, wx.ALL | wx.ALIGN_LEFT, 5)
        sizer.Add(btn3, 0, wx.ALL | wx.ALIGN_LEFT, 5)
        sizer.Add(btn4, 0, wx.ALL | wx.ALIGN_LEFT, 5)

        panel.SetSizer(sizer)
        sizer.Fit(self)

        html = "<html><body>\n"
        html = html + "<center><h3>Mouseless Test</h3></center>\n"
        html = html + '<br><center><a href="http://yahoo.com">Yahoo!</a></center>\n'
        html = html + '<br><center><a href="http://google.com">Google</a></center>\n'
        html = html + "</body></html>\n"

        desc_html.SetPage(html)

        btn1.SetFocus()


    def OnClick(self, event):
        print "Button Pressed."


class InfoHtmlWindow(wx.html.HtmlWindow):

    def __init__(self, parent, *args, **kwargs):
        wx.html.HtmlWindow.__init__(self, parent, *args, **kwargs)

    def OnLinkClicked(self, link):
        print "This link clicked: " + link.GetHref()
        #wx.LaunchDefaultBrowser(link.GetHref())


def main(argv=None):
    app = wx.App(0)
    frame = MainFrame(None, -1, 'Mouseless Test')
    frame.Center(wx.BOTH)
    frame.Show()
    app.MainLoop()


if __name__ == '__main__':

    main()


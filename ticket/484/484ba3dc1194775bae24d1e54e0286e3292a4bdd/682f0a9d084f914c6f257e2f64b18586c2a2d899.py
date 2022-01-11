import wx
import wx.html

class TestApp(wx.App):
  def OnInit(self):
    wx.InitAllImageHandlers()
    f = wx.Frame(None, -1, "Quick Test",size=(400,400))
    # put 2 html windows
    self.html1 = wx.html.HtmlWindow(f, -1)
    self.html2 = wx.html.HtmlWindow(f, -1)
    # quick test doc
    img_doc = """\
    <html>
    An Image: <img src=\"​http://www.machine501.com/bell.png\" />
    </html>
    """
    no_img_doc = """\
    <html>
    I have no image
    </html>
    """
    doc = no_img_doc # uncomment me to set a doc with no image
    #doc = img_doc # uncomment me to set a doc with image
    if False:
      # this one sets the images on this thread, main thread, same as 
      self.html1.SetPage(doc)
      print "Set page for one, setting two..."
      self.html2.SetPage(doc)
      print "Done setting page two"
    else:
      # this one sets them on a callafter, same thread tho ...
      print "Setting page for html 1 ..."
      wx.CallAfter(self.html1.SetPage, doc)
      print "Set page for one, setting two..."
      wx.CallAfter(self.html2.SetPage, doc)
      print "Done setting page two"
    sizer = wx.BoxSizer(wx.HORIZONTAL)
    sizer.Add(self.html1, 1, wx.EXPAND|wx.ALL,2)
    sizer.Add(self.html2, 1, wx.EXPAND|wx.ALL,2)
    f.SetSizer(sizer)
    f.Show()
    self.frame = f # for later ref in case
    return True

if __name__ == '__main__':
  t = TestApp(redirect=None)
  t.MainLoop()

import wx
import wx.html
import os,sys
import urlparse
import time
import mimetools
import urllib2
from httplib import HTTPMessage
try:
    from cStringIO import StringIO
except ImportError:
    from StringIO import StringIO

def openAURL(url,proxy=None):
    """ Open a URL with an optional proxy. """
    import socket
    socket.setdefaulttimeout(60)

    if proxy is None:
        proxy    = urllib2.ProxyHandler({})
    else:
        proxy    = urllib2.ProxyHandler({'http': 'http://' + proxy})
    opener   = urllib2.build_opener(proxy, urllib2.HTTPHandler)
    return opener.open(url)

class fshHTTP( wx.FileSystemHandler ):
    """
        Replacement for the C++ version.
        This fixes the problem with malformed URLs.
        Please note that it ONLY does the HTTP protocol.
        Similar fixes should be done for other FSHs!
    """

    def __init__( self ):
        wx.FileSystemHandler.__init__( self )

    def CanOpen( self, u ):
        return ((self.GetProtocol(u) == 'http') or (self.GetProtocol(u) == 'HTTP'))

    def OpenFile( self, fs, u ):
        # fix the bad url, it's indicated by a double slash in the path.
        bad=urlparse.urlsplit(u)
        nu=bad[2].rpartition('//')[2]
        fu = urlparse.urlunsplit((bad[0],bad[1],nu,bad[3],bad[4]))
        print "Original URL :`"+u+"'"
        print "Fixed URL ...:`"+fu+"'"
        # Open the fixed url
        h=openAURL(fu)
        # Get the mime header
        mmsgs = str(h.info())+"\n\n"
        # Parse the mime headers
        mio = StringIO(mmsgs)
        mmdcd = HTTPMessage(mio)
        amh=mmdcd.readheaders()
        # Get the mime type
        mtype = mmdcd.gettype()
        data = h.read()
        sio = StringIO(data)
        wxis = wx.InputStream(sio)
        wxfs = wx.FSFile(wxis, u, (mtype).lower(), self.GetAnchor(u), wx.DateTime())
        return wxfs

_fshHTTP = fshHTTP()


class exHtmlWindow(wx.html.HtmlWindow):
    def __init__(self, parent, id, frame):
        wx.html.HtmlWindow.__init__(self,parent,id)
        # Remove all the default handlers, we only do HTTP
        wx.FileSystem.CleanUpHandlers()
        # Add our own fixed handler
        wx.FileSystem.AddHandler( _fshHTTP )
        # Other handlers can be added here.

    def OnOpeningURL(self, type, url):
        kind = 'PAGE'
        if type == wx.html.HTML_URL_IMAGE:
            kind = 'IMAGE'
        if type == wx.html.HTML_URL_OTHER:
            kind = 'OTHER'
        print kind+" '"+url+"' "
        return wx.html.HTML_OPEN

    def OnLinkClicked(self, link):
        self.LoadPage(link.GetHref())

    def LoadPage(self, url):
        print "\nLoadPage: `"+url+"'"

        super(exHtmlWindow, self).LoadPage(url)

class exFrame (wx.Frame):
    def __init__(self, parent, ID, title):
        wx.Frame.__init__(self,parent,ID,title,wx.DefaultPosition,wx.Size(600,750))
        self.panel = exHtmlPanel(self, -1, self)
        self.CreateStatusBar()
        self.SetStatusText("Default status bar")
        mnu_file = wx.Menu()
        mnu_file.Append(101, "E&xit", "Exit the browser")
        menuBar = wx.MenuBar()
        menuBar.Append(mnu_file, "F&ile")
        self.SetMenuBar(menuBar)
        wx.EVT_MENU(self, 101, self.Exit)

    def Exit(self, event):
        self.Close(True)

class exHtmlPanel(wx.Panel):
    def __init__(self, parent, id, frame):
        wx.Panel.__init__(self, parent, -1)
        self.frame = frame
        self.cwd = os.path.split(sys.argv[0])[0]
        if not self.cwd:
            self.cwd = os.getcwd
        self.html = exHtmlWindow(self, -1, self.frame)
        self.html.SetStandardFonts()
        self.html.SetRelatedFrame(self.frame, "%s")
        self.html.SetRelatedStatusBar(0)

        self.box = wx.BoxSizer(wx.VERTICAL)
        self.box.Add(self.html, 1, wx.GROW)
        subbox = wx.BoxSizer(wx.HORIZONTAL)
        btn = wx.Button(self, 1202, "Clear")
        wx.EVT_BUTTON(self, 1202, self.OnClear)
        subbox.Add(btn, 1, wx.GROW | wx.ALL, 2)
        btn = wx.Button(self, 1203, "Load Page")
        wx.EVT_BUTTON(self, 1203, self.OnLoadPage)
        subbox.Add(btn, 1, wx.GROW | wx.ALL, 2)
        btn = wx.Button(self, 1204, "Back")
        wx.EVT_BUTTON(self, 1204, self.OnBack)
        subbox.Add(btn, 1, wx.GROW | wx.ALL, 2)
        btn = wx.Button(self, 1205, "Forward")
        wx.EVT_BUTTON(self, 1205, self.OnForward)
        subbox.Add(btn, 1, wx.GROW | wx.ALL, 2)
        self.box.Add(subbox, 0, wx.GROW)
        self.SetSizer(self.box)
        self.SetAutoLayout(True)

    def OnLoadPage(self, event):
        dlg = wx.TextEntryDialog(self, 'Location:')
        if dlg.ShowModal() == wx.ID_OK:
            loc = dlg.GetValue()
        dlg.Destroy()
        self.html.LoadPage(loc)

    def OnClear(self, event):
        self.html.SetPage("")

    def OnBack(self, event):
        if not self.html.HistoryBack():
            wx.MessageBox("No more items in history!")

    def OnForward(self, event):
        if not self.html.HistoryForward():
            wx.MessageBox("No more items in history!")

    # This URL will show the problem in stdout.
    # If click the "Start Page" link it shows the problem even better.
    def OnInit(self):
        self.html.LoadPage('http://trac.wxwidgets.org/')

class exApp(wx.App):
    def __init__(self, flag):
        wx.App.__init__(self, flag)
        wx.Log_SetActiveTarget(wx.LogStderr())

    def OnInit(self):
        frame = exFrame(None, -1, "Example Browser")
        frame.Show(True)
        self.SetTopWindow(frame)
        frame.panel.OnInit()
        return True

app = exApp(0)
app.MainLoop()

"""
Example run, with commentary.

$ python fixhttp.py

LoadPage: `http://trac.wxwidgets.org/'
PAGE 'http://trac.wxwidgets.org/'
Original URL :`http://trac.wxwidgets.org/'
Fixed URL ...:`http://trac.wxwidgets.org/'
IMAGE 'http://trac.wxwidgets.org/chrome/site/logo9.jpg' <-- THIS URL IS CORRECT!
Original URL :`http://trac.wxwidgets.org//chrome/site/logo9.jpg' <-- It got changed?!
Fixed URL ...:`http://trac.wxwidgets.org/chrome/site/logo9.jpg'
IMAGE 'http://trac.wxwidgets.org/chrome/common/trac_logo_mini.png'
Original URL :`http://trac.wxwidgets.org//chrome/common/trac_logo_mini.png' <-- Here too!
Fixed URL ...:`http://trac.wxwidgets.org/chrome/common/trac_logo_mini.png'

LoadPage: `/wiki/WikiStart'
PAGE 'http://trac.wxwidgets.org/wiki/WikiStart'
Original URL :`http://trac.wxwidgets.org//wiki/WikiStart' <-- Here too!
Fixed URL ...:`http://trac.wxwidgets.org/wiki/WikiStart'
IMAGE 'http://trac.wxwidgets.org/chrome/site/logo9.jpg'
Original URL :`http://trac.wxwidgets.org//wiki//chrome/site/logo9.jpg' <-- Here too!
Fixed URL ...:`http://trac.wxwidgets.org/chrome/site/logo9.jpg'
IMAGE 'http://trac.wxwidgets.org/chrome/common/trac_logo_mini.png'
Original URL :`http://trac.wxwidgets.org//wiki//chrome/common/trac_logo_mini.png' <-- Here too!
Fixed URL ...:`http://trac.wxwidgets.org/chrome/common/trac_logo_mini.png'

URLs become even MORE scrambled with cgi's! But the fix resolves the problem.
This bug needs to be forwarded to WxWidgets dev team so that can fix the mistake.

"""

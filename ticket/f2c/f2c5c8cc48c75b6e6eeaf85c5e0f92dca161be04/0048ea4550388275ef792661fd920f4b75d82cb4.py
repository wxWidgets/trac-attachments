'''sizeevents.py
'''
if __name__=='__main__':

    import wx
    import sys


    class mFrame(wx.Frame):


        def __init__(self):

            if sys.platform.startswith('freebsd'):
                self.__size = None

            wx.Frame.__init__(
                self,
                None,
                wx.ID_ANY,
                'Hello World',
                wx.DefaultPosition,
                wx.DefaultSize,
                wx.DEFAULT_FRAME_STYLE
                )

            self.Bind(wx.EVT_SIZE, self.OnSize)


        def OnSize(self, event):
        
            print 'OnSize called'
            if sys.platform.startswith('freebsd'):
                size = event.GetSize()
                if self.__size == size:
                    event.Skip()
                    return
                else:
                    print 'OnSize', self.__size, size, id(self)
                    self.__size = size
            else:
                print 'OnSize', id(self), event.GetSize()

            #Production code at this point may waste resources at best
            #(eg Getting extra records from database).
            #Done twice under FreeBSD without "startswith" hack.
            #Done once under both W2000 and Wine-1.1 under FreeBSD7.
            #Do not recall as problem on Linux (RedHat) several years ago.

            event.Skip()
        

    class mApp(wx.App):
        

        def OnInit(self):
            
            mf = mFrame()
            self.SetTopWindow(mf)
            mf.Show()
            return True


    app = mApp()
    app.MainLoop()

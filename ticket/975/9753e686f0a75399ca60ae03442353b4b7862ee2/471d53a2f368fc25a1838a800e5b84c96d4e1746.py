import  time
import  wx

#-------------------------------------------------------------------

class MyFrame(wx.Frame):

    def __init__(self, parent, id):
        wx.Frame.__init__(self, parent, id, 'Playing with menus', size=(400, 200))
        self.CenterOnScreen()

        # Prepare the menu bar
        menuBar = wx.MenuBar()

        menu5 = wx.Menu()
        # Show how to put an icon in the menu
        item = wx.MenuItem(menu5, 500, "&Smile!\tCtrl+S")
        item.SetBackgroundColour(wx.WHITE)    # !!!!!!!!!!!!!!
#         item.SetTextColour(wx.WHITE)   # Alternative, same problem
        menu5.AppendItem(item)

        menuBar.Append(menu5, "&Fun")

        self.SetMenuBar(menuBar)



#-------------------------------------------------------------------

class App(wx.App):   
    def OnInit(self):
        frame = MyFrame(None, -1)
        frame.Show()
        self.SetTopWindow(frame)
        
        return True


if __name__ == '__main__':
    app = App(0)
    app.MainLoop()

 	  	 

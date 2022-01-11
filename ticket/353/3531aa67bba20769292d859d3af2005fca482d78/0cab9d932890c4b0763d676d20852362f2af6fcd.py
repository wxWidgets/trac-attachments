import wx
import os
import time,socket #for session ID
import win32api as win32api



class panel_screenshot_monitor(wx.Panel):
    defaultscreen=os.path.abspath(r".\black_pixel_bw.png")
    
    def __init__(self,parent,_given_size=None,name="example"):
        wx.Panel.__init__(self,parent,name=name)
        self.col1_width=70
        self.col2_width=80
        self.col3_width=110
        self.col4_width=160
        self.col5_width=120
        self.given_size=_given_size
        self.screen_index=0
        self.sizer_L2=wx.BoxSizer( wx.VERTICAL);
        self.Sizer=self.sizer_L2;
        self.sizer_L3_a=wx.BoxSizer(wx.HORIZONTAL);
        self.sizer_L2.Add(self.sizer_L3_a);
       
        self.refresh_timer=wx.Timer(self)
        self.Bind(wx.EVT_TIMER,self.on_refresh,self.refresh_timer)

        self.init_methode_txt=["working: init with image from file","working: init with image from file + paste screenshot","gray instead: init with empty bitmap and paste screenshot","no color at all: init with empty bitmap"];
        self.init_methode_select=wx.ComboBox(self,name="updaterate", style=wx.CB_DROPDOWN,choices=self.init_methode_txt)
        self.init_methode_select.Select(0)
        #self.init_methode_select.Bind(wx.EVT_COMBOBOX, self.callback_updaterate)
        self.sizer_L3_a.Add(self.init_methode_select);
        
        self.footerheight=5+(self.init_methode_select.GetSize()[1])
        self.screenshotfile=wx.Image(self.defaultscreen,wx.BITMAP_TYPE_ANY)
        self.display_screenshot=wx.StaticBitmap(self,bitmap=wx.BitmapFromImage(self.screenshotfile))
        self.sizer_L2.Add(self.display_screenshot,flag=wx.EXPAND);
        
        
        self.sizer_L3_a.Layout()
        self.sizer_L2.Layout()
        self.callback_updaterate(None)
        
    def callback_updaterate(self,event):
        self.refresh=500;
        if self.refresh is not None:
            self.refresh_timer.Start(self.refresh)
        else:
            self.refresh_timer.Stop()
            
    def on_refresh(self,event):
        self.callback_update(None)
     
    def callback_update(self,event):
        self.sizemain=self.GetSize();
        self.display_screenshot.SetSize(self.sizemain)
        screengeo=wx.Display(self.screen_index).GetGeometry()
        if self.init_methode_select.GetSelection()==0:
            #required reload to remove the bug
            self.screenshotfile=wx.Image(self.defaultscreen,wx.BITMAP_TYPE_ANY)
            #if you remove the line above it works until you try a different init and switch back.
            self.screenshotfile.Rescale(self.sizemain[0],self.sizemain[1]-self.footerheight)
            self.screen_buffer=wx.BitmapFromImage(self.screenshotfile)
            self.screen_size=(screengeo[2],screengeo[3]);
        if self.init_methode_select.GetSelection()==1:
            #required reload to remove the bug
            self.screenshotfile=wx.Image(self.defaultscreen,wx.BITMAP_TYPE_ANY)
            #if you remove the line above it works until you try a different init and switch back.
            self.screenshotfile.Rescale(self.sizemain[0],self.sizemain[1]-self.footerheight)
            self.screen_buffer=wx.BitmapFromImage(self.screenshotfile)
            self.screen_size=(screengeo[2],screengeo[3]);
            mem=wx.MemoryDCFromDC(wx.ScreenDC())
            mem.SelectObject(self.screen_buffer)
            mem.Blit(0,0,screengeo[2],screengeo[3],wx.ScreenDC(),screengeo[0],screengeo[1])
            mem.SelectObject(wx.NullBitmap)
            del mem
        if self.init_methode_select.GetSelection()==2:
            self.screen_buffer=wx.EmptyBitmapRGBA(screengeo[2],screengeo[3])
            mem=wx.MemoryDCFromDC(wx.ScreenDC())
            mem.SelectObject(self.screen_buffer)
            mem.Blit(0,0,screengeo[2],screengeo[3],wx.ScreenDC(),screengeo[0],screengeo[1])
            mem.SelectObject(wx.NullBitmap)
            del mem            
        if self.init_methode_select.GetSelection()==3:
            self.screen_buffer=wx.EmptyBitmapRGBA(screengeo[2],screengeo[3])
        rel_x=win32api.GetCursorPos()[0]-screengeo[0]+1
        rel_y=win32api.GetCursorPos()[1]-screengeo[1]+1
        mouse_overlay_client=wx.MemoryDC(self.screen_buffer)
        thick_x=20
        thick_y=20
        exp_x=50
        exp_y=50
        mouse_overlay_client.SetPen(wx.Pen("RED",thick_y))
        print mouse_overlay_client.GetPen().IsOk()
        print mouse_overlay_client.IsOk()
        print "wx.Pen.Colour before drawing the cursor (should be red): " + mouse_overlay_client.GetPen().GetColour().__repr__()
        mouse_overlay_client.DrawLine(rel_x-exp_x,rel_y,rel_x+exp_x,rel_y)
        print "wx.Pen.Colour after drawing the cursor (should be red): " + mouse_overlay_client.GetPen().GetColour().__repr__()
        mouse_overlay_client.SetPen(wx.Pen("red",thick_x))
        mouse_overlay_client.DrawLine(rel_x,rel_y-exp_y,rel_x,rel_y+exp_y)
        self.screenshotfile=self.screen_buffer.ConvertToImage()
        self.display_screenshot.SetBitmap(wx.BitmapFromImage(self.screenshotfile))
        pass

            
            
            
    def __del__(self):
        del self.screen_buffer


class gui_main(wx.Frame):
    def __init__(self,parent):
        screengeo=wx.Display(0).GetGeometry()
        wx.Frame.__init__(self, parent, wx.ID_ANY, 'Bug Demo', size=(screengeo[2], screengeo[3]),pos=(1,1))
        self.Bind(wx.EVT_CLOSE, self.OnCloseWindow);
        self.sizer_L1_a=wx.BoxSizer( wx.VERTICAL)
        self.SetSizer(self.sizer_L1_a)
        self.panel_screenshot=panel_screenshot_monitor(self);
        self.sizer_L1_a.Add(self.panel_screenshot,1,flag=wx.EXPAND);
        self.sizer_L1_a.Layout()

      
        
    def OnCloseWindow(self, event):
        self.Destroy()


class gui_main_app(wx.App):
    def OnInit(self):
        self.main = gui_main(None)
        self.main.Show()
        self.SetTopWindow(self.main)
        return True
    
    def __del__(self):
        wx.App.__del__(self);

def run_gui():
    application = gui_main_app(redirect=False)
    application.MainLoop()

if __name__=='__main__':
    run_gui()

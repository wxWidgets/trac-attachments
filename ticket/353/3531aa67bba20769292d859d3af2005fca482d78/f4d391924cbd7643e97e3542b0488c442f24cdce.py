import wx
import os
import time,socket #for session ID
import win32api as win32api



class panel_screenshot_monitor(wx.Panel):
    
    def __init__(self,parent,_given_size=None,name="example",_print_to_prompt=False):
        wx.Panel.__init__(self,parent,name=name)
        self.col1_width=70
        self.col2_width=80
        self.col3_width=110
        self.col4_width=160
        self.col5_width=120
        self.given_size=_given_size
        self.print_to_prompt=_print_to_prompt
        self.screenshot_counter=0;
        self.screen_index=0
        self.screen_buffer=None;
        self.sizer_L2=wx.BoxSizer( wx.VERTICAL);
        self.Sizer=self.sizer_L2;
        self.Heading=wx.StaticText(self,label=self.Name);
        self.sizer_L2.Add(self.Heading);
        self.defaultscreen=0;
        self.sizer_L3_a=wx.BoxSizer(wx.HORIZONTAL);
        self.sizer_L2.Add(self.sizer_L3_a);
        self.button_update=wx.Button(self,label="update",size=(self.col1_width,-1))
        self.button_update.Bind(wx.EVT_BUTTON,self.callback_update)
        self.sizer_L3_a.Add(self.button_update);
        
        
        rangelist=[];
        for i in range(wx.Display.GetCount()):
            rangelist.append("Screen %d"%i);
        self.screen_select=wx.ComboBox(self,name="screenNr", style=wx.CB_DROPDOWN,choices=rangelist, size=(self.col3_width,-1))
        self.screen_select.Select(self.screen_index)
        self.screen_select.Bind(wx.EVT_COMBOBOX, self.callback_screen_select)
        self.sizer_L3_a.Add(self.screen_select);

        self.updateinterval_text=["no auto update","0.1sec.","1 sec.","10 sec."];
        self.updateinterval_num=[None,100,1000,10000];
        self.updaterate_select=wx.ComboBox(self,name="updaterate", style=wx.CB_DROPDOWN,choices=self.updateinterval_text, size=(self.col4_width,-1))
        self.updaterate_select.Select(2)
        self.updaterate_select.Bind(wx.EVT_COMBOBOX, self.callback_updaterate)
        self.sizer_L3_a.Add(self.updaterate_select);
        self.refresh_timer=wx.Timer(self)
        self.Bind(wx.EVT_TIMER,self.on_refresh,self.refresh_timer)


        
        self.mouse_on=wx.Button(self,label="Mouse Pos = on", size=(self.col5_width,-1))
        self.is_with_mouse=True
        self.mouse_on.Bind(wx.EVT_BUTTON, self.callback_mouse_on_off)
        self.sizer_L3_a.Add(self.mouse_on);
        self.mouse_overlay=None;

        self.footerheight=self.updaterate_select.GetSize()[1]+self.Heading.GetSize()[1]+5
        screengeo=wx.Display(0).GetGeometry()
        self.screenshotfile=wx.EmptyBitmapRGBA(screengeo[2],screengeo[3])
        self.sizemain=self.GetSize();
        img_size=(self.sizemain[0],self.sizemain[1]-self.footerheight)
        self.display_screenshot=wx.StaticBitmap(self,bitmap=(self.screenshotfile),size=img_size)
        self.sizer_L2.Add(self.display_screenshot,flag=wx.EXPAND);
        
        
        self.sizer_L3_a.Layout()
        self.sizer_L2.Layout()
        self.time_log=None
        self.callback_updaterate(None)
        
        
    def callback_mouse_on_off(self,event):
        if self.is_with_mouse:
            self.is_with_mouse=False
            self.mouse_on.SetLabel("Mouse Pos = off")
        else:
            self.is_with_mouse=True
            self.mouse_on.SetLabel("Mouse Pos = on")
            
    def callback_updaterate(self,event):
        self.refresh=self.updateinterval_num[self.updaterate_select.Selection]
        if self.refresh is not None:
            self.refresh_timer.Start(self.refresh)
        else:
            self.refresh_timer.Stop()
            
    def on_refresh(self,event):
        if self.print_to_prompt:
            print "time is up"
        self.callback_update(None)
        #
    def callback_screen_select(self,event):
        self.screen_index=self.screen_select.Selection;
        screengeo=wx.Display(self.screen_index).GetGeometry()
        self.screen_buffer=wx.EmptyBitmapRGBA(screengeo[2],screengeo[3])
        self.screen_select.Clear()
        rangelist=[];
        for i in range(wx.Display.GetCount()):
            rangelist.append("Screen %d"%i);
        self.screen_select.SetItems(rangelist)
        try:
            self.screen_select.Select(self.screen_index)
        except:
            pass
    
    def callback_update(self,event):
        self.sizemain=self.GetSize();
        img_size=(self.sizemain[0],self.sizemain[1]-self.footerheight)
        if self.display_screenshot.GetSize()!=img_size:
            self.display_screenshot.SetSize(img_size)
        screengeo=wx.Display(self.screen_index).GetGeometry()
        #print screengeo;
        if self.screen_buffer is None:
            self.screen_buffer=wx.EmptyBitmapRGBA(screengeo[2],screengeo[3])
        self.screen_size=(screengeo[2],screengeo[3]);
        self.shrinked_size=self.display_screenshot.GetSize();
        mem=wx.MemoryDCFromDC(wx.ScreenDC())
        mem.SelectObject(self.screen_buffer)
        mem.Blit(0,0,screengeo[2],screengeo[3],wx.ScreenDC(),screengeo[0],screengeo[1])
        if self.is_with_mouse:
            if self.print_to_prompt:
                print "mouse abs: "+ win32api.GetCursorPos().__repr__()
            rel_x=win32api.GetCursorPos()[0]-screengeo[0]+1
            rel_y=win32api.GetCursorPos()[1]-screengeo[1]+1
            mouse_overlay_client=wx.MemoryDC(self.screen_buffer)#self.display_screenshot)
            thick_x=int((self.screen_size[0])/(self.shrinked_size[0]))+20
            thick_y=int((self.screen_size[1])/(self.shrinked_size[1]))+20
            expand_cross=50
            exp_x=expand_cross*self.screen_size[0]/self.shrinked_size[0]
            exp_y=expand_cross*self.screen_size[1]/self.shrinked_size[1]
            mouse_overlay_client.SetPen(wx.Pen("red",thick_y))
            print "wx.Pen.Colour before drawing the cursor (should be red): " + mouse_overlay_client.GetPen().GetColour().__repr__()
            mouse_overlay_client.DrawLine(rel_x-exp_x,rel_y,rel_x+exp_x,rel_y)
            print "wx.Pen.Colour after drawing the cursor (should be red): " + mouse_overlay_client.GetPen().GetColour().__repr__()
            print "It is white on my machine!"
            mouse_overlay_client.SetPen(wx.Pen("red",thick_x))
            #mouse_overlay_client.SetPen(wx.Pen(colour=self.wx_red_colour,width=thick_x))
            mouse_overlay_client.DrawLine(rel_x,rel_y-exp_y,rel_x,rel_y+exp_y)
        mem.SelectObject(wx.NullBitmap)
        self.screenshotfile=self.screen_buffer.ConvertToImage()
        self.screenshotfile.Rescale(self.display_screenshot.GetSize()[0],self.display_screenshot.GetSize()[1])
        self.Freeze()
        self.display_screenshot.SetBitmap(wx.BitmapFromImage(self.screenshotfile))
        self.Thaw()
        self.screenshot_counter+=1;
        pass

            
            
            
    def __del__(self):
        del self.screen_buffer


class gui_main(wx.Frame):
    def __init__(self,parent,working_dir):
        wx.Frame.__init__(self, parent, wx.ID_ANY, 'Bug Demo', size=(1200, 800),pos=(10,10))
        self.Bind(wx.EVT_CLOSE, self.OnCloseWindow);
        self.working_dir=working_dir;
        self.HW_selection=None
        self.sizer_L0= wx.BoxSizer( wx.HORIZONTAL)
        self.SetSizer(self.sizer_L0)
        self.sizer_L1_a=wx.BoxSizer( wx.VERTICAL)
        self.sizer_L0.Add(self.sizer_L1_a,1,flag=wx.EXPAND)
        self.panel_screenshot=panel_screenshot_monitor(self);
        self.sizer_L1_a.Add(self.panel_screenshot,1,flag=wx.EXPAND);
        
        self.sizer_L1_a.Layout()
        self.sizer_L0.Layout()

        
    def callback_connection(self):
        pass
        
    def OnCloseWindow(self, event):
        self.Destroy()


class gui_main_app(wx.App):
    def OnInit(self):
        self.main = gui_main(None,None)
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

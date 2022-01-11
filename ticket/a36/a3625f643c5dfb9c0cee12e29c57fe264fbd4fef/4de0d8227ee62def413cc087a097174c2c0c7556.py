#!/usr/bin/env python
"""
Aim: handle slider drag and release differently

More detailed:
for a wxSlider I would like to attach events for
  a) dragging the slider
  b) releasing the slider
where a) just updates something quickly and after releasing
the slider b) should do a refined update (i.e. a slightly
longer computation).

I tried the code attached below, but I can't get b), i.e.
EVT_SCROLL_THUMBRELEASE, working.
((wxPython.__version__: '2.4.2.0p', on debian linux, python 2.3))

"""

from wxPython.wx import *     


class MainWindow(wxFrame):
    def __init__(self,parent,id,title):
        wxFrame.__init__(self,parent,-4, title,size=(200,100),
                         style=wxDEFAULT_FRAME_STYLE|
                                        wxNO_FULL_REPAINT_ON_RESIZE)

        self.Slider = wxSlider(id=-1,maxValue=5,minValue=0,name='Slider',
                               parent=self,style=wxSL_HORIZONTAL,
                               validator=wxDefaultValidator,value=0)
        self.Slider.Enable(True)

        #EVT_SCROLL(self.Slider, self.OnSliderScroll)
        EVT_SCROLL_THUMBRELEASE(self.Slider, self.OnSliderScrollRelease)
        EVT_SCROLL_THUMBTRACK(self.Slider, self.OnSliderScroll)
        #EVT_SCROLL_ENDSCROLL(self.Slider, self.OnSliderScrollRelease)


    def OnSliderScroll(self, event):
        cell=self.Slider.GetValue()
        print "do something when scrolling ...",cell
        event.Skip()

    def OnSliderScrollRelease(self, event):
        cell=self.Slider.GetValue()
        print "do something after releasing the slider ...",cell
        event.Skip()

   
app = wxPySimpleApp()
frame = MainWindow(None, -1, "SliderTest")
frame.Show(1)
app.MainLoop()


 	  	 

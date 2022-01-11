#!/usr/bin/env python

import wx
import wx.richtext as rt
import os.path as p

class NumList(object):
   def __init__(self, image_path, frame, toggle=False, handler=None):
      self.path = image_path
      self.name = 'blah'
      self.frame = frame
      self.id = wx.NewId()
      self.handler = handler

   @property
   def image(self):
      path = p.join(p.dirname(__file__), 'images', self.path)
      return wx.Bitmap(path, wx.BITMAP_TYPE_PNG)

   def add(self, toolbar):
      toolbar.AddSimpleTool(self.id, self.image, isToggle=True)
      self.frame.Bind(wx.EVT_TOOL, self.handler, id=self.id)

class RichFrame(wx.Frame):
   def __init__(self,parent,id,title='',text=None,):
      wx.Frame.__init__(self,parent,id,title,size=(800,600))
      self.rtc = rt.RichTextCtrl(self, -1)
      self.statusbar = self.CreateStatusBar()
      self.toolbar = self.CreateToolBar()
      self.bulletnumber = False
      n = NumList('text_list_numbers.png', self, toggle=True,
                  handler=self.OnNumList)
      n.add(self.toolbar)

   def OnNumList(self, event):
      tb = event.GetEventObject()
      toggled = tb.GetToolState(event.GetId())
      def numlist(attr):
         attr.SetFlags(attr.GetFlags() |rt.TEXT_ATTR_BULLET_STYLE |
                       rt.TEXT_ATTR_LEFT_INDENT | rt.TEXT_ATTR_PARAGRAPH )
         attr.SetBulletStyle(rt.TEXT_ATTR_BULLET_STYLE_ALIGN_LEFT |
                             rt.TEXT_ATTR_BULLET_STYLE_ARABIC |
                             rt.TEXT_ATTR_BULLET_STYLE_PERIOD)
         attr.SetLeftIndent(20,100)
         return attr

      if toggled:
         self.ApplyNewParaAttr(numlist)
      else:
         self.ApplyNewParaAttr(self.listoff)

   def OnUpdateNumList(self, event):
      pass

   def listoff(self, attr):
      attr.SetFlags(attr.GetFlags() |rt.TEXT_ATTR_LEFT_INDENT | rt.TEXT_ATTR_PARAGRAPH | rt.TEXT_ATTR_BULLET_STYLE ^ rt.TEXT_ATTR_BULLET_STYLE_ARABIC)
      attr.SetBulletStyle(rt.TEXT_ATTR_BULLET_STYLE_NONE)
      attr.SetLeftIndent(0)
      return attr

   def para_borders(self, point):
      """ Grab the boundaries of the paragraph that point is sitting
      in, and return the (beginning, end) points""" 
      rtc = self.rtc
      rtc.SetInsertionPoint(point)
      rtc.MoveToParagraphStart()
      bp = rtc.GetInsertionPoint()
      rtc.MoveToParagraphEnd()
      ep = rtc.GetInsertionPoint()
      return (bp, ep)

   def ApplyNewParaAttr(self, func):
      """ This takes a function that expects to be handed a
      rt.TextAttrEx object, which it then manipulates as needed, and
      then the attributes are applied to the current paragragh or all
      paragraghs is the selection"""
      ##### NOTE:At this moment this does not handle selections in
      ## more than one paragragh properly
      # Basic Features
      rtc = self.rtc
      ip = rtc.GetInsertionPoint()
      attr = rt.TextAttrEx()
      bp,ep = self.para_borders(ip)
      used_space_hack = False
      if bp == ep:
         rtc.WriteText(" ")
         used_space_hack = True
         bp,ep = self.para_borders(ip)
      r = rt.RichTextRange(bp, ep)
      # This needs to handle multiple paragraghs in a selection properly.
      if rtc.HasSelection():
         r = rtc.GetSelection()
      if rtc.GetStyle(ip, attr):
         attr = func(attr)
      # Apply the style
      rtc.SetFocus()
      rtc.SetInsertionPoint(ip)
      rtc.SetStyle(r, attr)
      if used_space_hack is True:
         rtc.Delete(rt.RichTextRange(bp, ep))

   def GetCurStyle(self, rtc, ):
      attr = rt.TextAttrEx()
      attr.SetFlags(rt.TEXT_ATTR_FONT)
      cursor_at = rtc.GetInsertionPoint()
      if rtc.GetStyle(cursor_at, attr):
         return attr


class RichApp(wx.App):
   def __init__(self, redirect=False, filename=None,
                style=wx.DEFAULT_FRAME_STYLE, text=None):
      self.text = text
      wx.App.__init__(self, redirect, filename)

   def OnInit(self):
      self.frame = RichFrame(parent=None, id=-1, title="Rich Editor",
                             text=self.text)
      self.frame.Show()
      self.SetTopWindow(self.frame)
      return True

if __name__ == '__main__':
   text = "This is a test of the first and second things to be seen"
   app = RichApp(text=text)
   app.MainLoop()

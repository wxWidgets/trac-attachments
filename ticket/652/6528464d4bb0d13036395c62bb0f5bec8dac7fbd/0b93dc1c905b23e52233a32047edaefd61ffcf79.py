import wx
import wx.lib.ogl as ogl

class AppFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__( self,
                          None, -1, "Demo",
                          size=(300,300),
                          style=wx.DEFAULT_FRAME_STYLE )
        sizer = wx.BoxSizer( wx.VERTICAL )
        # put stuff into sizer

        canvas = ogl.ShapeCanvas( self )
        sizer.Add( canvas, 1, wx.GROW )

        canvas.SetBackgroundColour( "LIGHT BLUE" ) #

        diagram = ogl.Diagram()
        canvas.SetDiagram( diagram )
        diagram.SetCanvas( canvas )

        shape1 = ogl.CircleShape( 20.0 )
        shape1.SetX( 25.0 )
        shape1.SetY( 25.0 )
        canvas.AddShape( shape1 )
        evthandler = MyEvtHandler(self)
        evthandler.SetShape(shape1)
        evthandler.SetPreviousHandler(shape1.GetEventHandler())
        shape1.SetEventHandler(evthandler)

        shape2 = ogl.CircleShape( 20.0 )
        shape2.SetX( 200.0 )
        shape2.SetY( 200.0 )
        canvas.AddShape( shape2 )
        evthandler = MyEvtHandler(self)
        evthandler.SetShape(shape2)
        evthandler.SetPreviousHandler(shape2.GetEventHandler())
        shape2.SetEventHandler(evthandler)

        line = MyLineShape(canvas, shape1, shape2, 'start', 'middle', 'end')        
        canvas.AddShape( line )
        evthandler = MyEvtHandler(self)
        evthandler.SetShape(line)
        evthandler.SetPreviousHandler(line.GetEventHandler())
        line.SetEventHandler(evthandler)
        
        diagram.ShowAll( 1 )

        # apply sizer
        self.SetSizer(sizer)
        self.SetAutoLayout(1)
        self.Show(1)


class MyLineShape(ogl.LineShape):
    def __init__(self, canvas, from_shape, to_shape, start_label, middle_label, end_label):
          
        ogl.LineShape.__init__(self)
        dc = wx.ClientDC(canvas)  # used for measuring
        dc.SetBackgroundMode(wx.SOLID)
        self.FormatText(dc, middle_label, 0)
        self.FormatText(dc, start_label, 1)
        self.FormatText(dc, end_label, 2)
        self.SetPen(wx.BLACK_PEN)
        self.SetBrush(wx.BLACK_BRUSH)
        self.MakeLineControlPoints(2)
        from_shape.AddLine(self, to_shape)
        
    def DrawRegion(self, dc, region, x, y):
        """Format one region at this position."""
        if self.GetDisableLabel():
            return

        w, h = region.GetSize()

        # Get offset from x, y
        xx, yy = region.GetPosition()

        xp = xx + x
        yp = yy + y

        # First, clear a rectangle for the text IF there is any
        if len(region.GetFormattedText()):
            dc.SetPen(self.GetBackgroundPen())
            dc.SetBrush(self.GetBackgroundBrush())

            # Now draw the text
            if region.GetFont():
                dc.SetFont(region.GetFont())
                # Don't draw the rectangle.
                #dc.DrawRectangle(xp - w / 2.0, yp - h / 2.0, w, h)

                if self._pen:
                    dc.SetPen(self._pen)
                dc.SetTextForeground(region.GetActualColourObject())

                ogl.DrawFormattedText(dc, region.GetFormattedText(), xp, yp, w, h, 
                        region.GetFormatMode()|4)
                        
class MyEvtHandler(ogl.ShapeEvtHandler):
    def __init__(self, frame):
        ogl.ShapeEvtHandler.__init__(self)
        self.statbarFrame = frame

    def OnLeftClick(self, x, y, keys=0, attachment=0):
        shape = self.GetShape()
        canvas = shape.GetCanvas()
        dc = wx.ClientDC(canvas)
        canvas.PrepareDC(dc)

        if shape.Selected():
            shape.Select(False, dc)
            #canvas.Redraw(dc)
            canvas.Refresh(False)
        else:
            redraw = False
            shapeList = canvas.GetDiagram().GetShapeList()
            toUnselect = []

            for s in shapeList:
                if s.Selected():
                    # If we unselect it now then some of the objects in
                    # shapeList will become invalid (the control points are
                    # shapes too!) and bad things will happen...
                    toUnselect.append(s)

            shape.Select(True, dc)

            if toUnselect:
                for s in toUnselect:
                    s.Select(False, dc)

                ##canvas.Redraw(dc)
                canvas.Refresh(False)

    def OnEndDragLeft(self, x, y, keys=0, attachment=0):
        shape = self.GetShape()
        ogl.ShapeEvtHandler.OnEndDragLeft(self, x, y, keys, attachment)

        if not shape.Selected():
            self.OnLeftClick(x, y, keys, attachment)

    def OnSizingEndDragLeft(self, pt, x, y, keys, attch):
        ogl.ShapeEvtHandler.OnSizingEndDragLeft(self, pt, x, y, keys, attch)

    def OnMovePost(self, dc, x, y, oldX, oldY, display):
        shape = self.GetShape()
        ogl.ShapeEvtHandler.OnMovePost(self, dc, x, y, oldX, oldY, display)
        if "wxMac" in wx.PlatformInfo:
            shape.GetCanvas().Refresh(False)

    def OnLeftDoubleClick(self, *dontcare):
        print "%s\n" % self.GetShape()

    def OnRightClick(self, *dontcare):
         print "%s\n" % self.GetShape()


app = wx.PySimpleApp()
ogl.OGLInitialize()
frame = AppFrame()
app.MainLoop()

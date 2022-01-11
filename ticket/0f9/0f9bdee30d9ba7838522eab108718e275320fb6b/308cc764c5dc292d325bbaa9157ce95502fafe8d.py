import wx
from wx.lib.agw.hypertreelist import (
    _MARGIN,
    _LINEATROOT,
    _BTNWIDTH,
    _BTNHEIGHT,
    _MININDENT,
    _MAX_WIDTH,
    TR_NO_HEADER,
    TR_ALIGN_WINDOWS,
    IsBufferingSupported,
    TreeListMainWindow as AGWTreeListMainWindow,
    HyperTreeList as AGWHyperTreeList,
    TreeListHeaderWindow
)
from datetime import datetime

N_NODES = 5000
CONNECTOR_STYLE = wx.STIPPLE

class TreeListMainWindow(AGWTreeListMainWindow):
    
    def __init__(self, *args, **kwargs):
        super(TreeListMainWindow, self).__init__(*args, **kwargs)
        self._init_pos = False
    
    def OnEraseBackground(self, event):
        """
        Prevent the background to be erased each time the view is scrolled.
        """
        pass
    
    def IsItemInView(self, item):
        """
        Return if an item is in the visible part of the scrolled view.
        """
        clientSize = self.GetClientSize()
        x, y = self.CalcScrolledPosition((item._x, item._y))
        
        if (y > clientSize.y) or (y + item._height < 0) :
            return False
        else :
            return True
    
    def GetChildrenRecursively(self, item, check_expand=False):
        """
        Get children recursively.
        """
        children = list()
        nodes = item.GetChildren()
        n_children = len(nodes)
        for n in xrange(n_children):
            children.append(nodes[n])
            if not check_expand or nodes[n].IsExpanded() :
                children.extend(self.GetChildrenRecursively(nodes[n], check_expand=check_expand))
        return children
    
    def GetParents(self, item):
        """Get parent nodes."""
        parents = list()
        parent = item.GetParent()
        while (parent != self.GetRootItem()) :
            parents.append(parent)
            parent = parent.GetParent()
        return parents
    
    def SetupItemPositions(self, item, level, x_maincol, y):
        """
        Setup all item positions before painting visible items.
        """
        root = self.GetRootItem()
        children = [root] if (not self.HasAGWFlag(wx.TR_HIDE_ROOT) and (item == root) and (level == 0)) else item.GetChildren()
        
        for child in children :
            # calculate position of vertical lines
            x = x_maincol + _MARGIN  # start of column
    
            if self.HasAGWFlag(wx.TR_LINES_AT_ROOT):
                x += _LINEATROOT  # space for lines at root
                
            if self.HasButtons():
                x += (self._btnWidth - self._btnWidth2)  # half button space
            else:
                x += (self._indent - self._indent / 2)
            
            if self.HasAGWFlag(wx.TR_HIDE_ROOT):
                x += self._indent * (level)  # indent but not level 1
            else:
                x += self._indent * (level + 1)  # indent according to level
            
            # set position of vertical line
            child.SetX(x)
            child.SetY(y)
    
            h = self.GetLineHeight(child)
            y += h
            
            if self.IsExpanded(child) :
                y = self.SetupItemPositions(child, level + 1, x_maincol, y)
        
        return y
    
    def OnPaint(self, event):
        """
        Paint all tree items.
        """
        if self._buffered:
            # paint the background
            dc = wx.BufferedPaintDC(self)
            rect = self.GetUpdateRegion().GetBox()
            dc.SetClippingRect(rect)
            dc.SetBackground(wx.Brush(self.GetBackgroundColour()))
            dc.SetTextForeground(self.GetForegroundColour())
            if self._backgroundImage:
                self.TileBackground(dc)
            else:
                dc.Clear()
        else:
            dc = wx.BufferedPaintDC(self)
            dc.SetBackground(wx.Brush(self.GetBackgroundColour()))
            dc.SetTextForeground(self.GetForegroundColour())
            dc.Clear()

        self.PrepareDC(dc)

        if not self._anchor or self.GetColumnCount() <= 0:
            return

        # calculate button size
        if self._imageListButtons:
            self._btnWidth, self._btnHeight = self._imageListButtons.GetSize(0)
        elif self.HasButtons():
            self._btnWidth = _BTNWIDTH
            self._btnHeight = _BTNHEIGHT
        
        self._btnWidth2 = self._btnWidth / 2
        self._btnHeight2 = self._btnHeight / 2

        # calculate image size
        if self._imageListNormal:
            self._imgWidth, self._imgHeight = self._imageListNormal.GetSize(0)
        
        self._imgWidth2 = self._imgWidth / 2
        self._imgHeight2 = self._imgHeight / 2

        if self._imageListCheck:
            self._checkWidth, self._checkHeight = self._imageListCheck.GetSize(0)

        self._checkWidth2 = self._checkWidth / 2
        self._checkHeight2 = self._checkHeight / 2
            
        # calculate indent size
        if self._imageListButtons:
            self._indent = max(_MININDENT, self._btnWidth + _MARGIN)
        elif self.HasButtons():
            self._indent = max(_MININDENT, self._btnWidth + _LINEATROOT)
        
        # set default values
        dc.SetFont(self._normalFont)
        dc.SetPen(self._dottedPen)

        # calculate column start and paint
        x_maincol = 0
        for i in xrange(self.GetMainColumn()):
            if not self._owner.GetHeaderWindow().IsColumnShown(i):
                continue
            x_maincol += self._owner.GetHeaderWindow().GetColumnWidth(i)
        
        # refresh item positions and retrieve
        # only items contained in the view
        if not self._init_pos :
            self.SetupItemPositions(self._anchor, 0, x_maincol, 0)
            self._init_pos = False
        
        # get visible items i.e. those having an
        # ordinate located inside the scrolled view
        items = [k for k in self.GetChildrenRecursively(self.GetRootItem(), check_expand=True) if self.IsItemInView(k)]
        self.PaintItems(items, dc, x_maincol)
    
    def PaintItems(self, items, dc, x_maincol):
        root = self.GetRootItem()
        v_lines = list()
        h_lines = list()
        drawn_parents = list()
        for item in items :
            h = self.GetLineHeight(item)
            x = item.GetX()
            y_top = item.GetY()
            y_mid = y_top + (h / 2)

            exposed_x = dc.LogicalToDeviceX(0)
            exposed_y = dc.LogicalToDeviceY(y_top)

            # horizontal lines between rows?
            draw_row_lines = self.HasAGWFlag(wx.TR_ROW_LINES)
            
            if self.IsExposed(exposed_x, exposed_y, _MAX_WIDTH, h + draw_row_lines):
                # draw lines
                if draw_row_lines:
                    self.DrawLine(dc, y_top, h)
                
                # draw item
                self.PaintItem(item, dc)
                
                # restore DC objects
                dc.SetBrush(wx.WHITE_BRUSH)
                dc.SetPen(self._dottedPen)
    
                # clip to the column width
                clip_width = self._owner.GetHeaderWindow().GetColumn(self._main_column).GetWidth()
    
                if not self.HasAGWFlag(wx.TR_NO_LINES):  # connection lines
                    # draw the horizontal line here
                    dc.SetPen(self._dottedPen)
                    x2 = x - self._indent
                    if x2 < (x_maincol + _MARGIN):
                        x2 = x_maincol + _MARGIN
                    x3 = x + (self._btnWidth - self._btnWidth2)
                    if self.HasButtons():
                        if item.HasPlus():
                            h_lines.append((x2, y_mid, x - self._btnWidth2, y_mid))
                            h_lines.append((x3, y_mid, x3 + _LINEATROOT, y_mid))
                        else:
                            h_lines.append((x2, y_mid, x3 + _LINEATROOT, y_mid))
                    else:
                        h_lines.append((x2, y_mid, x - self._indent / 2, y_mid))
                    
                if item.HasPlus() and self.HasButtons():  # should the item show a button?
                    if self._imageListButtons:
                        # draw the image button here
                        self.DrawImageButton(item, dc, x, y_mid)
                    elif self.HasAGWFlag(wx.TR_TWIST_BUTTONS):
                        # draw the twisty button here
                        self.DrawTwistedButton(item, dc, x_maincol, x, y_mid, y_top, clip_width, h)
                    else:  # if (HasAGWFlag(wxTR_HAS_BUTTONS))
                        rect = wx.Rect(x - self._btnWidth2, y_mid - self._btnHeight2, self._btnWidth, self._btnHeight)
                        flag = (item.IsExpanded() and [wx.CONTROL_EXPANDED] or [0])[0]
                        wx.RendererNative.GetDefault().DrawTreeItemButton(self, dc, rect, flag)        
    
            # restore DC objects
            dc.SetBrush(wx.WHITE_BRUSH)
            dc.SetPen(self._dottedPen)
            dc.SetTextForeground(wx.BLACK)
                
            # draw vertical line
            
            parent = item.GetParent()
            if not self.HasAGWFlag(wx.TR_NO_LINES) :
                # drawn connectors relative to parents
                parents = self.GetParents(item)
                for parent in parents :
                    if parent not in drawn_parents and parent.IsExpanded() :
                        last = self.GetLastChild(parent)
                        
                        # get parent properties
                        x_parent = parent.GetX()
                        y_parent = parent.GetY()
                        h_parent = parent.GetHeight()
                        
                        # get last child properties
                        y_last = last.GetY()
                        h_last = last.GetHeight()
                        
                        # if the scrolled position of the starting point
                        # of the line is too long clip the ordinate of the
                        # line to the ordinate of the first item to reduce
                        # processing time of DrawLineList
                        pos = self.CalcScrolledPosition((x_parent, y_parent))
                        y_start = y_parent + h_parent if (pos[1] >= 0) else items[0].GetY() - self.GetClientSize()[1]
                        y_end = y_last + h_last / 2
                        
                        v_lines.append((x_parent, y_start + 1, x_parent, y_end))
                    
                        drawn_parents.append(parent)
        
        # draw all connectors in a row
        grey = (160, 160, 160)
        pen = wx.Pen(grey, 1, wx.STIPPLE)
        dc.SetPen(pen)
        
        # draw horizontal connectors
        if len(h_lines) :
            t1 = datetime.now()
            dc.DrawLineList(h_lines)
            t2 = datetime.now()
            print "h_lines:%s, time:%s" % (len(h_lines), t2 - t1)
        
        # draw vertical connectors
        if len(v_lines) :
            t1 = datetime.now()
            dc.DrawLineList(v_lines)
            t2 = datetime.now()
            print "v_lines:%s, time:%s" % (len(v_lines), t2 - t1)

class HyperTreeList(AGWHyperTreeList):
    
    def __init__(self, parent, id=wx.ID_ANY, pos=wx.DefaultPosition, size=wx.DefaultSize, style=0, agwStyle=wx.TR_DEFAULT_STYLE, validator=wx.DefaultValidator, name="HyperTreeList"):
        wx.PyControl.__init__(self, parent, id, pos, size, style, validator, name)
        
        self._header_win = None
        self._main_win = None
        self._headerHeight = 0
        self._attr_set = False
        main_style = style & ~(wx.SIMPLE_BORDER | wx.SUNKEN_BORDER | wx.DOUBLE_BORDER | wx.RAISED_BORDER | wx.STATIC_BORDER)

        self._agwStyle = agwStyle
        
        self._main_win = TreeListMainWindow(self, -1, wx.Point(0, 0), size, main_style, agwStyle, validator)
        self._main_win._buffered = False
        
        self._header_win = TreeListHeaderWindow(self, -1, self._main_win, wx.Point(0, 0), wx.DefaultSize, wx.TAB_TRAVERSAL)
        self._header_win._buffered = False
        
        self.CalculateAndSetHeaderHeight()
        self.Bind(wx.EVT_SIZE, self.OnSize)

        self.SetBuffered(IsBufferingSupported())
        self._main_win.SetAGWWindowStyleFlag(agwStyle)

class MainFrame(wx.Frame):

    def __init__(self, parent):
        agwStyle = (
            wx.TR_DEFAULT_STYLE | 
            wx.TR_HIDE_ROOT | 
            wx.TR_MULTIPLE | 
            wx.TR_FULL_ROW_HIGHLIGHT | 
            TR_NO_HEADER | 
            wx.TR_HAS_BUTTONS | 
            wx.TR_HAS_VARIABLE_ROW_HEIGHT | 
            TR_ALIGN_WINDOWS 
        )
        wx.Frame.__init__(self, parent, -1, "Subclassing HyperTreeList", size=(-1, 800))
        
        # configuring HTL
        tree_list = HyperTreeList(self, size=(-1, 800), agwStyle=agwStyle)
        tree_list.EnableSelectionVista(True)
        column = tree_list.AddColumn("labels", width=200)
        root = tree_list.AddRoot("Root")
        
        # create 2 nodes
        first = tree_list.AppendItem(root, "First Node")
        second = tree_list.AppendItem(root, "Second Node")
        
        # create sub nodes
        for i in xrange(0, N_NODES + 1) :
            tree_list.AppendItem(first, "SubNode 1.%s" % (i + 1))
            tree_list.AppendItem(second, "SubNode 2.%s" % (i + 1))
        
        tree_list.Expand(second)

if __name__ == "__main__" :
    app = wx.PySimpleApp()
    frame = MainFrame(None)
    app.SetTopWindow(frame)
    frame.Show()
    app.MainLoop()

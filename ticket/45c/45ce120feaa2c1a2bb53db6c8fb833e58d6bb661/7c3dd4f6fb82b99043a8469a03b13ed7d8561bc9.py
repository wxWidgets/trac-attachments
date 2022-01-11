def XYToCell(self, x, y):
    # For virtual grids, XYToCell doesn't work properly
    # For some reason, the width and heights of the labels
    # are not computed properly and thw row and column
    # returned are computed as if the window wasn't
    # scrolled
    # This function replaces XYToCell for Virtual Grids

    rowwidth = self.GetGridRowLabelWindow().GetRect().width
    colheight = self.GetGridColLabelWindow().GetRect().height
    yunit, xunit = self.GetScrollPixelsPerUnit()
    xoff =  self.GetScrollPos(wxHORIZONTAL) * xunit
    yoff = self.GetScrollPos(wxVERTICAL) * yunit

    # the solution is to offset the x and y values
    # by the width and height of the label windows
    # and then adjust by the scroll position
    # Then just go through the columns and rows
    # incrementing by the current column and row sizes
    # until the offset points lie within the computed
    # bounding boxes.
    x += xoff - rowwidth
    xpos = 0
    for col in range(self.GetNumberCols()):
        nextx = xpos + self.GetColSize(col)            
        if xpos <= x <= nextx:
            break
        xpos = nextx

    y += yoff - colheight
    ypos = 0
    for row in range(self.GetNumberRows()):
        nexty = ypos + self.GetRowSize(row)
        if ypos <= y <= nexty:
            break
        ypos = nexty

        return row, col

 	  	 

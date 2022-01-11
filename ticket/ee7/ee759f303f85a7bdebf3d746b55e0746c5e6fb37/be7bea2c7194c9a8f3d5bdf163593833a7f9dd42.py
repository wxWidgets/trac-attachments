import wx
import wx.lib.agw.aui as aui
import wx.dataview as dv
    
import cPickle

# class VarNodeDropData(wx.CustomDataObject):
#     NAME = "VarNode"
#     PICKLE_PROTOCOL = 2
#     
#     def __init__(self):
#         wx.CustomDataObject.__init__(self, VarNodeDropData.NAME)
#             
#     def setNode(self, node):
#         data = cPickle.dumps(node, VarNodeDropData.PICKLE_PROTOCOL)        
#         self.SetData(data)
#         
#     def getNode(self):
#         return cPickle.loads(self.GetData())
# 
# class VarNodeDropTarget(wx.PyDropTarget):
#     def __init__(self, text):
#         wx.PyDropTarget.__init__(self)
#         self._text = text
#         
#         # specify the type of data we will accept
#         self.data = VarNodeDropData()
#         self.SetDataObject(self.data)
#                         
#     def OnData(self, x, y, defaultResult):
#         print "---OnData", self.GetData()
#         
#         if not self.GetData():
#             return wx.DragNone
#         
#         node = self.data.getNode()
#         
#         self._text.AppendText(node)
#         
#         return defaultResult
    
    
class TextDropTarget(wx.TextDropTarget):
    def __init__(self, text):
        wx.TextDropTarget.__init__(self)
        self._text = text
    

class MyFrame(wx.Frame):
    def __init__(self, parent):
        wx.Frame.__init__(self, parent, -1, "Table")
        
        panel = wx.Panel(self)
                
        mgr = aui.AuiManager()
        mgr.SetManagedWindow(panel)
        
        tree = wx.TreeCtrl(panel)
        root = tree.AddRoot("Root")
        tree.AppendItem(root, "child")
        tree.Bind(wx.EVT_TREE_BEGIN_DRAG, self._onDragText)
        
        dvcTree = dv.DataViewTreeCtrl(panel)
        root = dvcTree.AppendContainer(dv.NullDataViewItem, "Root")
        dvcTree.AppendItem(root, "child")

#         dvcTree.EnableDragSource(VarNodeDropData().GetFormat())
#         dvcTree.Bind(dv.EVT_DATAVIEW_ITEM_BEGIN_DRAG, self._onDragDv)
        dvcTree.EnableDragSource(wx.PyTextDataObject().GetFormat())
        dvcTree.Bind(dv.EVT_DATAVIEW_ITEM_BEGIN_DRAG, self._onDragDvText)        
        
        
        text = wx.TextCtrl(panel, style=wx.TE_MULTILINE)
#         dropTarget = VarNodeDropTarget(text)
        dropTarget = TextDropTarget(text)
        text.SetDropTarget(dropTarget)

        mgr.AddPane(text, aui.AuiPaneInfo().CenterPane().CloseButton(False).MinimizeButton(False).MaximizeButton(False))    
        mgr.AddPane(tree, aui.AuiPaneInfo().Left().Name("Tree").MinimizeButton(True).MaximizeButton(True).CloseButton(True).BestSize((250, 250)).Caption("Tree"))
        mgr.AddPane(dvcTree, aui.AuiPaneInfo().Left().Name("DVC Tree").MinimizeButton(True).MaximizeButton(True).CloseButton(True).BestSize((250, 250)).Caption("DVC Tree"))
        
        mgr.Update()
        mgr.Update()        
    
    
 
    def _onDragText(self, event):
        print "Starting to drag"
        dataObject = wx.PyTextDataObject("Hi Mom")
       
        dragSource = wx.DropSource(self)
        dragSource.SetData(dataObject)
        result = dragSource.DoDragDrop(True)
        print "Finshed", result
       

    def _onDrag(self, event):
        print "Starting to drag"
    
        dataObject = VarNodeDropData()
        dataObject.setNode("Hi mom\n")       
        dataObject = wx.PyTextDataObject("Hi Mom")
       
        dragSource = wx.DropSource(self)
        dragSource.SetData(dataObject)
        result = dragSource.DoDragDrop(True)       

    def _onDragDvText(self, event):
        print "Starting to drag dataview text"
        
        dataObject = wx.PyTextDataObject("Hi Mom")
        
        #AttributeError: 'DataViewEvent' object has no attribute 'SetDragFlags'
        #event.SetDragFlags(wx.Drag_DefaultMove)
        
        event.SetDataObject(dataObject)
            
    def _onDragDv(self, event):
        print "Starting to drag dataview"
        
        dataObject = VarNodeDropData()
        dataObject.setNode("Hi mom\n")
        
        #AttributeError: 'DataViewEvent' object has no attribute 'SetDragFlags'
        #event.SetDragFlags(wx.Drag_DefaultMove)
        
        print dir(event)
        event.SetDataObject(dataObject)
        
if __name__ == "__main__":
    from wx.lib.mixins.inspection import InspectionMixin 
    
    class TestApp(wx.App, InspectionMixin): 
            def OnInit(self): 
                self.Init() 
                frame = MyFrame(None)
                
                self.SetTopWindow(frame)
                
                frame.SetMinSize((1024,768))
                frame.Show()
                
                return 1 
            
    app = TestApp()
    
    app.MainLoop()

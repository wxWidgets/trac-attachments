import wx
from dlgBase import DlgBase
from dlgButtons import DlgButtons
from viewer import Viewer

class HSizerFrame(wx.Frame):
	def __init__(self):
		wx.Frame.__init__(self, None, -1, "Jimmy's PyPaint", pos=(0,0), size=(1280,760))
		self.createMenus()
		self.createStatusBar()
		self.createToolBar()
		self.createDrawBar()
		sizer = wx.BoxSizer(wx.HORIZONTAL)
		self.panelLeft = wx.Panel(self, -1, size=(200,-1))
		self.panelLeft.SetBackgroundColour(wx.Color(128,128,255))
		self.dlgButtons = DlgButtons(self.panelLeft, -1)
		self.dlgButtons.Show(True)
		self.Bind(wx.EVT_BUTTON, self.OnFileNew, self.dlgButtons.bNew)
		self.dlgNew = DlgBase(self.panelLeft, -1)
		self.dlgNew.Show(False)
		self.Bind(wx.EVT_BUTTON, self.OnDlgOk, self.dlgNew.okButton)
		self.dlgSelRect = DlgBase(self.panelLeft, -1)
		self.dlgSelRect.Show(False)
		button = wx.Button(self.panelLeft, label="Click me", pos=(75,225), size=(75,25))
		self.Bind(wx.EVT_BUTTON, self.OnFileNew, button)
		sizer.Add(self.panelLeft, flag=wx.EXPAND)
		self.listBook = wx.Listbook(self, -1, style=wx.BK_RIGHT)
		sizer.Add(self.listBook, 1, flag=wx.EXPAND)
		self.imageList = wx.ImageList(100,100)
		self.listBook.SetImageList(self.imageList)
		self.Bind(wx.EVT_NOTEBOOK_PAGE_CHANGED, self.OnPageChanged, self.listBook)
		self.Bind(wx.EVT_NOTEBOOK_PAGE_CHANGING, self.OnPageChanging, self.listBook)
		self.SetSizer(sizer)
		
		self.wildcard = "All image files (*.bmp;*.png;*.jpeg;*.jpg;*.gif)|*.bmp;*.png;*.jpeg;*.jpg;*.gif" \
			"|BMP files (*.bmp)|*.bmp|PNG files (*.png)|*.png" \
			"|JPEG files (*.jpeg;*.jpg)|*.jpeg;*jpg|GIF files (*.gif)|*.gif" \
			"All files (*.*)|*.*"
		
		self.filesList = []
		self.curFile = ""
		self.viewersList = []
		self.curViewer = None
		self.iconsIdxList = []
		self.curIconIdx = -1
		self.modifiedList = []
		self.curModified = False
		self.curIndex = -1
		
		self.baseDir = "C:\\Documents and Settings\\jimmy g\\My Documents\\My Pictures"
		self.lastOpenDir = self.baseDir #Save these on shutdown & restore on startup
		self.lastOpenFilterIx = 0
		self.lastSaveDir = self.baseDir
		self.lastSaveFilterIx = 0
		

		self.curDialog = self.dlgButtons
		
	def createMenus(self):
		self.menuBar = wx.MenuBar()
		#self.menuBar.SetOwnBackgroundColour(wx.Color(255,255,128))
		fileMenu = wx.Menu()
		self.menuBar.Append(fileMenu, "File")
		
		bmp = wx.Image("images\\new24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.fileNewItem = fileMenu.Append(-1, "New ...", "Create new image")
		self.fileNewItem.SetBitmap(bmp)
		self.Bind(wx.EVT_MENU, self.OnFileNew, self.fileNewItem)
		
		bmp = wx.Image("images\\open24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.fileOpenItem = fileMenu.Append( -1, "Open ...", "Presents Open File Dialog")
		self.fileOpenItem.SetBitmap(bmp)
		self.Bind(wx.EVT_MENU, self.OnFileOpen, self.fileOpenItem)
		
		fileMenu.AppendSeparator()
		
		bmp = wx.Image("images\\save24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.fileSaveItem = fileMenu.Append( -1, "Save", "Save current file")
		self.fileSaveItem.SetBitmap(bmp)
		self.Bind(wx.EVT_MENU, self.OnFileSave, self.fileSaveItem)
		
		bmp = wx.Image("images\\saveAs24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.fileSaveAsItem = fileMenu.Append( -1, "Save As ...", "Save current file as different name")
		self.fileSaveAsItem.SetBitmap(bmp)
		self.Bind(wx.EVT_MENU, self.OnFileSaveAs, self.fileSaveAsItem)
		
		self.fileSaveCopyItem = fileMenu.Append( -1, "Save Copy ...", "Save a copy of the current image")
		self.Bind(wx.EVT_MENU, self.OnFileSaveCopy, self.fileSaveCopyItem)
		
		self.fileSaveAllItem = fileMenu.Append( -1, "Save All", "Save all modified files")
		self.Bind(wx.EVT_MENU, self.OnFileSaveAll, self.fileSaveAllItem)
		
		fileMenu.AppendSeparator()
		
		bmp = wx.Image("images\\close24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.fileCloseItem = fileMenu.Append( -1, "Close", "Close current file")
		self.fileCloseItem.SetBitmap(bmp)
		self.Bind(wx.EVT_MENU, self.OnFileClose, self.fileCloseItem)
		
		self.fileCloseAllItem = fileMenu.Append( -1, "Close All", "Close all files")
		self.Bind(wx.EVT_MENU, self.OnFileCloseAll, self.fileCloseAllItem)
		
		fileMenu.AppendSeparator()
		
		bmp = wx.Image("images\\delete24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.fileDeleteItem = fileMenu.Append( -1, "Delete", "Deletes current file")
		self.fileDeleteItem.SetBitmap(bmp)
		self.Bind(wx.EVT_MENU, self.OnFileDelete, self.fileDeleteItem)
		
		fileMenu.AppendSeparator()
		
		self.fileRevertItem = fileMenu.Append( -1, "Revert", "Revert to original file")
		self.Bind(wx.EVT_MENU, self.OnFileRevert, self.fileRevertItem)
		
		fileMenu.AppendSeparator()
		
		self.filePrintItem = fileMenu.Append( -1, "Print ...", "Print current image")
		self.Bind(wx.EVT_MENU, self.OnFilePrint, self.filePrintItem)
		
		fileMenu.AppendSeparator()
		
		self.fileRecentFilesMenu = wx.Menu()
		fileMenu.AppendMenu(-1, "RecentFiles", self.fileRecentFilesMenu)
		
		fileMenu.AppendSeparator()
		
		self.fileExitItem = fileMenu.Append( -1, "Exit", "Close program")
		self.Bind(wx.EVT_MENU, self.OnFileExit, self.fileExitItem)
		
		viewMenu = wx.Menu()
		self.menuBar.Append(viewMenu, "View")
		
		self.view10xItem = viewMenu.AppendRadioItem(-1, "10x", "Zoom to 10x size")
		self.Bind(wx.EVT_MENU, self.OnViewMag, self.view10xItem)
		self.view8xItem = viewMenu.AppendRadioItem(-1, "8x", "Zoom to 8x size")
		self.Bind(wx.EVT_MENU, self.OnViewMag, self.view8xItem)
		self.view6xItem = viewMenu.AppendRadioItem(-1, "6x", "Zoom to 6x size")
		self.Bind(wx.EVT_MENU, self.OnViewMag, self.view6xItem)
		self.view4xItem = viewMenu.AppendRadioItem(-1, "4x", "Zoom to 4x size")
		self.Bind(wx.EVT_MENU, self.OnViewMag, self.view4xItem)
		self.view3xItem = viewMenu.AppendRadioItem(-1, "3x", "Zoom to 3x size")
		self.Bind(wx.EVT_MENU, self.OnViewMag, self.view3xItem)
		self.view2xItem = viewMenu.AppendRadioItem(-1, "2x", "Zoom to 2x size")
		self.Bind(wx.EVT_MENU, self.OnViewMag, self.view2xItem)
		self.view1xItem = viewMenu.AppendRadioItem(-1, "1x", "Zoom to 1x size")
		self.view1xItem.Check(True)
		self.Bind(wx.EVT_MENU, self.OnViewMag, self.view1xItem)
		self.view75xItem = viewMenu.AppendRadioItem(-1, ".75x", "Zoom to .75x size")
		self.Bind(wx.EVT_MENU, self.OnViewMag, self.view75xItem)
		self.view50xItem = viewMenu.AppendRadioItem(-1, ".50x", "Zoom to .50x size")
		self.Bind(wx.EVT_MENU, self.OnViewMag, self.view50xItem)
		self.view25xItem = viewMenu.AppendRadioItem(-1, ".25x", "Zoom to .25x size")
		self.Bind(wx.EVT_MENU, self.OnViewMag, self.view25xItem)
		self.view125xItem = viewMenu.AppendRadioItem(-1, ".125x", "Zoom to .125x size")
		self.Bind(wx.EVT_MENU, self.OnViewMag, self.view125xItem)
		
		editMenu = wx.Menu()
		self.menuBar.Append(editMenu, "Edit")
		
		#..........put this here for a test
		bmp = wx.Image("images\\selAll24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.editSelectAllItem = editMenu.Append(-1, "Select All", "Select entire image")
		self.editSelectAllItem.SetBitmap(bmp)
		
		editMenu.AppendSeparator()
		#............
		
		self.editUndoBmpDis = wx.Image("images\\undo24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.editUndoBmpEna = wx.Image("images\\undoEnab24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.editUndoItem = editMenu.Append(-1, "Undo", "When enabled, undoes last action")
		self.editUndoItem.SetBitmap(self.editUndoBmpDis)
		self.Bind(wx.EVT_MENU, self.OnEditUndo, self.editUndoItem)
		
		self.editRedoBmpDis = wx.Image("images\\redo24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.editRedoBmpEna = wx.Image("images\\redoEnab24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.editRedoItem = editMenu.Append(-1, "Redo", "When enabled, redoes last undone action")
		self.editRedoItem.SetBitmap(self.editRedoBmpDis)
		self.Bind(wx.EVT_MENU, self.OnEditRedo, self.editRedoItem)
		
		editMenu.AppendSeparator()
		
		bmp = wx.Image("images\\cut24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.editCutItem = editMenu.Append(-1, "Cut", "Cuts selection from image")
		self.editCutItem.SetBitmap(bmp)
		self.Bind(wx.EVT_MENU, self.OnEditCut, self.editCutItem)
		
		bmp = wx.Image("images\\copy24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.editCopyItem = editMenu.Append(-1, "Copy", "Copies the selection to the clipboard")
		self.editCopyItem.SetBitmap(bmp)
		self.Bind(wx.EVT_MENU, self.OnEditCopy, self.editCopyItem)
		
		self.editCopyAllItem = editMenu.Append(-1, "Copy All", "Copies entire image to the clipboard")
		self.Bind(wx.EVT_MENU, self.OnEditCopyAll, self.editCopyAllItem)
		
		self.editCreateNewItem = editMenu.Append(-1, "Create New", "Creates a new image from the selection")
		self.Bind(wx.EVT_MENU, self.OnEditCreateNew, self.editCreateNewItem)
		
		self.editDuplicateItem = editMenu.Append(-1, "Duplicate", "Duplicates the current image in its current state")
		self.Bind(wx.EVT_MENU, self.OnEditDuplicate, self.editDuplicateItem)
		
		bmp = wx.Image("images\\paste24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.editPasteItem = editMenu.Append(-1, "Paste", "Pastes clipboard contents to current image")
		self.editPasteItem.SetBitmap(bmp)
		self.Bind(wx.EVT_MENU, self.OnEditPaste, self.editPasteItem)
		
		sizeMenu = wx.Menu()
		self.menuBar.Append(sizeMenu, "Size")
		
		self.sizeDoubleItem = sizeMenu.Append(-1, "Double", "Doubles the size of the image without pixel averaging")
		self.Bind(wx.EVT_MENU, self.OnSizeDouble, self.sizeDoubleItem)
		
		self.sizeDoubleSmItem = sizeMenu.Append(-1, "Double Smooth", "Doubles the size of the image with pixel averaging")
		self.Bind(wx.EVT_MENU, self.OnSizeDoubleSm, self.sizeDoubleSmItem)
		
		self.sizeHalveItem = sizeMenu.Append(-1, "Halve", "Halves the size of the image")
		self.Bind(wx.EVT_MENU, self.OnSizeHalve, self.sizeHalveItem)
		
		sizeMenu.AppendSeparator()
		
		bmp = wx.Image("images\\crop24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.sizeCropItem = sizeMenu.Append(-1, "Crop ...", "Crop the image in various ways")
		self.sizeCropItem.SetBitmap(bmp)
		self.Bind(wx.EVT_MENU, self.OnSizeCrop, self.sizeCropItem)
		
		bmp = wx.Image("images\\strshr24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.sizeStrShrItem = sizeMenu.Append(-1, "Stretch/Shrink ...", "Stretch/Shrink the image")
		self.sizeStrShrItem.SetBitmap(bmp)
		self.Bind(wx.EVT_MENU, self.OnSizeStrShr, self.sizeStrShrItem)
		
		bmp = wx.Image("images\\resize24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.sizeResizeItem = sizeMenu.Append(-1, "Resize ...", "Resize the underlying canvas")
		self.sizeResizeItem.SetBitmap(bmp)
		self.Bind(wx.EVT_MENU, self.OnSizeResize, self.sizeResizeItem)
		
		self.SetMenuBar(self.menuBar)
		
	def createToolBar(self):
		self.toolBar = wx.ToolBar(self, -1)
		self.toolBar.SetBackgroundColour(wx.Color(255,255,128))
		self.toolBar.SetToolBitmapSize((24,24))
		bmp = wx.Image("images\\open24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.fileOpenTool = self.toolBar.AddSimpleTool(-1, bmp, "", "Presents Open File Dialog")
		self.Bind(wx.EVT_MENU, self.OnFileOpen, self.fileOpenTool)
		bmp = wx.Image("images\\close24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.fileCloseTool = self.toolBar.AddSimpleTool(-1, bmp, "", "Closes current file")
		#self.fileCloseTool.Enable(False)
		bmp = wx.Image("images\\save24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.fileSaveTool = self.toolBar.AddSimpleTool(-1, bmp, "", "Saves current file")
		#self.fileSaveTool.Enable(False)
		bmp = wx.Image("images\\saveAs24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.fileSaveAsTool = self.toolBar.AddSimpleTool(-1, bmp, "", "Saves current file as different name")
		#self.fileSaveAsTool.Enabled(False)
		bmp = wx.Image("images\\delete24.bmp", wx.BITMAP_TYPE_BMP).ConvertToBitmap()
		self.fileDeleteTool = self.toolBar.AddSimpleTool(-1, bmp, "", "Delete current file")
		#self.fileDeleteTool.Enable(False)
		self.toolBar.AddSeparator()
		self.SetToolBar(self.toolBar)
		self.toolBar.Realize()
		
	def createDrawBar(self):
		self.drawBar = wx.ToolBar(self, -1)
	
	def createStatusBar(self):
		self.statusBar = self.CreateStatusBar()
		self.statusBar.SetBackgroundColour(wx.Color(255,255,128))
		
		# Menu handlers
	def OnFileNew(self, event):
		self.dlgButtons.Show(False)
		self.dlgNew.Show(True)
		self.curDialog = self.dlgNew
		self.panelLeft.Layout()
		
	def OnFileOpen(self, event):
		dialog = wx.FileDialog(None, "Choose a File", self.lastOpenDir,
							   "", self.wildcard, wx.OPEN | wx.MULTIPLE)
		dialog.SetFilterIndex(self.lastOpenFilterIx)
		if dialog.ShowModal() == wx.ID_OK:
			self.lastOpenDir = dialog.GetDirectory()
			self.lastOpenFilterIx = dialog.GetFilterIndex()
			paths = dialog.GetPaths()
			names = dialog.GetFilenames()
			paths.reverse()
			names.reverse()
			self.OpenFileList(paths, names)
		dialog.Destroy()
		
	def OpenFileList(self, paths, names):
		count = len(paths)
		ix = 0
		while ix < count:
			self.OpenFile(paths[ix], names[ix])
			ix += 1
	
	def OpenFile(self, path, name):
		self.curIndex += 1
		self.curViewer = Viewer(self.listBook, -1)
		self.viewersList += [self.curViewer]
		self.curFile = path
		self.filesList += [self.curFile]
		self.curViewer.Load(path)
		thumb = self.curViewer.GetThumb()
		self.curIconIdx = self.imageList.Add(thumb)
		self.iconsIdxList += [self.curIconIdx]
		self.listBook.AddPage(self.curViewer, name, True, self.curIconIdx)
		self.curModified = False
		self.modifiedList += [False]
	
	def OnFileSave(self, event):
		pass
	
	def OnFileSaveAs(self, event):
		pass
	
	def OnFileSaveCopy(self, event):
		pass
	
	def OnFileSaveAll(self, event):
		pass
	
	def OnFileClose(self, event):
		pass
	
	def OnFileCloseAll(self, event):
		pass
	
	def OnFileDelete(self, event):
		pass
	
	def OnFileRevert(self, event):
		pass
	
	def OnFilePrint(self, event):
		pass
	
	def OnFileExit(self, event):
		self.Destroy()
		
	def OnViewMag(self, event):
		if self.view10xItem.IsChecked():
			pass
		elif self.view8xItem.IsChecked():
			pass
		elif self.view6xItem.IsChecked():
			pass
		elif self.view4xItem.IsChecked():
			pass
		elif self.view3xItem.IsChecked():
			pass
		elif self.view2xItem.IsChecked():
			pass
		elif self.view1xItem.IsChecked():
			pass
		elif self.view75xItem.IsChecked():
			pass
		elif self.view50xItem.IsChecked():
			pass
		elif self.view25xItem.IsChecked():
			pass
		else:
			pass
		
	def OnEditUndo(self, event):
		pass
	
	def OnEditRedo(self, event):
		pass
	
	def OnEditCut(self, event):
		pass
	
	def OnEditCopy(self, event):
		pass
	
	def OnEditCopyAll(self, event):
		pass
	
	def OnEditCreateNew(self, event):
		pass
	
	def OnEditDuplicate(self, event):
		pass
	
	def OnEditPaste(self, event):
		pass
		
	def OnSizeDouble(self, event):
		pass
	
	def OnSizeDoubleSm(self, event):
		pass
	
	def OnSizeHalve(self, event):
		pass
	
	def OnSizeCrop(self, event):
		pass
	
	def OnSizeStrShr(self, event):
		pass
	
	def OnSizeResize(self, event):
		pass
		
	def OnPageChanging(self, event):
		pass
	
	def OnPageChanged(self, event):
		self.curIndex = event.GetSelection()
		self.curFile = self.filesList[self.curIndex]
		self.curViewer = self.viewersList[self.curIndex]
		self.curModified = self.modifiedList[self.curIndex]
		self.curIconIdx = self.iconsIdxList[self.curIndex]
	
	def OnDlgOk(self, event):
		self.dlgButtons.Show(True)
		self.curDialog.Show(False)
		self.panelLeft.Layout()
		
app = wx.PySimpleApp()
frame = HSizerFrame()
frame.Show()
app.MainLoop()
 	  	 

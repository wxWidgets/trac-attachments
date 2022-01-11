#!/usr/bin/env python

# wx bug(?): toolbar alters frame size on mac
#
# This program demonstrates what looks to me to be a bug in the Mac implementation
# of wxWidgets. It create an application with a frame and saves the size and
# location of the frame between invocations of the application.
#
# If you repeatedly start the application and close the window (on a Mac), you will
# see that the frame increases in height by 23 pixels every time. This is
# due to the presence of the ToolBar.
#
# Setting workaround = 0 will demonstrate the bug.
# Setting workaround = 1 will suppress the ToolBar() causing the problem to disappear.
# Setting workaround = 2 will set the frame's size back to its original size after the
# creation of the ToolBar resulting in a stable frame size.
# Setting workaround = 3 will hide the toolbar before saving the frame's size
# resulting in a stable frame size.
#
# Note: This program will create a directory ~/.properties that you should
# delete before changing the value of workaround and when finished testing.
workaround = 0

import os, re, string, stat
from wx import *
from wx.aui import *

def r(pattern, options=''):
	if type(pattern) == type(u''): pattern = str(pattern)
	if type(pattern) != type(''): return pattern
	flags = 0
	odict = { 'i': re.I, 'l': re.L, 'm': re.M, 's': re.S, 'x': re.X, 'u': re.U }
	for option in options:
		flags |= odict[option]
	return re.compile(pattern, flags)

def m(pattern, str, pos=0, endpos=None):
	if endpos == None: endpos = len(str)
	return r(pattern).search(str, pos, endpos)

def s(pattern, rep, str, count=0):
	return r(pattern).sub(rep, str, count)

class Property:
	def __init__(self, appname):
		self.rodata, self.rwdata, self.dirty = {}, {}, False
		self.appname = s('/', '-', appname.lower())
		self.ggpath = '/etc/properties/app'
		self.ugpath = os.getenv('HOME') + '/.properties/app'
		self.gspath = '/etc/properties/app.' + self.appname
		self.rwdir = os.getenv('HOME') + '/.properties'
		self.uspath = self.rwdir + '/app.' + self.appname
		self.load(self.rodata, self.ggpath)
		self.load(self.rodata, self.ugpath)
		self.load(self.rodata, self.gspath)
		self.load(self.rwdata, self.uspath)
	special_code, special_char, eq = 'abfnrtv', '\a\b\f\n\r\t\v', '='
	def _quote_special(self, src):
		return self._encode(src, self.special_char, self.special_code, '\\', 1)
	def _unquote_special(self, src):
		return self._decode(src, self.special_char, self.special_code, '\\', 1)
	def _quote_equals(self, src):
		return self._encode(src, self.eq, self.eq, '\\', 0)
	def _unquote_equals(self, src):
		return self._decode(src, self.eq, self.eq, '\\', 0)
	def _encode(self, src, uncoded, coded, quote_char, make_printable):
		encoded = ''
		for s in src:
			target = uncoded.find(s)
			if target != -1:
				encoded += '%c%c' % (quote_char, coded[target])
			elif make_printable and string.printable.find(s) == -1:
				encoded += '%cx%c%c' % (quote_char, string.hexdigits[ord(s)>>4], string.hexdigits[ord(s)&0x0f])
			else:
				encoded += s
		return encoded
	def _decode(self, src, uncoded, coded, quote_char, make_printable):
		start, length, decoded = 0, len(src), ''
		while start < length:
			slosh = src.find(quote_char, start)
			if slosh == -1: break
			if make_printable:
				digits, s, c = 0, slosh + 1, 0
				if src[s] in string.octdigits:
					s -= 1
					while 1:
						digits += 1; s += 1
						c <<= 3; c |= ord(src[s]) - ord('0')
						if digits == 3 or src[s+1] not in string.octdigits: break
				elif src[s] == 'x' and src[s+1] in string.hexdigits:
					while 1:
						digits += 1; c <<= 4; s += 1
						if src[s] in string.digits: c |= ord(src[s]) - ord('0')
						elif src[s] in 'abcdef': c |= ord(src[s]) - ord('a') + 10
						elif src[s] in 'ABCDEF': c |= ord(src[s]) - ord('A') + 10
						if digits == 2 or src[s+1] not in string.hexdigits: break
				if digits:
					decoded += "%*.*s%c" % (slosh-start, slosh-start, src[start:], chr(c))
					slosh = s # Skip over ASCII code
					start = slosh+1
					continue
			target = coded.find(src[slosh+1])
			if slosh == length-1 or target == -1:
				decoded += "%*.*s%c" % (slosh-start, slosh-start, src[start:], quote_char)
				start = slosh+1
				continue
			decoded += "%*.*s%c" % (slosh-start, slosh-start, src[start:], uncoded[target])
			slosh += 1 # Skip over quoted char
			start = slosh+1
		decoded += src[start:]
		return decoded
	def load(self, props, path):
		try:
			lineno = 0
			for line in open(path):
				lineno += 1
				line = s('\s+$', '', line)
				line = s('\s*#.*$', '', line)
				(key, value) = self._prop_parse(path, line, lineno)
				props[key] = value
		except IOError: pass
	def _prop_parse(self, path, line, lineno):
		prop = self._unquote_special(line)
		# Find first unquoted '='
		eq = prop.find('=')
		while eq != -1:
			if eq == 0 or prop[eq-1] != '\\': break
			eq = prop.find('=', eq+1)
		if eq == -1:
			print 'property: %s line %d: Expected "="\n%s' % (path, lineno, line)
			return
		# Identify and separate the name and value
		length = len(prop)
		value = eq+1
		while value < length and prop[value] in string.whitespace:
			value += 1
		while eq > 0 and prop[eq-1] in string.whitespace and (eq == 1 or prop[eq-2] != '\\'):
			eq -= 1
		key = prop[:eq]
		value = prop[value:]
		# Unquote any quoted trailing space in the key
		if eq > 1 and prop[eq-1] in string.whitespace and prop[eq-2] == '\\':
			key = key[:-2] + key[-1]
		# Unquote any quoted '=' in the name
		key = self._unquote_equals(key)
		# Unquote any quoted leading space in the value
		if len(value) and value[0] == '\\': value = value[1:]
		# Return this property
		return (key, value)
	def set(self, key, value):
		self.rwdata[key] = value
		self.dirty = True
	def get(self, key, default=None):
		return self.rwdata.get(key, self.rodata.get(key, default))
	def get_int(self, key, default=0):
		return int(self.get(key, '%d' % default))
	def set_int(self, key, value):
		self.set(key, '%d' % value)
	def get_double(self, key, default=0.0):
		return float(self.get(key, '%g' % default))
	def set_double(self, key, value):
		self.set(key, '%g' % value)
	def get_bool(self, key, default=False):
		value = self.get(key)
		if value == None: return default
		try: return int(value)
		except ValueError: pass
		if m('\s*([tT][rR][uU][eE]|[yY][eE][sS]|[oO][nN])\s*', value): return True
		if m('\s*([fF][aA][lL][sS][eE]|[nN][oO]|[oO][fF][fF])\s*', value): return False
		return default
	def set_bool(self, key, value):
		self.set(key, '%d' % (1 if value else 0))
	def get_rect(self, key, x, y, width, height):
		x = self.get_int(key + '.x', x)
		y = self.get_int(key + '.y', y)
		w = self.get_int(key + '.width', width)
		h = self.get_int(key + '.height', height)
		return x, y, w, h
	def set_rect(self,  key, x, y, width, height):
		self.set_int(key + '.x', x)
		self.set_int(key + '.y', y)
		self.set_int(key + '.width', width)
		self.set_int(key + '.height', height)
	def unset(self, key):
		if key in self.rodata:
			del self.rodata[key]
		if key in self.rwdata:
			del self.rwdata[key]
			self.dirty = True
	def save(self):
		if not self.dirty: return
		if not self.get_bool('save', True): return
		try: s = os.stat(self.rwdir)
		except OSError:
			try: os.mkdir(self.rwdir); s = os.stat(self.rwdir)
			except OSError: return
		if not stat.S_ISDIR(s.st_mode): return
		f = open(self.uspath, 'wb')
		def fmt(key):
			val = self.rwdata.get(key, '')
			key = self._quote_equals(key) # Quote any '=' in the key
			key = self._quote_special(key) # Quote any special chars in the key
			if len(key) and key[-1] in string.whitespace: # Quote any trailing space in the key
				key = key[:-1] + '\\' + key[-1]
			val = self._quote_special(val) # Quote any special chars in the value
			if len(val) and val[0] in string.whitespace: # Quote any leading space in the value
				val = '\\' + val
			return '%s=%s\n' % (key, val) # Return a fully quoted line of text
		f.writelines(map(fmt, sorted(self.rwdata.keys())))
		f.close()

class TestApp(App):
	def GetAppName(self):
		return 'Payroll'
	def GetAppVersion(self):
		return '0.1'
	def GetUser(self):
		try:
			return self.GetUserPosix()
		except:
			try: return self.GetUserMSWin()
			except: return 'nobody'
	def GetUserPosix(self):
		import pwd
		return pwd.getpwuid(os.getuid())[0]
	def GetUserMSWin(self):
		import win32api, win32net, win32netcon
		dc = win32net.NetServerEnum(None, 100, win32netcon.SV_TYPE_DOMAIN_CTRL)
		name = r'\\' + dc[0][0]['name']
		user = win32api.GetUserName()
		if dc[0]: return win32net.NetUserGetInfo(name, user, 1)
		return win32net.NetUserGetInfo(None, user, 1)
	def OnInit(self):
		self.env = Property(self.GetAppName())
		self.mainframe = MainFrame(self)
		self.SetTopWindow(self.mainframe)
		self.mainframe.Show()
		return True
	def OnExit(self):
		self.env.save()
	def load_window_position(self, name, width, height):
		screen = GetDisplaySize()
		x, y, w, h = self.env.get_rect(name, -1, -1, width, height)
		if x < 0 or y < 0:
			x, y = (screen.width - w) / 2, (screen.height - h) / 2
		print 'load_window_position(x=%d y=%d w=%d h=%d' % (x, y, w, h)
		return x, y, w, h
	def save_window_position(self, name, rect):
		print 'save_window_position(x=%d y=%d w=%d h=%d' % (rect.x, rect.y, rect.width, rect.height)
		self.env.set_rect('mainframe', rect.x, rect.y, rect.width, rect.height)
	def login_cancelled(self):
		self.mainframe.Close()
	def login(self, db):
		self.db = db
		self.mainframe.Show()

class MainFrame(Frame):
	def __init__(self, app):
		self.app = app
		x, y, w, h = self.app.load_window_position('mainframe', 800, 600)
		Frame.__init__(self, None, -1, app.GetAppName(), pos=(x, y), size=(w, h))
		self.Bind(EVT_CLOSE, self.OnClose)
		self.build_menus()
		if workaround != 1:
			self.build_tools()
		self.build_panel()
		self.CreateStatusBar()
		if workaround == 2:
			if self.GetSize().height != h:
				self.SetRect(Rect(x, y, w, h))
	def OnToolClick(self, event):
		tool_id = event.GetId()
		if tool_id == self.blah_tool_id:
			self.OnQuitCmd(None)
	def OnToolRightClick(self, event):
		pass
	def OnQuitCmd(self, event):
		self.Close()
	def OnClose(self, event):
		if workaround == 3:
			self.SetToolBar(None)
		self.app.save_window_position('mainframe', self.GetRect())
		event.Skip()
	def build_menus(self):
		self.file_menu = Menu()
		self.exit_menu_item = self.file_menu.Append(-1, 'E&xit')
		self.menu_bar = MenuBar()
		self.menu_bar.Append(self.file_menu, '&File')
		self.Bind(EVT_MENU, self.OnQuitCmd, self.exit_menu_item)
		self.SetMenuBar(self.menu_bar)
	def build_tools(self):
		self.tool_bar = self.CreateToolBar()
		tsize = (16, 16)
		self.blah_tool_bmp = ArtProvider.GetBitmap(ART_NEW, ART_TOOLBAR, tsize)
		self.tool_bar.SetToolBitmapSize(tsize)
		self.blah_tool_id = NewId()
		self.tool_bar.AddLabelTool(self.blah_tool_id, 'Blah', self.blah_tool_bmp, shortHelp='Blah', longHelp='Long help for blah')
		self.Bind(EVT_TOOL, self.OnToolClick, id=self.blah_tool_id)
		self.Bind(EVT_TOOL_RCLICKED, self.OnToolRightClick, id=self.blah_tool_id)
		self.tool_bar.Realize()
	def build_panel(self):
		self.splitter = SplitterWindow(self, style=SP_LIVE_UPDATE)
		p1 = Panel(self.splitter, style=BORDER_SUNKEN)
		sz = BoxSizer(VERTICAL)
		sz.Add(self.create_tree(p1), 1, EXPAND, 3)
		sz.Add(self.create_info(p1), 1, EXPAND, 3)
		p1.SetSizer(sz)
		p2 = Panel(self.splitter, style=BORDER_SUNKEN)
		sz = BoxSizer(VERTICAL)
		sz.Add(self.create_book(p2), 1, EXPAND, 3)
		p2.SetSizer(sz)
		self.splitter.SplitVertically(p1, p2, 300)
	def create_tree(self, panel):
		self.tree = TreeCtrl(panel)
		self.root = self.tree.AddRoot('Blah')
		self.tree.AppendItem(self.root, 'Blah1')
		self.tree.AppendItem(self.root, 'Blah2')
		return self.tree
	def create_info(self, panel):
		self.info = Panel(panel)
		return self.info
	def create_book(self, panel):
		self.book = AuiNotebook(panel)
		return self.book

def main(redirect=False):
	TestApp(redirect=redirect).MainLoop()

if __name__ == '__main__':
	main()


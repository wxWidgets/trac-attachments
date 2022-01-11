#! /bin/bash

# Test building of wxWidgets in three configurations...

here=`cygpath -a .`
rm -rf RAWCYGWIN CYGWINMSW MINGWMSW
mkdir RAWCYGWIN
mkdir CYGWINMSW
mkdir MINGWMSW

cd RAWCYGWIN
echo Build using cygwin for use via X11/gtk
${here}/configure --without-msw --with-gtk --disable-shared
make -j4
cd samples
make -j4
cd ../demos
make -j4
cd $here

cd CYGWINMSW
echo Build using cygwin, linking with cygwin.dll, but using MSW for the GUI
${here}/configure --disable-shared LDFLAGS='-L/usr/lib/w32api -static'
make -j4
cd samples
make -j4
cd ../demos
make -j4
cd $here

cd MINGWMSW
echo Build under cygwin but using i686-w42-mingw32 tools for native Windows
${here}/configure --disable-shared LDFLAGS='-static' --host=i686-w64-mingw32
make -j4
cd samples
make -j4
cd ../demos
make -j4
cd $here

echo All versions built.


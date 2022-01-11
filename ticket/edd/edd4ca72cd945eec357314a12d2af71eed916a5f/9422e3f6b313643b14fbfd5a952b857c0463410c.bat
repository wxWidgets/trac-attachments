@echo off
echo Make sure to set wxUSE_GLCANVAS to 1 in include\wx\msw\setup0.h
pause
set path=C:\Borland\BCC55\Bin;%path%
mkdir lib\bcc_dll\mswd\wx
copy include\wx\msw\setup0.h lib\bcc_dll\mswd\wx\setup.h
cd build\msw
make -B -DSHARED=1 -DUSE_OPENGL=1 -DVENDOR=myname -f makefile.bcc
cd ..\..\samples\opengl\cube
make -B -DSHARED=1 -DUSE_OPENGL=1 -DVENDOR=myname -f makefile.bcc
copy bcc_mswddll\cube.exe ..\..\..\lib\bcc_dll
cd ..\..\..\lib\bcc_dll
copy C:\Borland\BCC55\Bin\cc3250mt.dll .
cube.exe

 	  	 

rem automatically go to particular toolset based in where compiler is by defaults.
if exist "c:\MinGW\bin\g++.exe" set TOOLSET=mingw
if exist "C:\Program Files\mingw-w64\i686-6.2.0-win32-dwarf-rt_v5-rev1\mingw32\bin\g++.exe" set TOOLSET=mingw64
if exist "C:\Program Files\mingw-w64\x86_64-6.2.0-win32-dwarf-rt_v5-rev1\mingw32\bin\g++.exe" set TOOLSET=mingw64
rem VC++? I don't remember exactly where the cl.exe file is for 32-bit or 64-bit.
rem with VC++ if it's ok with them, could auto-detect the dir the compiler is in.
rem cygwin?

goto %TOOLSET%

:msbuild
if .%BUILD%.==.. @goto errvcbuild
if .%VS%.==.. @goto errvcvs
if .%ARCH%.==.. @goto errvcarch
if .%PROCESSOR_ARCHITECTURE%.==.x86. (
	rem if you don't escape the perens in the string, it will get executed.
	if exist call "C:\Program Files ^(x86^)\Microsoft Visual Studio %VS%\VC\bin\cl.exe" set TOOLSET=nmake
	if not .%_pth%.==.1. set PATH=C:\Program Files ^(x86^)\Microsoft Visual Studio %VS%\VC\bin;%PATH%
) else (
	if exist call "%PROGRAMFILES%\Microsoft Visual Studio %VS%\VC\bin\cl.exe" set TOOLSET=nmake
	if not .%_pth%.==.1. set PATH=C:\Program Files\Microsoft Visual Studio %VS%\VC\bin;%PATH%
)
rem cd build\msw
cd ..\msw
msbuild /m:2 /v:n /p:Platform=%ARCH% /p:Configuration="%CONFIGURATION%" wx_vc12.sln
goto :end

:nmake
if .%BUILD%.==.. @goto errvcbuild
if .%VS%.==.. @goto errvcvs
if .%ARCH%.==.. @goto errvcarch
if .%PROCESSOR_ARCHITECTURE%.==.x86. (
	rem if you don't escape the perens in the string, it will get executed.
	if exist call "C:\Program Files ^(x86^)\Microsoft Visual Studio %VS%\VC\bin\cl.exe" set TOOLSET=nmake
	if not .%_pth%.==.1. set PATH=C:\Program Files ^(x86^)\Microsoft Visual Studio %VS%\VC\bin;%PATH%
) else (
	if exist call "%PROGRAMFILES%\Microsoft Visual Studio %VS%\VC\bin\cl.exe" set TOOLSET=nmake
	if not .%_pth%.==.1. set PATH=C:\Program Files\Microsoft Visual Studio %VS%\VC\bin;%PATH%
)
rem cd build\msw
cd ..\msw
rem vcvars32 and vcvarsall sets path as well as LIB, INCLUDE
rem note that ARCH is not set by default. 
rem PROCESSOR_ARCHITECTURE is the host architecture. 
rem so I can only assume that ARCH is the target?
call "C:\Program Files (x86)\Microsoft Visual Studio %VS%\VC\vcvarsall.bat" %ARCH%
nmake -f makefile.vc BUILD=%BUILD% clean
nmake -f makefile.vc BUILD=%BUILD%
goto :end

:mingw64
cd ..\msw
rem cd build\msw
if @%PROCESSOR_ARCHITECTURE%@==@x86@ (
if not .%_pth%.==.1. set PATH=C:\Program Files\mingw-w64\i686-6.2.0-win32-dwarf-rt_v5-rev1\mingw32\bin;%PATH%
) else (
if not .%_pth%.==.1. set PATH=C:\Program Files\mingw-w64\x86_64-6.2.0-win32-dwarf-rt_v5-rev1\mingw32\bin;%PATH%
)
echo --- Tools versions:
rem toolset does not have standard *nix tools like head, automake, autoconf.
g++ --version
mingw32-make --version
ar --version
echo.
echo --- Starting the build
echo.
rem clean out the .o and .exe and .dll and other built stuff from the build first
mingw32-make -fmakefile.gcc clean
rem make the installer
mingw32-make -fmakefile.gcc setup_h
rem make the .o files or .lib files
mingw32-make -fmakefile.gcc SHARED=0
goto :end

:mingw
cd ..\msw
rem cd build\msw
rem appveyor.bat is no longer in the build dir, it is in build\tools
if not %_pth%==1 set PATH=C:\MinGW\bin;%PATH%
echo --- Tools versions:
g++ --version | head -1
mingw32-make --version | head -1
ar --version | head -1
echo.
echo --- Starting the build
echo.
mingw32-make -fmakefile.gcc clean
mingw32-make -fmakefile.gcc setup_h
mingw32-make -fmakefile.gcc
goto :end

:msys2
rem I would like to know where this msys64 binary comes from.
if not .%_pth%.==.1. set PATH=C:\msys64\%MSYSTEM%\bin;C:\msys64\usr\bin;%PATH%
set CHERE_INVOKING=yes
:: Workaround for "configure: Bad file descriptor"
perl -i".bak" -pe "s/^test -n \".DJDIR\"/#$&/" configure
bash -lc "g++ --version"
bash -lc "CXXFLAGS=-Wno-deprecated-declarations ./configure --disable-optimise --disable-xrc && make clean"
bash -lc "CXXFLAGS=-Wno-deprecated-declarations ./configure --disable-optimise --disable-xrc && make setup_h"
bash -lc "CXXFLAGS=-Wno-deprecated-declarations ./configure --disable-optimise --disable-xrc && make"
goto :end

:cygwin
C:\cygwin\setup-x86.exe -qnNdO -R C:/cygwin -s http://cygwin.mirror.constant.com -l C:/cygwin/var/cache/setup -P libjpeg-devel -P libpng-devel -P libtiff-devel -P libexpat-devel
if not .%_pth%.==.1. set PATH=c:\cygwin\bin;%PATH%
set CHERE_INVOKING=yes
:: Workaround for "configure: Bad file descriptor"
perl -i".bak" -pe "s/^test -n \".DJDIR\"/#$&/" configure
bash -lc "g++ --version"
bash -lc "LDFLAGS=-L/usr/lib/w32api ./configure --disable-optimise --disable-shared --disable-aui --disable-html --disable-ribbon --disable-richtext --disable-stc && make clean"

rem not allowed to statically link in cygwin1.dll?
rem bash -lc "LDFLAGS=-L/usr/lib/w32api ./configure --disable-optimise --disable-shared --disable-aui --disable-html --disable-ribbon --disable-richtext --disable-stc && make setup_h"

rem I assume that makefile.gcc is used for this too, so I added -fmakefile.gcc
bash -lc "LDFLAGS=-L/usr/lib/w32api ./configure --disable-optimise --disable-shared --disable-aui --disable-html --disable-ribbon --disable-richtext --disable-stc && make"
goto :end





:errvcbuild
@echo ERROR: appveyor.bat needs BUILD set before running batch file.
@goto end

:errvcarch
@echo ERROR: appveyor.bat needs ARCH set before running batch file.
@goto end

:errvcvs
@echo ERROR: appveyor.bat needs VS set to VC++'s year before running batch file. suggest editing appveyor.bat and putting it in or making a wrapper batch file if you do this often?
@goto end

:end
rem flag to indicate I set the PATH once
set _pth=1

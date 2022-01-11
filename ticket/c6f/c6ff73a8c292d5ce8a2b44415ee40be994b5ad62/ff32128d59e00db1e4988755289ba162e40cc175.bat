if "%1" == "" goto ERR_NOPARM
if "%2" == "" goto ERR_NOPARM
if "%3" == "" goto ERR_NOPARM

rem Uncomment the next line to set the version; used also in wxWidgets.iss
SET WXW_VER=%1.%2.%3

echo docs building for %WXW_VER%

rem  This builds the docs in %WXWIN% in a number of formats 
rem  and a clean inno setup in a second tree
rem  it uses a number of tools, gnuwin32 zip & dos2unix, 
rem  writes a log file in c:\

set WXWIN=c:\wxWidgets-%1.%2.%3
set DAILY=c:\daily
set INNO=c:\wxWidgets-%1.%2.%3


path=%path%;"C:\Program Files\7-Zip";C:\Program Files (x86)\Inno Setup 5

rem update wxwidgets (holds docs) and inno (wxMSW setup.exe only)
c:
cd %WXWIN%

dos2unix configure
dos2unix config.guess
dos2unix config.sub

if exist include\wx\msw\setup.h del include\wx\msw\setup.h
if exist include\wx\univ\setup.h del include\wx\univ\setup.h

copy include\wx\msw\setup0.h include\wx\msw\setup.h
copy include\wx\univ\setup0.h include\wx\univ\setup.h

rem make   chm
rem Now create standalone copies of docs (chm and htb)
cd %WXWIN%\docs\doxygen

rmdir /S /Q %WXWIN%\docs\doxygen\out

call regen chm

cd %WXWIN%\docs\doxygen\out

7z a -t7z wxWidgets-%WXW_VER%-docs-chm.zip wx.chm
copy wxWidgets-%WXW_VER%-docs-chm.zip %DAILY%

mkdir %WXWIN%\docs\htmlhelp
copy %WXWIN%\docs\doxygen\out\wx.chm %WXWIN%\docs\htmlhelp\wx.chm

cd ..
rmdir /S /Q %WXWIN%\docs\doxygen\out

cd %WXWIN%\build\tools

iscc wxwidgets.iss

echo docs built for %WXW_VER%


goto End

:ERR_NOPARM
   @echo.
   @echo ERROR: NO PARAMETER SUPPLIED
   @echo MajorVers MinorVers BuildVers

:End


cd %WXWIN%\build\msw

@echo off
rem Batch to build a subset of the Open Watcom tools

if "%OWBOOTSTRAP%" == "" goto cont1
set WATCOM=%OWBOOTSTRAP%
set PATH=%OWBOOTSTRAP%\binnt;%OWBOOTSTRAP%\binw;%PATH%
set INCLUDE=%OWBOOTSTRAP%\h;%OWBOOTSTRAP%\h\nt
:cont1
cd %OWROOT%\src\make
if not exist %OWOBJDIR% mkdir %OWOBJDIR%
cd %OWOBJDIR%
if "%OWBOOTSTRAP%" == "" goto nowatcom
wmake -h -f ..\wmake
goto cont2
:nowatcom
nmake -nologo -f ..\nmkmake
:cont2
cd %OWROOT%\src\builder
if not exist %OWOBJDIR% mkdir %OWOBJDIR%
cd %OWOBJDIR%
%OWBINDIR%\wmake -h -f ..\bootmake builder.exe rm.exe
cd %OWROOT%\src
builder boot
if errorlevel == 1 goto cont4
if "%OWBOOTSTRAP%" == "" goto cont3
set PATH=%OWBINDIR%;%OWROOT%\build;%OWDEFPATH%
set INCLUDE=%OWDEFINCLUDE%
set WATCOM=%OWDEFWATCOM%
:cont3
builder build
goto finish
:cont4
if "%OWBOOTSTRAP%" == "" goto finish
set PATH=%OWBINDIR%;%OWROOT%\build;%OWDEFPATH%
set INCLUDE=%OWDEFINCLUDE%
set WATCOM=%OWDEFWATCOM%
:finish
cd %OWROOT%

@echo off
rem Batch to build a subset of the Open Watcom tools

rem Set up environment variables needed by Open Watcom (if provided)
if "%OWBOOTSTRAP%" == "" goto cont1
set WATCOM=%OWBOOTSTRAP%
set PATH=%OWBOOTSTRAP_PATH%
set INCLUDE=%OWBOOTSTRAP_INCLUDE%
:cont1

rem Build wmake
cd %OWROOT%\src\make
if not exist %OWOBJDIR% mkdir %OWOBJDIR%
cd %OWOBJDIR%
nmake -nologo -f ..\nmkmake

rem Build the builder utility and rm
cd %OWROOT%\src\builder
if not exist %OWOBJDIR% mkdir %OWOBJDIR%
cd %OWOBJDIR%
%OWBINDIR%\wmake -h -f ..\bootmake builder.exe rm.exe
cd %OWROOT%\src

rem With wmake and builder at hand, run the bootstrap build
builder boot
if errorlevel == 1 goto restore_vars

rem Modify the environment to point at freshly built tools
if "%OWBOOTSTRAP%" == "" goto cont3
rem set PATH=%OWBINDIR%;%OWROOT%\build;%OWDEFPATH%
rem set INCLUDE=%OWDEFINCLUDE%
rem set WATCOM=%OWDEFWATCOM%
:cont3

rem Do a regular build using fresh tools
builder build
goto finish

rem Restore original values of environment variables
:restore_vars
if "%OWBOOTSTRAP%" == "" goto finish
set PATH=%OWBINDIR%;%OWROOT%\build;%OWDEFPATH%
set INCLUDE=%OWDEFINCLUDE%
set WATCOM=%OWDEFWATCOM%

:finish
cd %OWROOT%

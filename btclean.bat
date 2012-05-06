@echo off
rem Batch to clean a bootstrap build of Open Watcom tools.

if exist %OWBINDIR%\builder.exe goto builder
echo Cannot find builder - did you run boot.bat?
goto end

:builder
cd %OWROOT%\src
builder bootclean
cd %OWROOT%
:end
cd %OWROOT%\src\make
if not exist %OWOBJDIR% goto cont1
del /q %OWOBJDIR%\*
rmdir %OWOBJDIR%
:cont1
cd %OWROOT%\src\builder
if not exist %OWOBJDIR% goto cont2
del /q %OWOBJDIR%\*
rmdir %OWOBJDIR%
:cont2
cd %OWROOT%
if exist %OWBINDIR%\wmake.exe del %OWBINDIR%\wmake.exe
if exist %OWBINDIR%\builder.exe del %OWBINDIR%\builder.exe
if exist %OWBINDIR%\rm.exe del %OWBINDIR%\rm.exe

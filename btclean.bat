@echo off
rem Batch to clean a bootstrap build of Open Watcom tools.

if exist %OWBINDIR%\builder.exe goto builder
echo Cannot find builder - did you run boot.bat?
goto end

:builder
cd src
builder bootclean
del /q make\%OBJDIR%\*
rmdir make\%OBJDIR%
del %OWBINDIR%\wmake.exe
del %OWBINDIR%\builder.exe
del %OWBINDIR%\rm.exe
cd ..
:end

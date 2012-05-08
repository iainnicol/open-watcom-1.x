@echo off
rem Batch to clean a bootstrap build of Open Watcom tools.

if exist %OWBINDIR%\builder.exe goto have_builder
echo Cannot find builder - did you run boot.bat?
goto no_builder

rem Use builder to clean out most of the bits, then delete builder.
:have_builder
cd %OWROOT%\src
builder bootclean
cd %OWROOT%

rem At this point there is no builder; kill off the stragglers.
rem First clean out wmake
:no_builder
cd %OWROOT%\src\make
if not exist %OWOBJDIR% goto no_wmake
del /q %OWOBJDIR%\*
rmdir %OWOBJDIR%
:no_wmake

rem Next delete builder object files
rem TODO: Has that not been done already?
cd %OWROOT%\src\builder
if not exist %OWOBJDIR% goto no_bldobj
del /q %OWOBJDIR%\*
rmdir %OWOBJDIR%
:no_bldobj

rem Finally delete remaining executables in build bin directory.
rem TODO: review whether all the POSIX utilities need to be built.
cd %OWROOT%
if exist %OWBINDIR%\wmake.exe del %OWBINDIR%\wmake.exe
if exist %OWBINDIR%\builder.exe del %OWBINDIR%\builder.exe
if exist %OWBINDIR%\rm.exe del %OWBINDIR%\rm.exe
if exist %OWBINDIR%\cat.exe del %OWBINDIR%\cat.exe
if exist %OWBINDIR%\chmod.exe del %OWBINDIR%\chmod.exe
if exist %OWBINDIR%\cp.exe del %OWBINDIR%\cp.exe
if exist %OWBINDIR%\egrep.exe del %OWBINDIR%\egrep.exe
if exist %OWBINDIR%\ls.exe del %OWBINDIR%\ls.exe
if exist %OWBINDIR%\mkdir.exe del %OWBINDIR%\mkdir.exe
if exist %OWBINDIR%\sed.exe del %OWBINDIR%\sed.exe
if exist %OWBINDIR%\uniq.exe del %OWBINDIR%\uniq.exe
if exist %OWBINDIR%\wc.exe del %OWBINDIR%\wc.exe
if exist %OWBINDIR%\which.exe del %OWBINDIR%\which.exe

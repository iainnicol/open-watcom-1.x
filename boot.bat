@echo off
rem Batch to build a subset of the Open Watcom tools
rem using the host platform's native C/C++ compiler tools.

cd src\make
if not exist %OBJDIR% mkdir %OBJDIR%
cd %OBJDIR%
nmake -nologo -f ..\nmkmake
cd ..\..\builder
if not exist %OBJDIR% mkdir %OBJDIR%
cd %OBJDIR%
wmake -h -f ..\bootmake builder.exe rm.exe
cd ..\..
builder boot
rem builder build
cd ..

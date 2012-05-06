@echo off
REM *****************************************************************
REM CMNVARS.BAT - common environment variables
REM *****************************************************************
REM NOTE: All batch files to set the environment must call this batch
REM       file at the end.

REM Set the version numbers
set BLD_VER=20
set BLD_VER_STR=2.0

REM Set up default path information variables
if not "%OWDEFPATH%" == "" goto cont1
set OWDEFPATH=%PATH%;
set OWDEFINCLUDE=%INCLUDE%
set OWDEFWATCOM=%WATCOM%
:cont1

REM Subdirectory to be used for bootstrapping
set OWOBJDIR=bootstrp

REM Subdirectory to be used for bootstrapping binaries
set OWBINDIR=%OWROOT%\build\bin

REM Set environment variables
set PATH=%OWBINDIR%;%OWROOT%\build;%OWDEFPATH%
set INCLUDE=%OWDEFINCLUDE%
set WATCOM=%OWDEFWATCOM%

echo Open Watcom build environment

REM OS specifics

REM setup right COMSPEC for non-standard COMSPEC setting on NT based systems
if '%OS%' == 'Windows_NT' set COMSPEC=%windir%\system32\cmd.exe

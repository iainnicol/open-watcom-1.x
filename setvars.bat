@echo off
REM *****************************************************************
REM SETVARS.BAT - Windows NT version
REM *****************************************************************
REM NOTE: Do not use this batch file directly, but copy it and
REM       modify it as necessary for your own use!!

REM Change this to point to your Open Watcom source tree
REM Must be an 8.3 name!
set OWROOT=d:\openwa~1

REM Change this to point to your existing Open Watcom installation
set WATCOM=c:\c\ow10

REM Set this variable to 1 to get debug build
set DEBUG_BUILD=0

REM Set this variable to 1 to get default windowing support in clib
set DEFAULT_WINDOWING=0

REM Set this variable to 0 to suppress documentation build
set DOC_BUILD=1

REM Setup environment variables for Perforce
set P4PORT=perforce.scitechsoft.com:3488
set P4USER=YourName
set P4CLIENT=YOURCLIENT
set P4PASSWD=YourPassword

REM Documentation related variables
REM set appropriate variables to blank for help compilers which you haven't installed
set WIN95HC=hcrtf
set WIN31HC=hc31
set OS2HC=ipfc

REM Set up default path information variable
if %DEFPATH%. == . set DEFPATH=%PATH%

REM Subdirectory to be used for bootstrapping
set OBJDIR=prebuild

REM Stuff for the Open Watcom build environment
set BUILD_PLATFORM=nt386
set BATDIR=%OWROOT%
set BLD_VER=14
set BLD_VER_STR=1.4
set BUILDER_CTL=lang.ctl
set DEFREL=rel2
set DEVDIR=%OWROOT%\bld
set DISTROOT=%OWROOT%\distrib
set RELROOT=%OWROOT%
set DWATCOM=%WATCOM%
set DOC_ROOT=%OWROOT%\docs
set LANG=%WATCOM%
set INCLUDE=%LANG%\h;%LANG%\h\win;%DEVDIR%\watcom\h
set LANG_BLD=%OWROOT%\bat
set LIB=%OWROOT%\bld\watcom\lib

echo Open Watcom compiler build environment

REM split up path for easy checking.
PATH %OWROOT%\bin
PATH %PATH%;%DEVDIR%\build\binnt
PATH %PATH%;%OWROOT%\bat
PATH %PATH%;%LANG%\binnt
PATH %PATH%;%LANG%\binw
PATH %PATH%;%LANG%\binp
PATH %PATH%;%DOC_ROOT%\cmds
PATH %PATH%;%DEFPATH%

set EDPATH=%LANG%\eddat
set WWINHELP=%OWROOT%\bld\online\hlp\ib

set DOS4G=quiet

%DEVDR%
cd %DEVDIR%

REM Change this to the install location of GhostScript for PDF creation (optional)
REM (optional)
set GHOSTSCRIPT=C:\gs\gs7.04

REM setup right COMSPEC for non-standard COMSPEC setting on NT based systems
if '%OS%' == 'Windows_NT' set COMSPEC=%windir%\system32\cmd.exe

set COPYCMD=/y

@echo off
REM *****************************************************************
REM SETVARS.BAT - Windows NT version
REM *****************************************************************
REM NOTE: Do not use this batch file directly, but copy it and
REM       modify it as necessary for your own use!!

REM Setup environment variables for Perforce
set P4PORT=perforce.openwatcom.org:3488
set P4USER=YourName
set P4CLIENT=YOURCLIENT
set P4PASSWD=YourPassword

REM Change this to point to your Open Watcom source tree - must be an 8.3 name!
set OWROOT=d:\ow

REM Change this to point to your existing Open Watcom installation 
REM if you bootstrap by host native tools then comment it out
set OWBOOTSTRAP=c:\ow1x

REM Change this to the PATH required by GhostScript for PDF creation on used host OS (optional)
set OWGHOSTSCRIPTPATH=c:\gs\gs7.04\bin;c:\gs\gs7.04\lib

REM Set this variable to 1 to get debug build
set OW_DEBUG_BUILD=0

REM Set this variable to 1 to get default windowing support in clib
set OW_DEFAULT_WINDOWING=0

REM Set this variable to 0 to suppress documentation build
set OW_DOC_BUILD=1

REM Documentation related variables
REM set appropriate variables to point Windows help compilers which you have installed
rem set OW_WIN95HC=hcrtf
rem set OW_HHC=hhc

REM Invoke the batch file for the common environment
call %OWROOT%\cmnvars.bat

REM Adjust to match the host platform
set BOOTSTRAP_OS=nt
set BOOTSTRAP_CPU=386
set OWBOOTSTRAP_PATH=%OWBOOTSTRAP%\binnt;%OWBOOTSTRAP%\binw;%PATH%
set OWBOOTSTRAP_INCLUDE=%OWBOOTSTRAP%\h;%OWBOOTSTRAP%\h\nt

cd %OWROOT%

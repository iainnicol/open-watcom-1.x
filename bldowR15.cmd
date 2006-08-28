@echo off
REM *****************************************************************
REM bldOWr15.CMD - build  Open Watcom from existing OW 1.5 release

REM will build the builder, wattcp, watcom and installer

REM combined        OS/2   and   NT / XP Version
REM
REM Call without parms for "builder rel2" operation -> bldowR15
REM Call with clean for "builder clean"  operation  -> bldowR15 clean
REM --> requires a customized setvars.bat/cmd named myowR15.cmd
REM --> set watcom to the existing OW 1.5 installation
REM *****************************************************************
setlocal
set myow=myowR15

if exist %myow%.cmd goto cont1
   echo Customized setvars.cmd not found, cannot continue
   echo must be in the same dir as bldowR15.cmd
   echo copy setvars.cmd/bat to %myow%.cmd and customize
   pause
   goto eof

:CONT1
   call %myow%.cmd
   set target=%1
   if [%target%] == [] set target=rel2
rem the makefiles dont know a target rel2, so only pass target if clean
   set makeclean=
   if [%target%] == [clean]  set makeclean=clean

rem NT/XP? or OS/2?
   If [%OS2_SHELL%] == [] goto noOS2
   If [%OS%] == [] goto noWIN
   echo Operating System not recognized, sorry
   goto eof

:NOOS2
rem only works if system is on c:
   if [%Systemroot%] == [C:\WINNT] goto noXP
   set builderdir=nt386
   goto bld1

:NOXP
   set builderdir=nt386
   goto bld1

:NOWIN
   set builderdir=os2386

:BLD1
rem start with making the builder
   cd builder\%builderdir%
   wmake %makeclean%

REM wattcp is needed for debugger helperprogram tcpserv
   cd %devdir%
   cd ..\contrib\wattcp\src
   wmake %makeclean% -ms

REM now we can start the builder with 9 generations of logfiles
   cd %devdir%
   builder %target% -b 9

REM build the installer, REM next 3 lines if not wanted
   cd %devdir%
   cd setupgui
   builder %target% -b 9

:EOF
   endlocal


#pmake: build os_linux cpu_386 386 intel
#
# Open Watcom Debugger makefile for Linux
#

host_OS  = linux
host_CPU = 386

syshdir =

>>>> ORIGINAL makefile#1
sysobjs = linuxcmd.obj linuxio.obj lnxinit.obj lnxscrn.obj lnxlkup.obj lnxchk.obj peloader.obj
==== THEIRS makefile#9
sysobjs = &
    linuxcmd.obj &
    linuxio.obj &
    lnxinit.obj &
    lnxscrn.obj &
    lnxlkup.obj &
    lnxchk.obj
==== YOURS makefile
sysobjs = linuxcmd.obj &
          linuxio.obj &
          lnxinit.obj &
          lnxscrn.obj &
          lnxlkup.obj &
          lnxchk.obj &
          peloader.obj
<<<<

!include ../../master.mif

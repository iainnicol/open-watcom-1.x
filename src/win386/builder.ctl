# Win386 Builder Control file
# ===========================

set PROJDIR=<CWD>
set PROJNAME=win386

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK . . ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> ext/win386.ext              <RELROOT>/binw/win386.ext
    <CCCMD> dll/w386dll.ext             <RELROOT>/binw/w386dll.ext
    <CCCMD> conv/win386/win386.lib      <RELROOT>/lib386/win/win386.lib
    <CCCMD> vxd/wdebug.386              <RELROOT>/binw/wdebug.386
    <CCCMD> vxd/wemu387.386             <RELROOT>/binw/wemu387.386
    <CCCMD> wbind/dosi86/wbind.exe      <RELROOT>/binw/wbind.exe
    <CCCMD> wbind/os2i86/wbind.exe      <RELROOT>/binp/wbind.exe
    <CCCMD> wbind/nt386/wbind.exe       <RELROOT>/binnt/wbind.exe
    <CCCMD> wbind/linux386/wbind.exe    <RELROOT>/binl/wbind

[ BLOCK <1> clean ]
#==================
    @rm -f asm/dllthk.asm c/dllthunk.c asm/winglue.asm h/winglue.inc
    @rm -f ext/win386.ext dll/w386dll.ext
    @rm -f vxd/wdebug.386 vxd/wemu387.386

[ BLOCK . . ]
#============
cdsay <PROJDIR>

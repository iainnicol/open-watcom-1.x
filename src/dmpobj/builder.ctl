# dmpobj Builder Control file
# ===========================

set PROJDIR=<CWD>
set PROJNAME=dmpobj

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/deftool.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/dosi86/dmpobj.exe    <RELROOT>/binw/dmpobj.exe
    <CCCMD> <PROJDIR>/os2386/dmpobj.exe    <RELROOT>/binp/dmpobj.exe
    <CCCMD> <PROJDIR>/nt386/dmpobj.exe     <RELROOT>/binnt/dmpobj.exe
    <CCCMD> <PROJDIR>/linux386/dmpobj.exe  <RELROOT>/binl/dmpobj
    <CCCMD> <PROJDIR>/ntaxp/dmpobj.exe     <RELROOT>/axpnt/dmpobj.exe

[ BLOCK . . ]
#============
cdsay <PROJDIR>

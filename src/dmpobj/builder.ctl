# dmpobj Builder Control file
# ===========================

set PROJDIR=<CWD>
set PROJNAME=dmpobj

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/deftool.ctl ]

[ BLOCK <1> rel2 cprel2 ]
#========================
    <CCCMD> dosi86/dmpobj.exe    <RELROOT>/binw/dmpobj.exe
    <CCCMD> os2386/dmpobj.exe    <RELROOT>/binp/dmpobj.exe
    <CCCMD> nt386/dmpobj.exe     <RELROOT>/binnt/dmpobj.exe
    <CCCMD> ntaxp/dmpobj.exe     <RELROOT>/axpnt/dmpobj.exe
    <CCCMD> qnx386/dmpobj.exe    <RELROOT>/qnx/dmpobj
    <CCCMD> linux386/dmpobj.exe  <RELROOT>/binl/dmpobj

[ BLOCK . . ]
#============
cdsay <PROJDIR>

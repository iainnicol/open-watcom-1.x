# wdump Builder Control file
# ==========================

set PROJDIR=<CWD>
set PROJNAME=wdump

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/deftool.ctl ]

[ BLOCK <1> rel2 cprel2 ]
#========================
    <CCCMD> dosi86/wdump.exe    <RELROOT>/binw/wdump.exe
    <CCCMD> os2386/wdump.exe    <RELROOT>/binp/wdump.exe
    <CCCMD> nt386/wdump.exe     <RELROOT>/binnt/wdump.exe
    <CCCMD> ntaxp/wdump.exe     <RELROOT>/axpnt/wdump.exe
    <CCCMD> qnx386/wdump.exe    <RELROOT>/qnx/wdump
    <CCCMD> linux386/wdump.exe  <RELROOT>/binl/wdump

[ BLOCK . . ]
#============

cdsay <PROJDIR>

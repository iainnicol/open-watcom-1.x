# whelp Builder Control file
# ===========================

set PROJDIR=<CWD>
set PROJNAME=whelp

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/deftool.ctl ]

[ BLOCK <1> rel2 cprel2 ]
#========================
    <CCCMD> dos386/whelp.exe    <RELROOT>/binw/whelp.exe
    <CCCMD> os2386/whelp.exe    <RELROOT>/binp/whelp.exe
    <CCCMD> linux386/whelp.exe  <RELROOT>/binl/whelp

[ BLOCK . . ]
#============
cdsay <PROJDIR>

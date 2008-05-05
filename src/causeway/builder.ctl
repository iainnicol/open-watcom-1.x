# CauseWay Builder Control file
# =============================

set PROJDIR=<CWD>
set PROJNAME=CauseWay

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/cw32/dosi86/cw32.exe <RELROOT>/binw/cwstub.exe

[ BLOCK . . ]
#============
cdsay <PROJDIR>

# HEAPWALKER Builder Control file
# ============================

set PROJDIR=<CWD>
set PROJNAME=heapwalk

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/wini86/wheapwlk.exe <RELROOT>/binw/wheapwlk.exe

[ BLOCK . . ]
#============
cdsay <PROJDIR>

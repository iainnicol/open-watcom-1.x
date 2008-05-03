# ZOOM Builder Control file
# ============================

set PROJDIR=<CWD>
set PROJNAME=zoom

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/wini86/wzoom.exe <RELROOT>/binw/wzoom.exe
    <CCCMD> <PROJDIR>/nt386/wzoom.exe  <RELROOT>/binnt/wzoom.exe
    <CCCMD> <PROJDIR>/ntaxp/wzoom.exe  <RELROOT>/axpnt/wzoom.exe

[ BLOCK . . ]
#============
cdsay <PROJDIR>

# WDE Builder Control file
# ========================

set PROJDIR=<CWD>
set PROJNAME=wde

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/wini86/wde.exe      <RELROOT>/binw/wde.exe
    <CCCMD> <PROJDIR>/nt386/wde.exe       <RELROOT>/binnt/wde.exe
    <CCCMD> <PROJDIR>/ntaxp/wde.exe       <RELROOT>/axpnt/wde.exe

[ BLOCK . . ]
#============
cdsay <PROJDIR>

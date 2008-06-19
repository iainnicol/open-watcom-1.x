# WRE Builder Control file
# ========================

set PROJDIR=<CWD>
set PROJNAME=wre

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/wini86/wre.exe         <RELROOT>/binw/wre.exe
    <CCCMD> <PROJDIR>/nt386/wre.exe          <RELROOT>/binnt/wre.exe
    <CCCMD> <PROJDIR>/ntaxp/wre.exe          <RELROOT>/axpnt/wre.exe

[ BLOCK . . ]
#============
cdsay <PROJDIR>

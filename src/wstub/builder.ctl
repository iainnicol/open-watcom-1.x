# wstub Builder Control file
# ==========================

set PROJDIR=<CWD>
set PROJNAME=wstub

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> wstub.exe   <RELROOT>/binw/wstub.exe
    <CCCMD> wstubq.exe  <RELROOT>/binw/wstubq.exe
    <CCCMD> wstub.asm   <RELROOT>/src/wstub.asm

[ BLOCK . . ]
#============
cdsay <PROJDIR>

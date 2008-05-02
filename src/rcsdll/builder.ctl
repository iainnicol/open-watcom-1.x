# RCSDLL Builder Control file
# ===========================

set PROJDIR=<CWD>
set PROJNAME=rcsdll

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/wini86/rcsdll.dll  <RELROOT>/binw/rcsdll.dll
    <CPCMD> <PROJDIR>/bat/*.bat          <RELROOT>/binw/
    <CCCMD> <PROJDIR>/os2386/rcsdll.dll  <RELROOT>/binp/dll/rcsdll.dll
    <CPCMD> <PROJDIR>/cmd/*.cmd          <RELROOT>/binp/
    <CCCMD> <PROJDIR>/nt386/rcsdll.dll   <RELROOT>/binnt/rcsdll.dll
    <CCCMD> <PROJDIR>/ntaxp/rcsdll.dll   <RELROOT>/axpnt/rcsdll.dll

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean

[ BLOCK . . ]
#============
cdsay <PROJDIR>

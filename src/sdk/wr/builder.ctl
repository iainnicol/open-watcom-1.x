# WR Builder Control file
# =======================

set PROJDIR=<CWD>
set PROJNAME=wr

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/wini86/wr.dll        <RELROOT>/binw/wr.dll
    <CCCMD> <PROJDIR>/nt386/wr.dll         <RELROOT>/binnt/wr.dll
    <CCCMD> <PROJDIR>/ntaxp/wr.dll         <RELROOT>/axpnt/wr.dll

[ BLOCK . . ]
#============
cdsay <PROJDIR>

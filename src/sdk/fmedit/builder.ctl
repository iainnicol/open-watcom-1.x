# FMEDIT Builder Control file
# ===========================

set PROJDIR=<CWD>
set PROJNAME=fmedit

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/wini86/fmedit.dll  <RELROOT>/binw/
    <CCCMD> <PROJDIR>/nt386/fmedit.dll   <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/ntaxp/fmedit.dll   <RELROOT>/axpnt/

[ BLOCK . . ]
#============
cdsay <PROJDIR>

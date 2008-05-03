# DDESPY Builder Control file
# ============================

set PROJDIR=<CWD>
set PROJNAME=ddespy

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/wini86/wddespy.exe <RELROOT>/binw/wddespy.exe
    <CCCMD> <PROJDIR>/nt386/wddespy.exe  <RELROOT>/binnt/wddespy.exe
    <CCCMD> <PROJDIR>/ntaxp/wddespy.exe  <RELROOT>/axpnt/wddespy.exe

[ BLOCK . . ]
#============
cdsay <PROJDIR>

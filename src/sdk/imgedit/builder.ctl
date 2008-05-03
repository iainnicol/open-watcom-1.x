# IMAGE EDITOR Builder Control file
# =================================

set PROJDIR=<CWD>
set PROJNAME=imgedit

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/wini86/wimgedit.exe <RELROOT>/binw/
    <CCCMD> <PROJDIR>/nt386/wimgedit.exe  <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/ntaxp/wimgedit.exe  <RELROOT>/axpnt/

[ BLOCK . . ]
#============
cdsay <PROJDIR>

# WSTRIP Builder Control file
# ===========================

set PROJDIR=<CWD>
set PROJNAME=wstrip

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> boot ]
#=================
    <CPCMD> <OWOBJDIR>/wstripx.exe <OWBINDIR>/wstrip<CMDEXT>

[ BLOCK <1> bootclean ]
#======================
    echo rm -f <OWBINDIR>/wstrip<CMDEXT>
    rm -f <OWBINDIR>/wstrip<CMDEXT>

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/dosi86/wstripx.exe    <RELROOT>/binw/wstrip.exe
    <CCCMD> <PROJDIR>/os2386/wstripx.exe    <RELROOT>/binp/wstrip.exe
    <CCCMD> <PROJDIR>/nt386/wstripx.exe     <RELROOT>/binnt/wstrip.exe
    <CCCMD> <PROJDIR>/linux386/wstripx.exe  <RELROOT>/binl/wstrip
    <CCCMD> <PROJDIR>/ntaxp/wstripx.exe     <RELROOT>/axpnt/wstrip.exe
    <CCCMD> <PROJDIR>/qnx386/wstripx.exe    <RELROOT>/qnx/binq/wstrip

[ BLOCK . . ]
#============
cdsay <PROJDIR>

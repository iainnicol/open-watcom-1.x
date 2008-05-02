# WSTRIP Builder Control file
# ===========================

set PROJDIR=<CWD>
set PROJNAME=wstrip

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

set BOOTCOPY=<CPCMD> strip.exe <OWBINDIR>/wstrip<CMDEXT>
set BOOTCLEAN=rm -f <OWBINDIR>/wstrip<CMDEXT>

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/dosi86/strip.exe    <RELROOT>/binw/wstrip.exe
    <CCCMD> <PROJDIR>/os2386/strip.exe    <RELROOT>/binp/wstrip.exe
    <CCCMD> <PROJDIR>/nt386/strip.exe     <RELROOT>/binnt/wstrip.exe
    <CCCMD> <PROJDIR>/linux386/strip.exe  <RELROOT>/binl/wstrip
    <CCCMD> <PROJDIR>/ntaxp/strip.exe     <RELROOT>/axpnt/wstrip.exe
    <CCCMD> <PROJDIR>/qnx386/strip.exe    <RELROOT>/qnx/binq/wstrip.

[ BLOCK . . ]
#============
cdsay <PROJDIR>

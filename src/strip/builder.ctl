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

[ BLOCK <1> rel2 cprel2 ]
#========================
    <CCCMD> <DEVDIR>/wstrip/dosi86/strip.exe    <RELROOT>/binw/wstrip.exe
    <CCCMD> <DEVDIR>/wstrip/os2386/strip.exe    <RELROOT>/binp/wstrip.exe
    <CCCMD> <DEVDIR>/wstrip/nt386/strip.exe     <RELROOT>/binnt/wstrip.exe
    <CCCMD> <DEVDIR>/wstrip/linux386/strip.exe  <RELROOT>/binl/wstrip
    <CCCMD> <DEVDIR>/wstrip/ntaxp/strip.exe     <RELROOT>/axpnt/wstrip.exe
    <CCCMD> <DEVDIR>/wstrip/qnx386/strip.exe    <RELROOT>/qnx/binq/wstrip.

[ BLOCK . . ]
#============
cdsay <PROJDIR>

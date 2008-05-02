# wmake Builder Control file
# ==========================

set PROJDIR=<CWD>
set PROJNAME=wmake

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> dos386/wmk.exe    <RELROOT>/binw/wmake.exe
    <CCCMD> dos386/wmk.sym    <RELROOT>/binw/wmake.sym
    <CCCMD> dosi86/wmk.exe    <RELROOT>/binw/wmaker.exe
    <CCCMD> dosi86/wmk.sym    <RELROOT>/binw/wmaker.sym
    <CCCMD> os2386/wmk.exe    <RELROOT>/binp/wmake.exe
    <CCCMD> os2386/wmk.sym    <RELROOT>/binp/wmake.sym
    <CCCMD> nt386/wmk.exe     <RELROOT>/binnt/wmake.exe
    <CCCMD> nt386/wmk.sym     <RELROOT>/binnt/wmake.sym
    <CCCMD> ntaxp/wmk.exe     <RELROOT>/axpnt/wmake.exe
    <CCCMD> ntaxp/wmk.sym     <RELROOT>/axpnt/wmake.sym
    <CCCMD> qnx386/wmk.exe    <RELROOT>/qnx/binq/wmake
    <CCCMD> qnx386/wmk.sym    <RELROOT>/qnx/sym/wmake.sym
    <CCCMD> linux386/wmk.exe  <RELROOT>/binl/wmake
    <CCCMD> linux386/wmk.sym  <RELROOT>/binl/wmake.sym

[ BLOCK . . ]
#============
cdsay <PROJDIR>

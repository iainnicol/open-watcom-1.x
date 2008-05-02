# wdis Builder Control file
# =========================

set PROJDIR=<CWD>
set PROJNAME=wdis

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/deftool.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/dos386/wdis.exe   <RELROOT>/binw/
    <CCCMD> <PROJDIR>/dos386/wdis.sym   <RELROOT>/binw/
    <CCCMD> <PROJDIR>/os2386/wdis.exe   <RELROOT>/binp/
    <CCCMD> <PROJDIR>/os2386/wdis.sym   <RELROOT>/binp/
    <CCCMD> <PROJDIR>/nt386/wdis.exe    <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/nt386/wdis.sym    <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/ntaxp/wdis.exe    <RELROOT>/axpnt/
    <CCCMD> <PROJDIR>/ntaxp/wdis.sym    <RELROOT>/axpnt/
    <CCCMD> <PROJDIR>/qnx386/wdis.exe   <RELROOT>/qnx/binq/wdis
    <CCCMD> <PROJDIR>/qnx386/wdis.sym   <RELROOT>/qnx/sym/
    <CCCMD> <PROJDIR>/linux386/wdis.exe <RELROOT>/binl/wdis
    <CCCMD> <PROJDIR>/linux386/wdis.sym <RELROOT>/binl/

[ BLOCK . . ]
#============
cdsay <PROJDIR>

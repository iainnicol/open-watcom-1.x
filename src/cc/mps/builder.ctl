# wccmps Builder Control file
# ===========================

set PROJDIR=<CWD>
set PROJNAME=wccmps

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/deftool.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> dos386/wccmpsc.exe    <RELROOT>/binw/wccmps.exe
    <CCCMD> dos386/wccmpsc.sym    <RELROOT>/binw/wccmps.sym
    <CCCMD> os2386/wccmpsc.exe    <RELROOT>/binp/wccmps.exe
    <CCCMD> os2386/wccmpsc.sym    <RELROOT>/binp/wccmps.sym
    <CCCMD> os2386/wccdmpsc.dll   <RELROOT>/binp/dll/wccdmps.dll
    <CCCMD> os2386/wccdmpsc.sym   <RELROOT>/binp/dll/wccdmps.sym
    <CCCMD> nt386/wccmpsc.exe     <RELROOT>/binnt/wccmps.exe
    <CCCMD> nt386/wccmpsc.sym     <RELROOT>/binnt/wccmps.sym
    <CCCMD> nt386/wccdmpsc.dll    <RELROOT>/binnt/wccdmps.dll
    <CCCMD> nt386/wccdmpsc.sym    <RELROOT>/binnt/wccdmps.sym
    <CCCMD> ntaxp/wccmpsc.exe     <RELROOT>/axpnt/wccmps.exe
    <CCCMD> ntaxp/wccmpsc.sym     <RELROOT>/axpnt/wccmps.sym
    <CCCMD> ntaxp/wccdmpsc.dll    <RELROOT>/axpnt/wccdmps.dll
    <CCCMD> ntaxp/wccdmpsc.sym    <RELROOT>/axpnt/wccdmps.sym
    <CCCMD> qnx386/wccmpsc.exe    <RELROOT>/qnx/binq/wccmps
    <CCCMD> qnx386/wccmpsc.sym    <RELROOT>/qnx/sym/wccmps.sym
    <CCCMD> linux386/wccmpsc.exe  <RELROOT>/binl/wccmps
    <CCCMD> linux386/wccmpsc.sym  <RELROOT>/binl/wccmps.sym

[ BLOCK . . ]
#============
cdsay <PROJDIR>

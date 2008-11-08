# wppaxp Builder Control file
# ===========================

set PROJDIR=<CWD>
set PROJNAME=wppaxp

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/deftool.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> dos386/wcppaxp.exe    <RELROOT>/binw/wppaxp.exe
    <CCCMD> dos386/wcppaxp.sym    <RELROOT>/binw/wppaxp.sym
    <CCCMD> os2386/wcppaxp.exe    <RELROOT>/binp/wppaxp.exe
    <CCCMD> os2386/wcppaxp.sym    <RELROOT>/binp/wppaxp.sym
    <CCCMD> os2386/wppdaxp.dll    <RELROOT>/binp/dll/wppdaxp.dll
    <CCCMD> os2386/wppdaxp.sym    <RELROOT>/binp/dll/wppdaxp.sym
    <CCCMD> nt386/wcppaxp.exe     <RELROOT>/binnt/wppaxp.exe
    <CCCMD> nt386/wcppaxp.sym     <RELROOT>/binnt/wppaxp.sym
    <CCCMD> nt386/wppdaxp.dll     <RELROOT>/binnt/wppdaxp.dll
    <CCCMD> nt386/wppdaxp.sym     <RELROOT>/binnt/wppdaxp.sym
    <CCCMD> ntaxp/wcppaxp.exe     <RELROOT>/axpnt/wppaxp.exe
    <CCCMD> ntaxp/wcppaxp.sym     <RELROOT>/axpnt/wppaxp.sym
    <CCCMD> ntaxp/wppdaxp.dll     <RELROOT>/axpnt/wppdaxp.dll
    <CCCMD> ntaxp/wppdaxp.sym     <RELROOT>/axpnt/wppdaxp.sym
    <CCCMD> linux386/wcppaxp.exe  <RELROOT>/binl/wppaxp
    <CCCMD> linux386/wcppaxp.sym  <RELROOT>/binl/wppaxp.sym

[ BLOCK . . ]
#============
cdsay <PROJDIR>

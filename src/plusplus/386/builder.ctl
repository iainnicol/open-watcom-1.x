# wpp386 Builder Control file
# ===========================

set PROJDIR=<CWD>
set PROJNAME=wpp386

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/deftool.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> dos386/wcpp386.exe    <RELROOT>/binw/wpp386.exe
    <CCCMD> dos386/wcpp386.sym    <RELROOT>/binw/wpp386.sym
    <CCCMD> os2386/wcpp386.exe    <RELROOT>/binp/wpp386.exe
    <CCCMD> os2386/wcpp386.sym    <RELROOT>/binp/wpp386.sym
    <CCCMD> os2386/wccd386.dll    <RELROOT>/binp/dll/wccd386.dll
    <CCCMD> os2386/wccd386.sym    <RELROOT>/binp/dll/wccd386.sym
    <CCCMD> nt386/wcpp386.exe     <RELROOT>/binnt/wpp386.exe
    <CCCMD> nt386/wcpp386.sym     <RELROOT>/binnt/wpp386.sym
    <CCCMD> nt386/wppd386.dll     <RELROOT>/binnt/wppd386.dll
    <CCCMD> nt386/wppd386.sym     <RELROOT>/binnt/wppd386.sym
    <CCCMD> ntaxp/wcpp386.exe     <RELROOT>/axpnt/wpp386.exe
    <CCCMD> ntaxp/wcpp386.sym     <RELROOT>/axpnt/wpp386.sym
    <CCCMD> ntaxp/wppd386.dll     <RELROOT>/axpnt/wppd386.dll
    <CCCMD> ntaxp/wppd386.sym     <RELROOT>/axpnt/wppd386.sym
    <CCCMD> qnx386/wcpp386.exe    <RELROOT>/qnx/binq/wpp386
    <CCCMD> qnx386/wcpp386.sym    <RELROOT>/qnx/sym/wpp386.sym
    <CCCMD> linux386/wcpp386.exe  <RELROOT>/binl/wpp386
    <CCCMD> linux386/wcpp386.sym  <RELROOT>/binl/wpp386.sym

[ BLOCK . . ]
#============
cdsay <PROJDIR>

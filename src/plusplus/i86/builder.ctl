# wpp Builder Control file
# ========================

set PROJDIR=<CWD>
set PROJNAME=wpp

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

set BOOTCOPY=<CPCMD> wppi86.exe <OWBINDIR>/wpp<CMDEXT>
set BOOTCLEAN=rm -f <OWBINDIR>/wpp<CMDEXT>

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> dos386/wcpp386.exe    <RELROOT>/binw/wpp.exe
    <CCCMD> dos386/wcpp386.sym    <RELROOT>/binw/wpp6.sym
    <CCCMD> os2386/wcpp386.exe    <RELROOT>/binp/wpp.exe
    <CCCMD> os2386/wcpp386.sym    <RELROOT>/binp/wpp.sym
    <CCCMD> os2386/wccd386.dll    <RELROOT>/binp/dll/wppd.dll
    <CCCMD> os2386/wccd386.sym    <RELROOT>/binp/dll/wppd.sym
    <CCCMD> nt386/wcpp386.exe     <RELROOT>/binnt/wpp.exe
    <CCCMD> nt386/wcpp386.sym     <RELROOT>/binnt/wpp.sym
    <CCCMD> nt386/wccd386.dll     <RELROOT>/binnt/wppd.exe
    <CCCMD> nt386/wccd386.sym     <RELROOT>/binnt/wppd.sym
    <CCCMD> ntaxp/wcpp386.exe     <RELROOT>/axpnt/wpp.exe
    <CCCMD> ntaxp/wcpp386.sym     <RELROOT>/axpnt/wpp.sym
    <CCCMD> ntaxp/wccd386.dll     <RELROOT>/axpnt/wppd.dll
    <CCCMD> ntaxp/wccd386.sym     <RELROOT>/axpnt/wppd.sym
    <CCCMD> qnx386/wcpp386.exe    <RELROOT>/qnx/binq/wpp
    <CCCMD> qnx386/wcpp386.sym    <RELROOT>/qnx/sym/wpp.sym
    <CCCMD> linux386/wcpp386.exe  <RELROOT>/binl/wpp
    <CCCMD> linux386/wcpp386.sym  <RELROOT>/binl/wpp.sym

[ BLOCK . . ]
#============
cdsay <PROJDIR>

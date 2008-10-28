# wpp Builder Control file
# ========================

set PROJDIR=<CWD>
set PROJNAME=wpp

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

set BOOTCOPY=<CPCMD> wppi86.exe <OWBINDIR>/<PROJNAME><CMDEXT>
set BOOTCLEAN=rm -f <OWBINDIR>/<PROJNAME><CMDEXT>

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> dos386/wcppi86.exe    <RELROOT>/binw/wpp.exe
    <CCCMD> dos386/wcppi86.sym    <RELROOT>/binw/wpp.sym
    <CCCMD> os2386/wcppi86.exe    <RELROOT>/binp/wpp.exe
    <CCCMD> os2386/wcppi86.sym    <RELROOT>/binp/wpp.sym
    <CCCMD> os2386/wccdi86.dll    <RELROOT>/binp/dll/wppd.dll
    <CCCMD> os2386/wccdi86.sym    <RELROOT>/binp/dll/wppd.sym
    <CCCMD> nt386/wcppi86.exe     <RELROOT>/binnt/wpp.exe
    <CCCMD> nt386/wcppi86.sym     <RELROOT>/binnt/wpp.sym
    <CCCMD> nt386/wccdi86.dll     <RELROOT>/binnt/wppd.exe
    <CCCMD> nt386/wccdi86.sym     <RELROOT>/binnt/wppd.sym
    <CCCMD> ntaxp/wcppi86.exe     <RELROOT>/axpnt/wpp.exe
    <CCCMD> ntaxp/wcppi86.sym     <RELROOT>/axpnt/wpp.sym
    <CCCMD> ntaxp/wccdi86.dll     <RELROOT>/axpnt/wppd.dll
    <CCCMD> ntaxp/wccdi86.sym     <RELROOT>/axpnt/wppd.sym
    <CCCMD> qnx386/wcppi86.exe    <RELROOT>/qnx/binq/wpp
    <CCCMD> qnx386/wcppi86.sym    <RELROOT>/qnx/sym/wpp.sym
    <CCCMD> linux386/wcppi86.exe  <RELROOT>/binl/wpp
    <CCCMD> linux386/wcppi86.sym  <RELROOT>/binl/wpp.sym

[ BLOCK . . ]
#============
cdsay <PROJDIR>

# wpp Builder Control file
# ========================

set PROJDIR=<CWD>
set PROJNAME=wpp

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> boot ]
#=================
    <CPCMD> <PROJDIR>/<OWOBJDIR>/wppi86.exe <OWBINDIR>/wpp<CMDEXT>

[ BLOCK <1> bootclean ]
#======================
    echo rm -f <OWBINDIR>/wpp<CMDEXT>
    rm -f <OWBINDIR>/wpp<CMDEXT>

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> dos386/wcppi86.exe    <RELROOT>/binw/wpp.exe
    <CCCMD> dos386/wcppi86.sym    <RELROOT>/binw/wpp.sym
    <CCCMD> os2386/wcppi86.exe    <RELROOT>/binp/wpp.exe
    <CCCMD> os2386/wcppi86.sym    <RELROOT>/binp/wpp.sym
    <CCCMD> os2386/wppdi86.dll    <RELROOT>/binp/dll/wppdi86.dll
    <CCCMD> os2386/wppdi86.sym    <RELROOT>/binp/dll/wppdi86.sym
    <CCCMD> nt386/wcppi86.exe     <RELROOT>/binnt/wpp.exe
    <CCCMD> nt386/wcppi86.sym     <RELROOT>/binnt/wpp.sym
    <CCCMD> nt386/wppdi86.dll     <RELROOT>/binnt/wppdi86.dll
    <CCCMD> nt386/wppdi86.sym     <RELROOT>/binnt/wppdi86.sym
    <CCCMD> ntaxp/wcppi86.exe     <RELROOT>/axpnt/wpp.exe
    <CCCMD> ntaxp/wcppi86.sym     <RELROOT>/axpnt/wpp.sym
    <CCCMD> ntaxp/wppdi86.dll     <RELROOT>/axpnt/wppdi86.dll
    <CCCMD> ntaxp/wppdi86.sym     <RELROOT>/axpnt/wppdi86.sym
    <CCCMD> qnx386/wcppi86.exe    <RELROOT>/qnx/binq/wpp
    <CCCMD> qnx386/wcppi86.sym    <RELROOT>/qnx/sym/wpp.sym
    <CCCMD> linux386/wcppi86.exe  <RELROOT>/binl/wpp
    <CCCMD> linux386/wcppi86.sym  <RELROOT>/binl/wpp.sym

[ BLOCK . . ]
#============
cdsay <PROJDIR>

# wcc Builder Control file
# ========================

set PROJDIR=<CWD>
set PROJNAME=wcc

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> boot ]
#=================
    <CPCMD> <OWOBJDIR>/wcci86.exe <OWBINDIR>/wcc<CMDEXT>

[ BLOCK <1> bootclean ]
#======================
    echo rm -f <OWBINDIR>/wcc<CMDEXT>
    rm -f <OWBINDIR>/wcc<CMDEXT>

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> dos386/wcci86c.exe    <RELROOT>/binw/wcc.exe
    <CCCMD> dos386/wcci86c.sym    <RELROOT>/binw/wcc.sym
    <CCCMD> os2386/wcci86c.exe    <RELROOT>/binp/wcc.exe
    <CCCMD> os2386/wcci86c.sym    <RELROOT>/binp/wcc.sym
    <CCCMD> os2386/wccdi86c.dll   <RELROOT>/binp/dll/wccd.dll
    <CCCMD> os2386/wccdi86c.sym   <RELROOT>/binp/dll/wccd.sym
    <CCCMD> nt386/wcci86c.exe     <RELROOT>/binnt/wcc.exe
    <CCCMD> nt386/wcci86c.sym     <RELROOT>/binnt/wcc.sym
    <CCCMD> nt386/wccdi86c.dll    <RELROOT>/binnt/wccd.dll
    <CCCMD> nt386/wccdi86c.sym    <RELROOT>/binnt/wccd.sym
    <CCCMD> ntaxp/wcci86c.exe     <RELROOT>/axpnt/wcc.exe
    <CCCMD> ntaxp/wcci86c.sym     <RELROOT>/axpnt/wcc.sym
    <CCCMD> ntaxp/wccdi86c.dll    <RELROOT>/axpnt/wccd.dll
    <CCCMD> ntaxp/wccdi86c.sym    <RELROOT>/axpnt/wccd.sym
    <CCCMD> qnx386/wcci86c.exe    <RELROOT>/qnx/binq/wcc
    <CCCMD> qnx386/wcci86c.sym    <RELROOT>/qnx/sym/wcc.sym
    <CCCMD> linux386/wcci86c.exe  <RELROOT>/binl/wcc
    <CCCMD> linux386/wcci86c.sym  <RELROOT>/binl/wcc.sym

[ BLOCK . . ]
#============
cdsay <PROJDIR>

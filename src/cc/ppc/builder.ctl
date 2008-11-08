# wccppc Builder Control file
# ===========================

set PROJDIR=<CWD>
set PROJNAME=wccppc

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/deftool.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> dos386/wccppcc.exe    <RELROOT>/binw/wccppc.exe
    <CCCMD> dos386/wccppcc.sym    <RELROOT>/binw/wccppc.sym
    <CCCMD> os2386/wccppcc.exe    <RELROOT>/binp/wccppc.exe
    <CCCMD> os2386/wccppcc.sym    <RELROOT>/binp/wccppc.sym
    <CCCMD> os2386/wccdppcc.dll   <RELROOT>/binp/dll/wccdppc.dll
    <CCCMD> os2386/wccdppcc.sym   <RELROOT>/binp/dll/wccdppc.sym
    <CCCMD> nt386/wccppcc.exe     <RELROOT>/binnt/wccppc.exe
    <CCCMD> nt386/wccppcc.sym     <RELROOT>/binnt/wccppc.sym
    <CCCMD> nt386/wccdppcc.dll    <RELROOT>/binnt/wccdppc.dll
    <CCCMD> nt386/wccdppcc.sym    <RELROOT>/binnt/wccdppc.sym
    <CCCMD> ntaxp/wccppcc.exe     <RELROOT>/axpnt/wccppc.exe
    <CCCMD> ntaxp/wccppcc.sym     <RELROOT>/axpnt/wccppc.sym
    <CCCMD> ntaxp/wccdppcc.dll    <RELROOT>/axpnt/wccdppc.dll
    <CCCMD> ntaxp/wccdppcc.sym    <RELROOT>/axpnt/wccdppc.sym
    <CCCMD> qnx386/wccppcc.exe    <RELROOT>/qnx/binq/wccppc
    <CCCMD> qnx386/wccppcc.sym    <RELROOT>/qnx/sym/wccppc.sym
    <CCCMD> linux386/wccppcc.exe  <RELROOT>/binl/wccppc
    <CCCMD> linux386/wccppcc.sym  <RELROOT>/binl/wccppc.sym

[ BLOCK . . ]
#============
cdsay <PROJDIR>

# wlib Builder Control file
# =========================

set PROJDIR=<CWD>
set PROJNAME=wlib

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/deftool.ctl ]

[ BLOCK <1> rel2 cprel2 ]
#========================
    <CCCMD> dos386/wlib.exe    <RELROOT>/binw/
    <CCCMD> dos386/wlib.sym    <RELROOT>/binw/
    <CCCMD> os2386/wlib.exe    <RELROOT>/binp/
    <CCCMD> os2386/wlibd.dll   <RELROOT>/binp/dll/
    <CCCMD> os2386/wlibd.sym   <RELROOT>/binp/dll/
    <CCCMD> nt386/wlib.exe     <RELROOT>/binnt/
    <CCCMD> nt386/wlibd.dll    <RELROOT>/binnt/
    <CCCMD> nt386/wlibd.sym    <RELROOT>/binnt/
    <CCCMD> ntaxp/wlib.exe     <RELROOT>/axpnt/
    <CCCMD> ntaxp/wlibd.dll    <RELROOT>/axpnt/
    <CCCMD> ntaxp/wlibd.sym    <RELROOT>/axpnt/
    <CCCMD> qnx386/wlib.exe    <RELROOT>/qnx/binq/wlib
    <CCCMD> qnx386/wlib.sym    <RELROOT>/qnx/sym/wlib.sym
    <CCCMD> linux386/wlib.exe  <RELROOT>/binl/wlib
    <CCCMD> linux386/wlib.sym  <RELROOT>/binl/wlib.sym

[ BLOCK . . ]
#============

cdsay <PROJDIR>

# wccaxp Builder Control file
# ===========================

set PROJDIR=<CWD>
set PROJNAME=wccaxp

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> boot ]
#=================
    <CPCMD> <OWOBJDIR>/wccaxpc.exe <OWBINDIR>/<PROJNAME><CMDEXT>

[ BLOCK <1> bootclean ]
#======================
    echo rm -f <OWBINDIR>/<PROJNAME><CMDEXT>
    rm -f <OWBINDIR>/<PROJNAME><CMDEXT>

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> dos386/wccaxpc.exe    <RELROOT>/binw/wccaxp.exe
    <CCCMD> dos386/wccaxpc.sym    <RELROOT>/binw/wccaxp.sym
    <CCCMD> os2386/wccaxpc.exe    <RELROOT>/binp/wccaxp.exe
    <CCCMD> os2386/wccaxpc.sym    <RELROOT>/binp/wccaxp.sym
    <CCCMD> os2386/wccdaxpc.dll   <RELROOT>/binp/dll/wccdaxp.dll
    <CCCMD> os2386/wccdaxpc.sym   <RELROOT>/binp/dll/wccdaxp.sym
    <CCCMD> nt386/wccaxpc.exe     <RELROOT>/binnt/wccaxp.exe
    <CCCMD> nt386/wccaxpc.sym     <RELROOT>/binnt/wccaxp.sym
    <CCCMD> nt386/wccdaxpc.dll    <RELROOT>/binnt/wccdaxp.dll
    <CCCMD> nt386/wccdaxpc.sym    <RELROOT>/binnt/wccdaxp.sym
    <CCCMD> ntaxp/wccaxpc.exe     <RELROOT>/axpnt/wccaxp.exe
    <CCCMD> ntaxp/wccaxpc.sym     <RELROOT>/axpnt/wccaxp.sym
    <CCCMD> ntaxp/wccdaxpc.dll    <RELROOT>/axpnt/wccdaxp.dll
    <CCCMD> ntaxp/wccdaxpc.sym    <RELROOT>/axpnt/wccdaxp.sym
    <CCCMD> qnx386/wccaxpc.exe    <RELROOT>/qnx/binq/wccaxp
    <CCCMD> qnx386/wccaxpc.sym    <RELROOT>/qnx/sym/wccaxp.sym
    <CCCMD> linux386/wccaxpc.exe  <RELROOT>/binl/wccaxp
    <CCCMD> linux386/wccaxpc.sym  <RELROOT>/binl/wccaxp.sym

[ BLOCK . . ]
#============
cdsay <PROJDIR>

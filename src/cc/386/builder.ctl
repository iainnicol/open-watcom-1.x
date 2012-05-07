# wcc386 Builder Control file
# ===========================

set PROJDIR=<CWD>
set PROJNAME=wcc386

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> boot ]
#=================
    <CPCMD> <OWOBJDIR>/wcc386c.exe <OWBINDIR>/<PROJNAME><CMDEXT>

[ BLOCK <1> bootclean ]
#======================
    echo rm -f <OWBINDIR>/<PROJNAME><CMDEXT>
    rm -f <OWBINDIR>/<PROJNAME><CMDEXT>

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> dos386/wcc386c.exe    <RELROOT>/binw/wcc386.exe
    <CCCMD> dos386/wcc386c.sym    <RELROOT>/binw/wcc386.sym
    <CCCMD> os2386/wcc386c.exe    <RELROOT>/binp/wcc386.exe
    <CCCMD> os2386/wcc386c.sym    <RELROOT>/binp/wcc386.sym
    <CCCMD> os2386/wccd386c.dll   <RELROOT>/binp/dll/wccd386.dll
    <CCCMD> os2386/wccd386c.sym   <RELROOT>/binp/dll/wccd386.sym
    <CCCMD> nt386/wcc386c.exe     <RELROOT>/binnt/wcc386.exe
    <CCCMD> nt386/wcc386c.sym     <RELROOT>/binnt/wcc386.sym
    <CCCMD> nt386/wccd386c.dll    <RELROOT>/binnt/wccd386.dll
    <CCCMD> nt386/wccd386c.sym    <RELROOT>/binnt/wccd386.sym
    <CCCMD> ntaxp/wcc386c.exe     <RELROOT>/axpnt/wcc386.exe
    <CCCMD> ntaxp/wcc386c.sym     <RELROOT>/axpnt/wcc386.sym
    <CCCMD> ntaxp/wccd386c.dll    <RELROOT>/axpnt/wccd386.dll
    <CCCMD> ntaxp/wccd386c.sym    <RELROOT>/axpnt/wccd386.sym
    <CCCMD> qnx386/wcc386c.exe    <RELROOT>/qnx/binq/wcc386
    <CCCMD> qnx386/wcc386c.sym    <RELROOT>/qnx/sym/wcc386.sym
    <CCCMD> linux386/wcc386c.exe  <RELROOT>/binl/wcc386
    <CCCMD> linux386/wcc386c.sym  <RELROOT>/binl/wcc386.sym

[ BLOCK . . ]
#============
cdsay <PROJDIR>

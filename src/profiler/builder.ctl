# WPROF Builder Control file
# ==========================

set PROJDIR=<CWD>
set PROJNAME=wprof

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/deftool.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/dos386/wprof.exe     <RELROOT>/binw/wprof.exe
    <CCCMD> <PROJDIR>/wini86/wprof.exe     <RELROOT>/binw/wprofw.exe
    <CCCMD> <PROJDIR>/os2386pm/wprof.exe   <RELROOT>/binp/wprof.exe
    <CCCMD> <PROJDIR>/os2386/wprof.exe     <RELROOT>/binp/wprofc.exe
    <CCCMD> <PROJDIR>/nt386/wprof.exe      <RELROOT>/binnt/wprof.exe
    <CCCMD> <PROJDIR>/nt386c/wprof.exe     <RELROOT>/binnt/wprofc.exe
    <CCCMD> <PROJDIR>/ntaxp/wprof.exe      <RELROOT>/axpnt/wprof.exe
    <CCCMD> <PROJDIR>/linux386/wprof.exe   <RELROOT>/binl/wprof
    <CCCMD> <PROJDIR>/linux386/wprof.sym   <RELROOT>/binl/wprof.sym
    <CCCMD> <PROJDIR>/qnx386/wprof.qnx     <RELROOT>/qnx/binq/wprof.
    <CCCMD> <PROJDIR>/qnx386/wprof.sym     <RELROOT>/qnx/sym/wprof.sym

[ BLOCK . . ]
#============
cdsay <PROJDIR>

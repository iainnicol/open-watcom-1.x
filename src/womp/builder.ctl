# womp Builder Control file
# =========================

set PROJDIR=<CWD>
set PROJNAME=womp

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/deftool.ctl ]

[ BLOCK <1> rel2 cprel2 ]
#========================
    <CCCMD> <PROJDIR>/dosi86/womp.exe   <RELROOT>/binw/
    <CCCMD> <PROJDIR>/dosi86/womp.sym   <RELROOT>/binw/
    <CCCMD> <PROJDIR>/os2386/womp.exe   <RELROOT>/binp/
    <CCCMD> <PROJDIR>/os2386/womp.sym   <RELROOT>/binp/
    <CCCMD> <PROJDIR>/nt386/womp.exe    <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/nt386/womp.sym    <RELROOT>/binnt/
#    <CCCMD> <PROJDIR>/ntaxp/womp.exe    <RELROOT>/axpnt/
#    <CCCMD> <PROJDIR>/ntaxp/womp.sym    <RELROOT>/axpnt/
#    <CCCMD> <PROJDIR>/linux386/womp.exe <RELROOT>/binl/womp
#    <CCCMD> <PROJDIR>/linux386/womp.sym <RELROOT>/binl/

[ BLOCK . . ]
#============
cdsay <PROJDIR>

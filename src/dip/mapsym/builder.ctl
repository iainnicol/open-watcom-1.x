# MAPSYM DIP Builder Control file
# ===============================

set PROJDIR=<CWD>
set PROJNAME=mapsym

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defdylib.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/dos386/mapsym.dip         <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/dos386/mapsym.sym         <RELROOT>/binw/mapsym.dsy

    <CCCMD> <PROJDIR>/wini86/mapsym.dll         <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/wini86/mapsym.sym         <RELROOT>/binw/

#    <CCCMD> <PROJDIR>/os2i86/mapsym.dll         <RELROOT>/binp/dll/
#    <CCCMD> <PROJDIR>/os2i86/mapsym.sym         <RELROOT>/binp/dll/
    <CCCMD> <PROJDIR>/os2386/mapsym.d32         <RELROOT>/binp/
    <CCCMD> <PROJDIR>/os2386/mapsym.sym         <RELROOT>/binp/

    <CCCMD> <PROJDIR>/nt386/mapsym.dll          <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/nt386/mapsym.sym          <RELROOT>/binnt/

    <CCCMD> <PROJDIR>/linux386/mapsym.dip       <RELROOT>/binl/
    <CCCMD> <PROJDIR>/linux386/mapsym.sym       <RELROOT>/binl/

    <CCCMD> <PROJDIR>/ntaxp/mapsym.dll          <RELROOT>/axpnt/
    <CCCMD> <PROJDIR>/ntaxp/mapsym.sym          <RELROOT>/axpnt/

    <CCCMD> <PROJDIR>/qnx386/mapsym.dip         <RELROOT>/qnx/watcom/wd/
    <CCCMD> <PROJDIR>/qnx386/mapsym.sym         <RELROOT>/qnx/sym/

[ BLOCK . . ]
#============
cdsay <PROJDIR>

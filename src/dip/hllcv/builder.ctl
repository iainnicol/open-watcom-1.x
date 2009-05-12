# IBM HLL/CodeView DIP Builder Control file
# =========================================

set PROJDIR=<CWD>
set PROJNAME=hllcv

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defdylib.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/dos386/hllcv.dip      <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/dos386/hllcv.sym      <RELROOT>/binw/hllcv.dsy

    <CCCMD> <PROJDIR>/wini86/hllcv.dll      <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/wini86/hllcv.sym      <RELROOT>/binw/

#    <CCCMD> <PROJDIR>/os2i86/hllcv.dll      <RELROOT>/binp/dll/
#    <CCCMD> <PROJDIR>/os2i86/hllcv.sym      <RELROOT>/binp/dll/
    <CCCMD> <PROJDIR>/os2386/hllcv.d32      <RELROOT>/binp/
    <CCCMD> <PROJDIR>/os2386/hllcv.sym      <RELROOT>/binp/

    <CCCMD> <PROJDIR>/nt386/hllcv.dll       <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/nt386/hllcv.sym       <RELROOT>/binnt/

    <CCCMD> <PROJDIR>/linux386/hllcv.dip    <RELROOT>/binl/
    <CCCMD> <PROJDIR>/linux386/hllcv.sym    <RELROOT>/binl/

    <CCCMD> <PROJDIR>/ntaxp/hllcv.dll       <RELROOT>/axpnt/
    <CCCMD> <PROJDIR>/ntaxp/hllcv.sym       <RELROOT>/axpnt/

    <CCCMD> <PROJDIR>/qnx386/hllcv.dip      <RELROOT>/qnx/watcom/wd/
    <CCCMD> <PROJDIR>/qnx386/hllcv.sym      <RELROOT>/qnx/sym/

[ BLOCK . . ]
#============
cdsay <PROJDIR>

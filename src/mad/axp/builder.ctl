# Alpha AXP MAD Builder Control file
# ==================================

set PROJDIR=<CWD>
set PROJNAME=madaxp

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defdylib.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/dos386/madaxp.mad     <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/dos386/madaxp.sym     <RELROOT>/binw/madaxp.dsy

    <CCCMD> <PROJDIR>/wini86/madaxp.dll     <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/wini86/madaxp.sym     <RELROOT>/binw/

#    <CCCMD> <PROJDIR>/os2i86/madaxp.dll     <RELROOT>/binp/dll/
#    <CCCMD> <PROJDIR>/os2i86/madaxp.sym     <RELROOT>/binp/dll/
    <CCCMD> <PROJDIR>/os2386/madaxp.d32     <RELROOT>/binp/
    <CCCMD> <PROJDIR>/os2386/madaxp.sym     <RELROOT>/binp/

    <CCCMD> <PROJDIR>/nt386/madaxp.dll      <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/nt386/madaxp.sym      <RELROOT>/binnt/

    <CCCMD> <PROJDIR>/linux386/madaxp.mad   <RELROOT>/binl/
    <CCCMD> <PROJDIR>/linux386/madaxp.sym   <RELROOT>/binl/

    <CCCMD> <PROJDIR>/ntaxp/madaxp.dll      <RELROOT>/axpnt/
    <CCCMD> <PROJDIR>/ntaxp/madaxp.sym      <RELROOT>/axpnt/

    <CCCMD> <PROJDIR>/qnx386/madaxp.mad     <RELROOT>/qnx/watcom/wd/
    <CCCMD> <PROJDIR>/qnx386/madaxp.sym     <RELROOT>/qnx/sym/

[ BLOCK . . ]
#============
cdsay <PROJDIR>

# Export symbols DIP Builder Control file
# =======================================

set PROJDIR=<CWD>
set PROJNAME=export

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defdylib.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/dos386/export.dip     <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/dos386/export.sym     <RELROOT>/binw/export.dsy

    <CCCMD> <PROJDIR>/wini86/export.dll     <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/wini86/export.sym     <RELROOT>/binw/

#    <CCCMD> <PROJDIR>/os2i86/export.dll     <RELROOT>/binp/dll/
#    <CCCMD> <PROJDIR>/os2i86/export.sym     <RELROOT>/binp/dll/
    <CCCMD> <PROJDIR>/os2386/export.d32     <RELROOT>/binp/
    <CCCMD> <PROJDIR>/os2386/export.sym     <RELROOT>/binp/

    <CCCMD> <PROJDIR>/nt386/export.dll      <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/nt386/export.sym      <RELROOT>/binnt/

    <CCCMD> <PROJDIR>/linux386/export.dip   <RELROOT>/binl/
    <CCCMD> <PROJDIR>/linux386/export.sym   <RELROOT>/binl/

    <CCCMD> <PROJDIR>/ntaxp/export.dll      <RELROOT>/axpnt/
    <CCCMD> <PROJDIR>/ntaxp/export.sym      <RELROOT>/axpnt/

    <CCCMD> <PROJDIR>/qnx386/export.dip     <RELROOT>/qnx/watcom/wd/
    <CCCMD> <PROJDIR>/qnx386/export.sym     <RELROOT>/qnx/sym/

[ BLOCK . . ]
#============
cdsay <PROJDIR>

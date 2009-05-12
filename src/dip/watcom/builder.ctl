# WATCOM DIP Builder Control file
# ===============================

set PROJDIR=<CWD>
set PROJNAME=watcom

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defdylib.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/dos386/watcom.dip     <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/dos386/watcom.sym     <RELROOT>/binw/watcom.dsy

    <CCCMD> <PROJDIR>/wini86/watcom.dll     <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/wini86/watcom.sym     <RELROOT>/binw/

#    <CCCMD> <PROJDIR>/os2i86/watcom.dll     <RELROOT>/binp/dll/
#    <CCCMD> <PROJDIR>/os2i86/watcom.sym     <RELROOT>/binp/dll/
    <CCCMD> <PROJDIR>/os2386/watcom.d32     <RELROOT>/binp/
    <CCCMD> <PROJDIR>/os2386/watcom.sym     <RELROOT>/binp/

    <CCCMD> <PROJDIR>/nt386/watcom.dll      <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/nt386/watcom.sym      <RELROOT>/binnt/

    <CCCMD> <PROJDIR>/linux386/watcom.dip   <RELROOT>/binl/
    <CCCMD> <PROJDIR>/linux386/watcom.sym   <RELROOT>/binl/

    <CCCMD> <PROJDIR>/ntaxp/watcom.dll      <RELROOT>/axpnt/
    <CCCMD> <PROJDIR>/ntaxp/watcom.sym      <RELROOT>/axpnt/

    <CCCMD> <PROJDIR>/qnx386/watcom.dip     <RELROOT>/qnx/watcom/wd/
    <CCCMD> <PROJDIR>/qnx386/watcom.sym     <RELROOT>/qnx/sym/

[ BLOCK . . ]
#============
cdsay <PROJDIR>

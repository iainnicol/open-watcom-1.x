# x86 MAD Builder Control file
# ============================

set PROJDIR=<CWD>
set PROJNAME=madx86

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defdylib.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/dos386/madx86.mad     <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/dos386/madx86.sym     <RELROOT>/binw/madx86.dsy

    <CCCMD> <PROJDIR>/wini86/madx86.dll     <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/wini86/madx86.sym     <RELROOT>/binw/

#    <CCCMD> <PROJDIR>/os2i86/madx86.dll     <RELROOT>/binp/dll/
#    <CCCMD> <PROJDIR>/os2i86/madx86.sym     <RELROOT>/binp/dll/
    <CCCMD> <PROJDIR>/os2386/madx86.d32     <RELROOT>/binp/
    <CCCMD> <PROJDIR>/os2386/madx86.sym     <RELROOT>/binp/

    <CCCMD> <PROJDIR>/nt386/madx86.dll      <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/nt386/madx86.sym      <RELROOT>/binnt/

    <CCCMD> <PROJDIR>/linux386/madx86.mad   <RELROOT>/binl/
    <CCCMD> <PROJDIR>/linux386/madx86.sym   <RELROOT>/binl/

    <CCCMD> <PROJDIR>/ntaxp/madx86.dll      <RELROOT>/axpnt/
    <CCCMD> <PROJDIR>/ntaxp/madx86.sym      <RELROOT>/axpnt/

    <CCCMD> <PROJDIR>/qnx386/madx86.mad     <RELROOT>/qnx/watcom/wd/
    <CCCMD> <PROJDIR>/qnx386/madx86.sym     <RELROOT>/qnx/sym/

[ BLOCK . . ]
#============
cdsay <PROJDIR>

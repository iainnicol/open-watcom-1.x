# PowerPC MAD Builder Control file
# ================================

set PROJDIR=<CWD>
set PROJNAME=madppc

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defdylib.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/dos386/madppc.mad     <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/dos386/madppc.sym     <RELROOT>/binw/madppc.dsy

    <CCCMD> <PROJDIR>/wini86/madppc.dll     <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/wini86/madppc.sym     <RELROOT>/binw/

#    <CCCMD> <PROJDIR>/os2i86/madppc.dll     <RELROOT>/binp/dll/
#    <CCCMD> <PROJDIR>/os2i86/madppc.sym     <RELROOT>/binp/dll/
    <CCCMD> <PROJDIR>/os2386/madppc.d32     <RELROOT>/binp/
    <CCCMD> <PROJDIR>/os2386/madppc.sym     <RELROOT>/binp/

    <CCCMD> <PROJDIR>/nt386/madppc.dll      <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/nt386/madppc.sym      <RELROOT>/binnt/

    <CCCMD> <PROJDIR>/linux386/madppc.mad   <RELROOT>/binl/
    <CCCMD> <PROJDIR>/linux386/madppc.sym   <RELROOT>/binl/

    <CCCMD> <PROJDIR>/ntaxp/madppc.dll      <RELROOT>/axpnt/
    <CCCMD> <PROJDIR>/ntaxp/madppc.sym      <RELROOT>/axpnt/

    <CCCMD> <PROJDIR>/qnx386/madppc.mad     <RELROOT>/qnx/watcom/wd/
    <CCCMD> <PROJDIR>/qnx386/madppc.sym     <RELROOT>/qnx/sym/

[ BLOCK . . ]
#============
cdsay <PROJDIR>

# CodeView DIP Builder Control file
# =================================

set PROJDIR=<CWD>
set PROJNAME=codeview

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defdylib.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/dos386/codeview.dip       <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/dos386/codeview.sym       <RELROOT>/binw/codeview.dsy

    <CCCMD> <PROJDIR>/wini86/codeview.dll       <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/wini86/codeview.sym       <RELROOT>/binw/

#    <CCCMD> <PROJDIR>/os2i86/codeview.dll       <RELROOT>/binp/dll/
#    <CCCMD> <PROJDIR>/os2i86/codeview.sym       <RELROOT>/binp/dll/
    <CCCMD> <PROJDIR>/os2386/codeview.d32       <RELROOT>/binp/
    <CCCMD> <PROJDIR>/os2386/codeview.sym       <RELROOT>/binp/

    <CCCMD> <PROJDIR>/nt386/codeview.dll        <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/nt386/codeview.sym        <RELROOT>/binnt/

    <CCCMD> <PROJDIR>/linux386/codeview.dip     <RELROOT>/binl/
    <CCCMD> <PROJDIR>/linux386/codeview.sym     <RELROOT>/binl/

    <CCCMD> <PROJDIR>/ntaxp/codeview.dll        <RELROOT>/axpnt/
    <CCCMD> <PROJDIR>/ntaxp/codeview.sym        <RELROOT>/axpnt/

    <CCCMD> <PROJDIR>/qnx386/codeview.dip       <RELROOT>/qnx/watcom/wd/
    <CCCMD> <PROJDIR>/qnx386/codeview.sym       <RELROOT>/qnx/sym/

[ BLOCK . . ]
#============
cdsay <PROJDIR>

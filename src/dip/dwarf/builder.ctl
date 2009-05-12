# DWARF DIP Builder Control file
# ==============================

set PROJDIR=<CWD>
set PROJNAME=dwarf

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defdylib.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/dos386/dwarf.dip      <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/dos386/dwarf.sym      <RELROOT>/binw/dwarf.dsy

    <CCCMD> <PROJDIR>/wini86/dwarf.dll      <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/wini86/dwarf.sym      <RELROOT>/binw/

#    <CCCMD> <PROJDIR>/os2i86/dwarf.dll      <RELROOT>/binp/dll/
#    <CCCMD> <PROJDIR>/os2i86/dwarf.sym      <RELROOT>/binp/dll/
    <CCCMD> <PROJDIR>/os2386/dwarf.d32      <RELROOT>/binp/
    <CCCMD> <PROJDIR>/os2386/dwarf.sym      <RELROOT>/binp/

    <CCCMD> <PROJDIR>/nt386/dwarf.dll       <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/nt386/dwarf.sym       <RELROOT>/binnt/

    <CCCMD> <PROJDIR>/linux386/dwarf.dip    <RELROOT>/binl/
    <CCCMD> <PROJDIR>/linux386/dwarf.sym    <RELROOT>/binl/

    <CCCMD> <PROJDIR>/ntaxp/dwarf.dll       <RELROOT>/axpnt/
    <CCCMD> <PROJDIR>/ntaxp/dwarf.sym       <RELROOT>/axpnt/

    <CCCMD> <PROJDIR>/qnx386/dwarf.dip      <RELROOT>/qnx/watcom/wd/
    <CCCMD> <PROJDIR>/qnx386/dwarf.sym      <RELROOT>/qnx/sym/

[ BLOCK . . ]
#============
cdsay <PROJDIR>

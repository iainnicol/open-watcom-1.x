# exe2bin Builder Control file
# ============================

set PROJDIR=<CWD>
set PROJNAME=exe2bin

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/deftool.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/dosi86/exe2bin.exe        <RELROOT>/binw/exe2bin.exe
    <CCCMD> <PROJDIR>/os2386/exe2bin.exe        <RELROOT>/binp/exe2bin.exe
    <CCCMD> <PROJDIR>/nt386/exe2bin.exe         <RELROOT>/binnt/exe2bin.exe
    <CCCMD> <PROJDIR>/linux386/exe2bin.exe      <RELROOT>/binl/exe2bin
    <CCCMD> <PROJDIR>/ntaxp/exe2bin.exe         <RELROOT>/axpnt/exe2bin.exe

[ BLOCK . . ]
#============
cdsay <PROJDIR>

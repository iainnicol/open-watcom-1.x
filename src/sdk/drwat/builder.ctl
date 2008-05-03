# DRWATCOM Builder Control file
# ============================

set PROJDIR=<CWD>
set PROJNAME=drwatcom

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/win/wini86/drwatcom.exe  <RELROOT>/binw/drwatcom.exe
    <CCCMD> <PROJDIR>/nt/nt386/drwatcom.exe    <RELROOT>/binnt/drwatcom.exe
    <CCCMD> <PROJDIR>/nt/win95/drwatcom.exe    <RELROOT>/binnt/_drwin95.exe
    <CCCMD> <PROJDIR>/nt/ntaxp/drwatcom.exe    <RELROOT>/axpnt/drwatcom.exe

[ BLOCK . . ]
#============
cdsay <PROJDIR>

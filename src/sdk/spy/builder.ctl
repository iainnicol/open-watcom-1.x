# SPY Builder Control file
# ============================

set PROJDIR=<CWD>
set PROJNAME=spy

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/wini86/wspy.exe    <RELROOT>/binw/wspy.exe
    <CCCMD> <PROJDIR>/wini86/wspyhk.dll  <RELROOT>/binw/wspyhk.dll

    <CCCMD> <PROJDIR>/nt386/wspy.exe     <RELROOT>/binnt/wspy.exe
    <CCCMD> <PROJDIR>/nt386/ntspyhk.dll  <RELROOT>/binnt/ntspyhk.dll

    <CCCMD> <PROJDIR>/ntaxp/wspy.exe     <RELROOT>/axpnt/wspy.exe
    <CCCMD> <PROJDIR>/ntaxp/ntspyhk.dll  <RELROOT>/axpnt/ntspyhk.dll

[ BLOCK . . ]
#============
cdsay <PROJDIR>

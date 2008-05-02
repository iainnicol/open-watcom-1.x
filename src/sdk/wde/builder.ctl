# WDE Builder Control file
# ========================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> build rel ]
#======================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h

[ BLOCK <1> rel ]
#================
    cdsay <PROJDIR>

[ BLOCK <1> rel cprel ]
#======================
    <CPCMD> <PROJDIR>/wini86/wde.exe      <RELROOT>/binw/wde.exe
    <CPCMD> <PROJDIR>/nt386/wde.exe       <RELROOT>/binnt/wde.exe
    <CPCMD> <PROJDIR>/ntaxp/wde.exe       <RELROOT>/axpnt/wde.exe

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean

[ BLOCK . . ]
#============
cdsay <PROJDIR>

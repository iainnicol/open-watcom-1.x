# WIC Builder Control file
# ========================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> build rel2 ]
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cd <PROJDIR>

[ BLOCK <1> rel2 cprel2 ]
#========================
    <CPCMD> <DEVDIR>/wic/os2386/wic.exe <relroot>/rel2/binp/wic.exe
    <CPCMD> <DEVDIR>/wic/dos386/wic.exe <relroot>/rel2/binw/wic.exe
    <CPCMD> <DEVDIR>/wic/nt386/wic.exe <relroot>/rel2/binnt/wic.exe

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean

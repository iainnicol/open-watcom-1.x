# windows 16-bit API Builder Control file
# ===========================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> build rel2 ]
#=======================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cd <PROJDIR>

[ BLOCK <1> rel2 cprel2 acprel2 ]
#================================
  [ IFDEF (os_win "") <2*> ]
    <CPCMD> wini86/*.lib               <RELROOT>/rel2/lib286/win/
  [ ENDIF ]
    <CPCMD> include/*.h                <RELROOT>/rel2/h/win/
    <CPCMD> <DEVDIR>/sdk/misc/ctl3d.h  <RELROOT>/rel2/h/win/

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
    cd <PROJDIR>


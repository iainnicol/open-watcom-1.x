# WR Builder Control file
# =======================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> build rel2 ]
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cd <PROJDIR>

[ BLOCK <1> rel2 cprel2 ]
#========================
  [ IFDEF (os_win "") <2*> ]
    <CPCMD> <DEVDIR>/sdk/wr/wini86/wr.dll        <RELROOT>/rel2/binw/wr.dll
  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> <DEVDIR>/sdk/wr/nt386/wr.dll         <RELROOT>/rel2/binnt/wr.dll
  [ IFDEF (cpu_axp) <2*> ]
    <CPCMD> <DEVDIR>/sdk/wr/ntaxp/wr.dll         <RELROOT>/rel2/axpnt/wr.dll

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
    cd <PROJDIR>


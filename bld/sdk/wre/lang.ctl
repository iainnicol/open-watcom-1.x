# WRE Builder Control file
# ========================

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
    <CPCMD> <DEVDIR>/sdk/wre/wini86/wre.exe         <RELROOT>/rel2/binw/wre.exe
  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> <DEVDIR>/sdk/wre/nt386/wre.exe          <RELROOT>/rel2/binnt/wre.exe
  [ IFDEF (cpu_axp) <2*> ]
    <CPCMD> <DEVDIR>/sdk/wre/ntaxp/wre.exe          <RELROOT>/rel2/axpnt/wre.exe

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
    cdsay <PROJDIR>


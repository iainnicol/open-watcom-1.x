# DRWATCOM Builder Control file
# ============================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> build rel2 ]
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cdsay <PROJDIR>

[ BLOCK <1> rel2 cprel2 ]
  [ IFDEF (os_win "") <2*> ]
    <CPCMD> <DEVDIR>/sdk/drwat/win/obj/drwatcom.exe <RELROOT>/rel2/binw/drwatcom.exe
  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> <DEVDIR>/sdk/drwat/nt/nt386/drwatcom.exe <RELROOT>/rel2/binnt/drwatcom.exe
    <CPCMD> <DEVDIR>/sdk/drwat/nt/win95/drwatcom.exe <RELROOT>/rel2/binnt/_drwin95.exe
  [ IFDEF (cpu_axp) <2*> ]
    <CPCMD> <DEVDIR>/sdk/drwat/nt/ntaxp/drwatcom.exe <RELROOT>/rel2/axpnt/drwatcom.exe

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
    cdsay <PROJDIR>

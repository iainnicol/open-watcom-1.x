# IMAGE EDITOR Builder Control file
# =================================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> build rel2 ]
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cdsay <PROJDIR>

[ BLOCK <1> rel2 cprel2 ]
  [ IFDEF (os_win "") <2*> ]
    <CPCMD> <DEVDIR>/sdk/imgedit/wini86/wimgedit.exe <RELROOT>/rel2/binw/
  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> <DEVDIR>/sdk/imgedit/nt386/wimgedit.exe <RELROOT>/rel2/binnt/
  [ IFDEF (cpu_axp) <2*> ]
    <CPCMD> <DEVDIR>/sdk/imgedit/ntaxp/wimgedit.exe <RELROOT>/rel2/axpnt/

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
    cdsay <PROJDIR>


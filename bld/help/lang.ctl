# WHELP Builder Control file
# =========================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/bat/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> build rel2 ]
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cdsay <PROJDIR>

[ BLOCK <1> rel2 cprel2 ]
#========================
  [ IFDEF (os_dos "") <2*> ]
    <CPCMD> <PROJDIR>/dos386/whelp.exe    <RELROOT>/rel2/binw/whelp.exe
  [ IFDEF (os_os2 "") <2*> ]
    <CPCMD> <PROJDIR>/os2386/whelp.exe    <RELROOT>/rel2/binp/whelp.exe
  [ IFDEF (os_linux "") <2*> ]
    <CPCMD> <PROJDIR>/linux386/whelp.exe  <RELROOT>/rel2/binl/whelp

[ BLOCK <1> clean ]
#==================
    pmake -d all -h clean
    cdsay <PROJDIR>


# WTOUCH Builder Control file
# ===========================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> build rel2 ]
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cd <PROJDIR>

[ BLOCK <1> rel2 cprel2 ]
#========================
  [ IFDEF (os_dos "") <2*> ]
    <CPCMD> <PROJDIR>/dosi86/wtouch.exe    <RELROOT>/rel2/binw/wtouch.exe

  [ IFDEF (os_os2 "") <2*> ]
    <CPCMD> <PROJDIR>/os2386/wtouch.exe    <RELROOT>/rel2/binp/wtouch.exe

  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> <PROJDIR>/nt386/wtouch.exe     <RELROOT>/rel2/binnt/wtouch.exe

  [ IFDEF (os_linux "") <2*> ]
    <CPCMD> <PROJDIR>/linux386/wtouch.exe  <RELROOT>/rel2/binl/wtouch

  [ IFDEF (cpu_axp) <2*> ]
    <CPCMD> <PROJDIR>/ntaxp/wtouch.exe     <RELROOT>/rel2/axpnt/wtouch.exe


[ BLOCK <1> clean ]
#==================
    pmake -d all -h clean
    cd <PROJDIR>

# w32ldr Builder Control file
# ===========================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/bat/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> build rel2 ]
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cd <PROJDIR>

[ BLOCK <1> rel2 cprel2 acprel2 ]
#================================
  [ IFDEF (os_dos "") <2*> ]
#   <CPCMD> dos386/x32run.exe   <RELROOT>/rel2/binw/x32run.exe
#   <CPCMD> dos386/x32run.exe   <RELROOT>/rel2/binw/w32run.exe
#   <CPCMD> dos386/d4grun.exe   <RELROOT>/rel2/binw/d4grun.exe
#   <CPCMD> dos386/tntrun.exe   <RELROOT>/rel2/binw/tntrun.exe

  [ IFDEF (os_os2 "") <2*> ]
    <CPCMD> os2386/w32bind.exe  ../build/binp/w32bind.exe
    <CPCMD> os2386/os2ldr.exe   ../build/binp/os2ldr.exe

  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> nt386/ntrunner.exe  <RELROOT>/rel2/binnt/w32run.exe
#    these are now real NT exe's - don't copy the stub
#    <CPCMD> nt/*.exe           <RELROOT>/rel2/binnt/

[ BLOCK <1> clean ]
#=================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
    cd <PROJDIR>

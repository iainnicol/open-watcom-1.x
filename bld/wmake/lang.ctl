# WMake Builder Control file
# ==========================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> build rel2 ]
#=======================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cd <PROJDIR>

[ BLOCK <1> rel2 cprel2 ]
#========================
  [ IFDEF (os_dos "") <2*> ]
    <CPCMD> <DEVDIR>/wmake/dosi86/wmk.exe    <RELROOT>/rel2/binw/wmaker.exe
    <CPCMD> <DEVDIR>/wmake/dos386/wmk.exe    <RELROOT>/rel2/binw/wmake.exe

  [ IFDEF (os_os2 "") <2*> ]
    <CPCMD> <DEVDIR>/wmake/os2386/wmk.exe    <RELROOT>/rel2/binp/wmake.exe

  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> <DEVDIR>/wmake/nt386/wmk.exe     <RELROOT>/rel2/binnt/wmake.exe

  [ IFDEF (os_linux "") <2*> ]
    <CPCMD> <DEVDIR>/wmake/linux386/wmk.elf  <RELROOT>/rel2/binl/wmake
    <CPCMD> <DEVDIR>/wmake/linux386/wmk.sym  <RELROOT>/rel2/binl/wmake.sym

  [ IFDEF (cpu_axp) <2*> ]
    <CPCMD> <DEVDIR>/wmake/ntaxp/wmk.exe     <RELROOT>/rel2/axpnt/wmake.exe

# I'm guessing for the QNX output, can't build it to check (Mat Nieuwenhoven)
  [ IFDEF (os_qnx)]
    <CPCMD> <DEVDIR>/qnxi86/wmk.qnx          <RELROOT>/rel2/qnx/binq/wmake

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
    cd <PROJDIR>


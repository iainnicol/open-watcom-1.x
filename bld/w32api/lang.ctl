# w32api Builder Control file
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
#NT stuff
    <CPCMD> READ*.*         <RELROOT>/rel2/readme.w32
  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> nt386/include/*.h     <RELROOT>/rel2/h/nt/
    <CPCMD> nt386/include/directx/*.h     <RELROOT>/rel2/h/nt/
    <CPCMD> nt386/include/GL/*.h  <RELROOT>/rel2/h/nt/GL/
    <CPCMD> nt386/*.lib     <RELROOT>/rel2/lib386/nt/

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
    cd <PROJDIR>


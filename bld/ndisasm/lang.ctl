# WDISASM Builder Control file
# ============================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> build rel2 ]
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cdsay <PROJDIR>

[ BLOCK <1> rel2 cprel2 ]
#========================
  [ IFDEF (os_dos "") <2*> ]
    #<CPCMD> <PROJDIR>/osi386/wdis.exe   <RELROOT>/rel2/binw/
    #<CPCMD> <PROJDIR>/osi386/wdis.sym   <RELROOT>/rel2/binw/
    <CPCMD> <PROJDIR>/dos386/wdis.exe   <RELROOT>/rel2/binw/
    <CPCMD> <PROJDIR>/dos386/wdis.sym   <RELROOT>/rel2/binw/

  [ IFDEF (os_os2 "") <2*> ]
    <CPCMD> <PROJDIR>/os2386/wdis.exe   <RELROOT>/rel2/binp/
    <CPCMD> <PROJDIR>/os2386/wdis.sym   <RELROOT>/rel2/binp/

  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> <PROJDIR>/nt386/wdis.exe    <RELROOT>/rel2/binnt/
    <CPCMD> <PROJDIR>/nt386/wdis.sym    <RELROOT>/rel2/binnt/

  [ IFDEF (cpu_axp) <2*> ]
    <CPCMD> <PROJDIR>/ntaxp/wdis.exe    <RELROOT>/rel2/axpnt/
    <CPCMD> <PROJDIR>/ntaxp/wdis.sym    <RELROOT>/rel2/axpnt/

  [ IFDEF (os_qnx) <2*> ]
    <CPCMD> <PROJDIR>/qnx386/wdis.qnx   <RELROOT>/rel2/qnx/binq/wdis
    <CPCMD> <PROJDIR>/qnx386/wdis.sym   <RELROOT>/rel2/qnx/sym/

  [ IFDEF (os_linux "") <2*> ]
    <CPCMD> <PROJDIR>/linux386/wdis.elf <RELROOT>/rel2/binl/wdis
    <CPCMD> <PROJDIR>/linux386/wdis.sym <RELROOT>/rel2/binl/

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
    cdsay <PROJDIR>


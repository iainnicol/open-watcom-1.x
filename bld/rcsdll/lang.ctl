# RCSDLL Builder Control file
# ===========================

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
    <CPCMD> <PROJDIR>/wini86/rcsdll.dll  <RELROOT>/rel2/binw/rcsdll.dll
    <CPCMD> <PROJDIR>/bat/*.bat          <RELROOT>/rel2/binw/
  [ IFDEF (os_os2 "") <2*> ]
    <CPCMD> <PROJDIR>/os2386/rcsdll.dll  <RELROOT>/rel2/binp/dll/rcsdll.dll
    <CPCMD> <PROJDIR>/cmd/*.cmd          <RELROOT>/rel2/binp/
  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> <PROJDIR>/nt386/rcsdll.dll   <RELROOT>/rel2/binnt/rcsdll.dll
  [ IFDEF (cpu_axp) <2*> ]
    <CPCMD> <PROJDIR>/ntaxp/rcsdll.dll   <RELROOT>/rel2/axpnt/rcsdll.dll

[ BLOCK <1> clean ]
#==================
    pmake -d all <2> <3> <4> <5> <6> <7> <8> <9> -h clean
    cdsay <PROJDIR>


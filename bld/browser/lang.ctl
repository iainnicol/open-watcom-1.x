# Browser Builder Control file
# ============================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> build rel2 ]
#=======================
    # pmake priorities are used to build:
    # 1) dlgprs/o
    # 2) gen
    # 3) everywhere else.
    #
    # gen is dependent on dlgprs/o
    # the os_dos dlgprs/o and gen are dependent on windows.h and not selected.
    # brg/* are independent of dlgprs/o and gen
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cdsay <PROJDIR>


[ BLOCK <1> rel2 cprel2 ]
#========================
  [ IFDEF (os_dos "") <2*> ]
    <CPCMD> <DEVDIR>/browser/brg/dos386/wbrg.exe    <RELROOT>/rel2/binw/wbrg.exe

  [ IFDEF (os_win "") <2*> ]
    <CPCMD> <DEVDIR>/browser/wini86/wbrw.exe        <RELROOT>/rel2/binw/wbrw.exe

  [ IFDEF (os_os2 "") <2*> ]
    <CPCMD> <DEVDIR>/browser/os2386/wbrw.exe        <RELROOT>/rel2/binp/wbrw.exe
    <CPCMD> <DEVDIR>/browser/brg/os2386/wbrg.exe    <RELROOT>/rel2/binp/wbrg.exe

  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> <DEVDIR>/browser/nt386/wbrw.exe         <RELROOT>/rel2/binnt/wbrw.exe
    <CPCMD> <DEVDIR>/browser/brg/nt386/wbrg.exe     <RELROOT>/rel2/binnt/wbrg.exe

  [ IFDEF (cpu_axp) <2*> ]
#   <CPCMD> <DEVDIR>/browser/axpnt/wbrw.exe         <RELROOT>/rel2/axpnt/wbrw.exe
#   <CPCMD> <DEVDIR>/browser/brg/ntaxp/wbrg.exe     <RELROOT>/rel2/axpnt/wbrg.exe

[ BLOCK <1> clean ]
#==================
   pmake -d all <2> <3> <4> <5> <6> <7> <8> <9> -h clean
   cdsay <PROJDIR>


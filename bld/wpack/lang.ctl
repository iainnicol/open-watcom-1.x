# WPACK Builder Control file
# ==========================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> build rel2 ]
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cdsay <PROJDIR>

[ BLOCK <1> rel2 cprel2 ]
#========================
    [ IFDEF <BUILD_PLATFORM> dos386 ]
        <CPCMD> <DEVDIR>/wpack/supp/wpack.exe <OWROOT>/supp/

    [ IFDEF <BUILD_PLATFORM> nt386 ]
        <CPCMD> <DEVDIR>/wpack/supp/wpack.exe <OWROOT>/supp/

    [ IFDEF <BUILD_PLATFORM> os2386 ]
        <CPCMD> <DEVDIR>/wpack/supp/wpack.exe <OWROOT>/supp/

    [ IFDEF <BUILD_PLATFORM> linux386 ]
        <CPCMD> <DEVDIR>/wpack/supp/wpack.exe <OWROOT>/supp/wpack

    [ ENDIF ]

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
    cdsay <PROJDIR>


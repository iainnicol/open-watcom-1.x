# windows 16-bit API Builder Control file
# ===========================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>\master.ctl ]
[ INCLUDE <LANG_BLD>\wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> build rel2 ]
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h

[ BLOCK <1> rel2 cprel2 acprel2 ]

#    <CPCMD> wini86\*.lib <relroot>\rel2\lib286\win\

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean

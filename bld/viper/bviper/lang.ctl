# IDEB (aka BVIPER) Builder Control file
# ======================================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> build rel2 ]
#=======================
    [ INCLUDE prereq.ctl ]

[ BLOCK <1> clean ]
#==================
    pmake -d all -h clean

# YACC Builder Control file
# =========================

set PROJDIR=<CWD>
set PROJNAME=yacc

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/deftool.ctl ]

[ BLOCK <1> rel2 cprel2 ]
#========================
    # Currently not built by default

[ BLOCK . . ]
#============
cdsay <PROJDIR>

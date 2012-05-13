# BUILDER POSIX tools Control file
# ================================

set PROJDIR=<CWD>
set PROJNAME=build POSIX tools

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> boot ]
#=================
    <CPCMD> <OWOBJDIR>/*.exe <OWBINDIR>/

[ BLOCK . . ]
#============
cdsay <PROJDIR>

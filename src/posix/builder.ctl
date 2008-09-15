# BUILDER POSIX tools Control file
# ================================

set PROJDIR=<CWD>
set PROJNAME=build POSIX tools

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> bootclean ]
#======================
    cdsay <PROJDIR>/systems/<OBJDIR>
    wmake -h -f ../bootmake clean_build
    cdsay <PROJDIR>

[ BLOCK . . ]

set BOOTSUBDIR=systems/
set BOOTCOPY=<CPCMD> *.exe <OWBINDIR>/

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK . . ]
#============

cdsay <PROJDIR>

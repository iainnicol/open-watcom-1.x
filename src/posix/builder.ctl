# BUILDER POSIX tools Control file
# ================================

set PROJDIR=<CWD>
set PROJNAME=build POSIX tools

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

set BOOTSUBDIR=systems/

[ BLOCK <1> bootclean ]
#======================
    cdsay <PROJDIR>/<BOOTSUBDIR><OBJDIR>
    wmake -h -f ../bootmake clean_build
    cdsay <PROJDIR>

[ BLOCK . . ]

set BOOTCOPY=<CPCMD> *.exe <OWBINDIR>/
set BOOTCLEAN=rm -f <OWBINDIR>/<PROJNAME><CMDEXT>

[ INCLUDE <OWROOT>/build/defrule.ctl ]

cdsay <PROJDIR>

# BUILDER Builder Control file
# =========================

set PROJDIR=<CWD>
set PROJNAME=build utilities

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> build rel2 ]
#=======================
    [ INCLUDE prereq.ctl ]

[ BLOCK <1> clean ]
#==================
    pmake -d all -h clean

[ BLOCK <1> boot ]
#=================
    echo Building the build utilities bootstrap
    mkdir <PROJDIR>/<OBJDIR>
    cdsay <PROJDIR>/<OBJDIR>
    wmake -h -f ../bootmake
    cdsay <PROJDIR>

[ BLOCK <1> bootclean ]
#======================
    echo rm -f -r <PROJDIR>/<OBJDIR>
    rm -f -r <PROJDIR>/<OBJDIR>
    echo rm -f <OWBINDIR>/wsplice<CMDEXT> <OWBINDIR>/sweep<CMDEXT>
    rm -f <OWBINDIR>/wsplice<CMDEXT> <OWBINDIR>/sweep<CMDEXT>
    echo rm -f <OWBINDIR>/cdsay<CMDEXT> <OWBINDIR>/comstrip<CMDEXT>
    rm -f <OWBINDIR>/cdsay<CMDEXT> <OWBINDIR>/comstrip<CMDEXT>
    echo rm -f <OWBINDIR>/diff<CMDEXT> <OWBINDIR>/aliasgen<CMDEXT>
    rm -f <OWBINDIR>/diff<CMDEXT> <OWBINDIR>/aliasgen<CMDEXT>

[ BLOCK . . ]
#============

cdsay <PROJDIR>

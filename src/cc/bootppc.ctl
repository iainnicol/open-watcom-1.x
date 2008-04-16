# wccppc Builder Control file
# ===========================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> bootclean ]
#======================
    echo rm -f -r <PROJDIR>/<OBJDIR>.ppc
    rm -f -r <PROJDIR>/<OBJDIR>.ppc
    echo rm -f <OWBINDIR>/wccppc<CMDEXT>
    rm -f <OWBINDIR>/wccppc<CMDEXT>

[ BLOCK <1> boot ]
#=================
    echo Building the wccppc bootstrap
    mkdir <PROJDIR>/<OBJDIR>.ppc
    cdsay <PROJDIR>/<OBJDIR>.ppc
    cp -f ../linux386.ppc/target.h .
    wmake -h -f ../makeppc
    <CPCMD> wccppc <OWBINDIR>/wccppc<CMDEXT>
    cdsay <PROJDIR>

# wcc Builder Control file
# ========================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> bootclean ]
#======================
    echo rm -f -r <PROJDIR>/<OBJDIR>.i86
    rm -f -r <PROJDIR>/<OBJDIR>.i86
    echo rm -f <OWBINDIR>/wcc<CMDEXT>
    rm -f <OWBINDIR>/wcc<CMDEXT>

[ BLOCK <1> boot ]
#=================
    echo Building the wcc bootstrap
    mkdir <PROJDIR>/<OBJDIR>.i86
    cdsay <PROJDIR>/<OBJDIR>.i86
    cp -f ../linux386.i86/target.h .
    wmake -h -f ../makei86
    <CPCMD> wcci86c.exe <OWBINDIR>/wcc<CMDEXT>
    cdsay <PROJDIR>

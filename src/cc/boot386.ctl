# wcc386 Builder Control file
# ===========================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> bootclean ]
#======================
    echo rm -f -r <PROJDIR>/<OBJDIR>.386
    rm -f -r <PROJDIR>/<OBJDIR>.386
    echo rm -f <OWBINDIR>/wcc386<CMDEXT>
    rm -f <OWBINDIR>/wcc386<CMDEXT>

[ BLOCK <1> boot ]
#=================
    echo Building the wcc386 bootstrap
    mkdir <PROJDIR>/<OBJDIR>.386
    cdsay <PROJDIR>/<OBJDIR>.386
    cp -f ../linux386.386/target.h .
    wmake -h -f ../make386
    <CPCMD> wcc386c.exe <OWBINDIR>/wcc386<CMDEXT>
    cdsay <PROJDIR>

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <BUILD_PLATFORM> linux386 ]
#==================================
    echo Building the wcc386 bootstrap
    mkdir <PROJDIR>/<OBJDIR>
    cdsay <PROJDIR>/<OBJDIR>
    cp -f ../linux386.386/target.h .
    wmake -h -f ../linux386.386/makefile bootstrap=1
    <CPCMD> wcc386 <DEVDIR>/build/binl/wcc386
    <CPCMD> <DEVDIR>/misc/unicode.* <DEVDIR>/build/binl/
    cdsay <PROJDIR>

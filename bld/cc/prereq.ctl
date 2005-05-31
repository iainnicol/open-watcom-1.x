set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/bat/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

set TMP_BUILD_PLATFORM=<BUILD_PLATFORM>

[ BLOCK <OWLINUXBUILD> bootstrap ]
#=================================
    set BUILD_PLATFORM=<BUILD_PLATFORM>boot

[ BLOCK <1> clean ]
#==================
    echo rm -f -r <PROJDIR>/<OBJDIR>
    rm -f -r <PROJDIR>/<OBJDIR>
    wmake -h -f <DEVDIR>/build/mif/cleanp.mif file=wcc386
    set BUILD_PLATFORM=

[ BLOCK <BUILD_PLATFORM> linux386boot ]
#======================================
    echo Building the wcc386 bootstrap
    mkdir <PROJDIR>/<OBJDIR>
    cdsay <PROJDIR>/<OBJDIR>
    cp -f ../linux386.386/target.h .
    wmake -h -f ../linux386.386/makefile bootstrap=1
    <CPCMD> wcc386 <DEVDIR>/build/binl/wcc386
    <CPCMD> <DEVDIR>/misc/unicode.* <DEVDIR>/build/binl/

[ BLOCK . . ]
#============
set BUILD_PLATFORM=<TMP_BUILD_PLATFORM>
set TMP_BUILD_PLATFORM=

cdsay <PROJDIR>

# wcl Builder Control file
# ==========================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/bat/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

set TMP_BUILD_PLATFORM=<BUILD_PLATFORM>

[ BLOCK <OWLINUXBUILD> bootstrap ]
#=================================
    set BUILD_PLATFORM=<BUILD_PLATFORM>boot

[ BLOCK <1> clean ]
#==================
    echo rm -f -r <PROJDIR>/<OBJDIR>
    rm -f -r <PROJDIR>/<OBJDIR>
    wmake -h -f <DEVDIR>/build/mif/cleanp.mif platform=<BUILD_PLATFORM> file=bwcl386
    set BUILD_PLATFORM=

[ BLOCK <BUILD_PLATFORM> dos386 ]
#================================
    mkdir <PROJDIR>\<OBJDIR>
    cdsay <PROJDIR>\<OBJDIR>
    wmake -h -f ../dosi86.386/makefile
    <CPCMD> wcl386.exe <DEVDIR>/build/bin/bwcl386.exe
    cdsay <PROJDIR>

[ BLOCK <BUILD_PLATFORM> os2386 ]
#================================
    mkdir <PROJDIR>\<OBJDIR>
    cdsay <PROJDIR>\<OBJDIR>
    wmake -h -f ../os2386.386/makefile
    <CPCMD> wcl386.exe <DEVDIR>/build/binp/bwcl386.exe
    cdsay <PROJDIR>

[ BLOCK <BUILD_PLATFORM> nt386 ]
#===============================
    mkdir <PROJDIR>\<OBJDIR>
    cdsay <PROJDIR>\<OBJDIR>
    wmake -h -f ../nt386.386/makefile
    <CPCMD> wcl386.exe <DEVDIR>/build/binnt/bwcl386.exe
    cdsay <PROJDIR>

[ BLOCK <BUILD_PLATFORM> linux386boot ]
#======================================
    echo Building the wcl bootstrap
    mkdir <PROJDIR>/<OBJDIR>
    cdsay <PROJDIR>/<OBJDIR>
    wmake -h -f ../linux386.386/makefile
    <CPCMD> wcl386.exe <DEVDIR>/build/binl/bwcl386
    <CPCMD> wcl386.exe <DEVDIR>/build/binl/wcl386
    cdsay <PROJDIR>

[ BLOCK <BUILD_PLATFORM> linux386 ]
#==================================
    mkdir <PROJDIR>/<OBJDIR>
    cdsay <PROJDIR>/<OBJDIR>
    wmake -h -f ../linux386.386/makefile
    <CPCMD> wcl386.exe <DEVDIR>/build/binl/bwcl386
    cdsay <PROJDIR>

[ BLOCK . . ]
#==================
set BUILD_PLATFORM=<TMP_BUILD_PLATFORM>
set TMP_BUILD_PLATFORM=


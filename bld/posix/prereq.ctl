# POSIX Prerequisite Tool Build Control File
# =========================================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> clean ]
#==================
set TMP_BUILD_PLATFORM=<BUILD_PLATFORM>
set BUILD_PLATFORM=

[ BLOCK <BUILD_PLATFORM> dos386 ]
#================================
    mkdir <PROJDIR>\<OBJDIR>
    cdsay <PROJDIR>\<OBJDIR>
    wmake -h -f ../systems/dos/makefile prebuild=1
    <CPCMD> *.exe <OWROOT>\bld\build\bin\
    cdsay <PROJDIR>

[ BLOCK <BUILD_PLATFORM> os2386 ]
#================================
    mkdir <PROJDIR>\<OBJDIR>
    cdsay <PROJDIR>\<OBJDIR>
    wmake -h -f ../systems/os2386/makefile prebuild=1
    <CPCMD> *.exe <OWROOT>\bld\build\binp\
    cdsay <PROJDIR>

[ BLOCK <BUILD_PLATFORM> nt386 ]
#===============================
    mkdir <PROJDIR>\<OBJDIR>
    cdsay <PROJDIR>\<OBJDIR>
    wmake -h -f ../systems/nt386/makefile prebuild=1
    <CPCMD> *.exe <OWROOT>\bld\build\binnt\
    cdsay <PROJDIR>

[ BLOCK <1> clean ]
#==================
set BUILD_PLATFORM=<TMP_BUILD_PLATFORM>
set TMP_BUILD_PLATFORM=
    rm -f -r <PROJDIR>/<OBJDIR>

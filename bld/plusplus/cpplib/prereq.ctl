# C++ Reference Compilers Prerequisite Tool Build Control File
# ============================================================

[ BLOCK <BUILD_PLATFORM> dos386 ]
#================================
    echo Building DOS 386 C++ reference compilers
    cdsay <projdir>\..\dosi86
    wmake -h -k reference
    cdsay ..\dos386
    wmake -h -k reference
    cdsay <projdir>

[ BLOCK <BUILD_PLATFORM> os2386 ]
#================================
    echo Building OS/2 386 C++ reference compilers
    cdsay <projdir>\..\os2i86
    wmake -h -k reference
    cdsay ..\os2386
    wmake -h -k reference
    cdsay <projdir>

[ BLOCK <BUILD_PLATFORM> nt386 ]
#===============================
    echo Building Win32 386 C++ reference compilers
    cdsay <projdir>\..\nti86
    wmake -h -k reference
    cdsay ..\nt386
    wmake -h -k reference
    cdsay <projdir>

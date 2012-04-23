# Installer builder control file
# ==============================

set INSTDIR=<CWD>

[ INCLUDE <OWROOT>/bat/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

echo Installer Build: <1> <2> <3> <4> <5>

[ BLOCK <1> build rel2 ]
#=======================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean

[ BLOCK <1> missing ]
    #########################################################
    # this is hack used by build server to create installers
    # mksetup -x create all missing files with zero length
    # it is dedicated for missing help files which are not
    # buildable on each host platform
    #########################################################
    langdat c
    mksetup -x -i../include c filelist <RELROOT>
    langdat f77
    mksetup -x -i../include f77 filelist <RELROOT>
    rm filelist

[ BLOCK . . ]
cdsay .

# Redistributable binary files control file
# =========================================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/bat/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> build rel2 ]
#=======================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h

[ BLOCK <1> rel2 cprel2 ]
#========================
    <CPCMD> <DEVDIR>/redist/causeway/* <RELROOT>/rel2/binw/
    <CPCMD> <DEVDIR>/redist/causeway/cwdll/*.lib <RELROOT>/rel2/lib386/dos/
    <CPCMD> <DEVDIR>/redist/causeway/cwdll/*.h <RELROOT>/rel2/h/
    <CPCMD> <DEVDIR>/redist/dos4gw/* <RELROOT>/rel2/binw/
    <CPCMD> <DEVDIR>/redist/dos32a/* <RELROOT>/rel2/binw/
    <CPCMD> <DEVDIR>/redist/pmodew/* <RELROOT>/rel2/binw/

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean

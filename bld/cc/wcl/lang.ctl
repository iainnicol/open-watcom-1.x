# wcl Builder Control file
# ========================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/bat/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> build rel2 ]
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h

[ BLOCK <1> rel2 cprel2 acprel2 ]
#================================
    <CPCMD> <DEVDIR>/cc/wcl/dosi86/wcl.exe    <RELROOT>/rel2/binw/wcl.exe
    <CPCMD> <DEVDIR>/cc/wcl/dosi86/wcl386.exe <RELROOT>/rel2/binw/wcl386.exe
    <CPCMD> <DEVDIR>/cc/wcl/os2386/wcl.exe    <RELROOT>/rel2/binp/wcl.exe
    <CPCMD> <DEVDIR>/cc/wcl/os2386/wcl386.exe <RELROOT>/rel2/binp/wcl386.exe
    <CPCMD> <DEVDIR>/cc/wcl/nt386/wcl.exe     <RELROOT>/rel2/binnt/wcl.exe
    <CPCMD> <DEVDIR>/cc/wcl/nt386/wcl386.exe  <RELROOT>/rel2/binnt/wcl386.exe
#   <CPCMD> <DEVDIR>/cc/wcl/nt386/wclaxp.exe  <RELROOT>/rel2/binnt/wclaxp.exe
#   <CPCMD> <DEVDIR>/cc/wcl/ntaxp/wcl.exe     <RELROOT>/rel2/axpnt/wcl.exe
#   <CPCMD> <DEVDIR>/cc/wcl/ntaxp/wcl386.exe  <RELROOT>/rel2/axpnt/wcl386.exe
#   <CPCMD> <DEVDIR>/cc/wcl/ntaxp/wclaxp.exe  <RELROOT>/rel2/axpnt/wclaxp.exe

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean

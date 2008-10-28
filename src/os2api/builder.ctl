# os2api Builder Control file
# ==========================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> build rel ]
#=======================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h

[ BLOCK <1> rel ]
#=================
    cdsay <PROJDIR>

[ BLOCK <1> rel cprel acprel ]
#================================
#16-bit stuff
    <CPCMD> os2286/include/*.h          <RELROOT>/h/os21x/
    <CPCMD> os2286/lib/*.lib            <RELROOT>/lib286/os2/
#32-bit stuff
    <CPCMD> os2386/include/*.h          <RELROOT>/h/os2/
    <CPCMD> os2386/include/arpa/*.h     <RELROOT>/h/os2/arpa/
    <CPCMD> os2386/include/machine/*.h  <RELROOT>/h/os2/machine/
    <CPCMD> os2386/include/net/*.h      <RELROOT>/h/os2/net/
    <CPCMD> os2386/include/netinet/*.h  <RELROOT>/h/os2/netinet/
    <CPCMD> os2386/include/protocol/*.h <RELROOT>/h/os2/protocol/
    <CPCMD> os2386/include/sys/*.h      <RELROOT>/h/os2/sys/
    <CPCMD> os2386/include/GL/*.h       <RELROOT>/h/os2/GL/
    <CPCMD> os2386/lib/*.lib            <RELROOT>/lib386/os2/

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean

[ BLOCK . . ]
#============

cdsay <PROJDIR>

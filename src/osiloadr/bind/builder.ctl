# osibind Builder Control file
# ============================

set PROJDIR=<CWD>
set PROJNAME=osibind

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/deftool.ctl ]


[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> dosi86/osibind.exe  <RELROOT>/binw/osibind.exe
    <CCCMD> os2386/osibind.exe  <RELROOT>/binp/osibind.exe
    <CCCMD> nt386/osibind.exe   <RELROOT>/binnt/osibind.exe


[ BLOCK . . ]
#============
cdsay <PROJDIR>

# Windows 16-bit API Builder Control file
# =======================================

set PROJDIR=<CWD>
set PROJNAME=w16api

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel acprel ]
#=============================
    <CPCMD> wini86/*.lib                <RELROOT>/lib286/win/
    <CPCMD> wini86/*.h                  <RELROOT>/h/win/
#    <CPCMD> <DEVDIR>/sdk/misc/ctl3d.h   <RELROOT>/h/win/

[ BLOCK . . ]
#============
cdsay <PROJDIR>

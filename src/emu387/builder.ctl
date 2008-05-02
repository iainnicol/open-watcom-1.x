# 387 emulator Builder Control file
# =================================

set PROJDIR=<CWD>
set PROJNAME=emu387

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/stub386/emu387.lib <RELROOT>/lib386/noemu387.lib
    <CCCMD> <PROJDIR>/stub386/emu387.lib <RELROOT>/lib386/osi/emu387.lib
    <CCCMD> <PROJDIR>/dos386/emu387.lib  <RELROOT>/lib386/dos/emu387.lib
    <CCCMD> <PROJDIR>/stub386/emu387.lib <RELROOT>/lib386/win/emu387.lib
    <CCCMD> <PROJDIR>/stub386/emu387.lib <RELROOT>/lib386/os2/emu387.lib
    <CCCMD> <PROJDIR>/stub386/emu387.lib <RELROOT>/lib386/nt/emu387.lib
    <CCCMD> <PROJDIR>/stub386/emu387.lib <RELROOT>/lib386/linux/emu387.lib
    <CCCMD> <PROJDIR>/stub386/emu387.lib <RELROOT>/lib386/netware/emu387.lib
    <CCCMD> <PROJDIR>/stub386/emu387.lib <RELROOT>/lib386/qnx/emu387.lib
    <CCCMD> <PROJDIR>/qnx386/emu387      <RELROOT>/qnx/binq/emu387

[ BLOCK . . ]
#============
cdsay <PROJDIR>

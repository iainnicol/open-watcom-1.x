# emu87 Builder Control file
# ==========================

set PROJDIR=<CWD>
set PROJNAME=emu87

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/stubi86/noemu87.lib  <RELROOT>/lib286/noemu87.lib
    <CCCMD> <PROJDIR>/dosi86/emu87.lib     <RELROOT>/lib286/dos/emu87.lib
    <CCCMD> <PROJDIR>/wini86/emu87.lib     <RELROOT>/lib286/win/emu87.lib
    <CCCMD> <PROJDIR>/os2i86/emu87.lib     <RELROOT>/lib286/os2/emu87.lib
    <CCCMD> <PROJDIR>/stubi86/noemu87.lib  <RELROOT>/lib286/qnx/emu87.lib
    <CCCMD> <PROJDIR>/qnxi86/emu86         <RELROOT>/qnx/binq/emu86
    <CCCMD> <PROJDIR>/qnxi86/emu86_16      <RELROOT>/qnx/binq/emu86_16
    <CCCMD> <PROJDIR>/qnxi86/emu86_32      <RELROOT>/qnx/binq/emu86_32

[ BLOCK . . ]
#============
cdsay <PROJDIR>

# UNIX UI lib bootstrap Builder Control file
# ==========================================

set PROJDIR=<CWD>
set PROJNAME=ui library (bootstrap)

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/deflib.ctl ]

[ BLOCK <1> rel cprel ]
#======================
  [ IFDEF (os_qnx) <2*> ]
    <CPCMD> <PROJDIR>/qnx/tix/*.tix <RELROOT>/qnx/tix/

[ BLOCK . . ]
#============
cdsay <PROJDIR>

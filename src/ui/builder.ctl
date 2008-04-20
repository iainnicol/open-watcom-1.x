# UI lib Builder Control file
# ===========================

set PROJDIR=<CWD>
set PROJNAME=ui library

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

set BOOTSUBDIR=unix/

[ INCLUDE <OWROOT>/build/deflib.ctl ]

[ BLOCK <1> rel2 cprel2 ]
#========================
  [ IFDEF (os_qnx) <2*> ]
    <CPCMD> <PROJDIR>/qnx/tix/*.tix <RELROOT>/qnx/tix/

[ BLOCK . . ]
#============
cdsay <PROJDIR>

# GUI lib Builder Control file
# ============================

set PROJDIR=<CWD>
set PROJNAME=gui library

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

set BOOTSUBDIR=ui/

[ INCLUDE <OWROOT>/build/deflib.ctl ]

cdsay <PROJDIR>
